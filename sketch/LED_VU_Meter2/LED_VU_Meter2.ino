#include <arduinoFFT.h>      //https://github.com/kosme/arduinoFFT
//                           //https://github.com/G6EJD/ESP32-8266-Audio-Spectrum-Display
#include <FastLED.h>

#define LED_PIN     12
#define LED_COUNT   300
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[LED_COUNT];


#define NUM_BANDS  4
#define READ_DELAY 50
#define USE_RANDOM_DATA false

arduinoFFT FFT = arduinoFFT();

#define SAMPLES 512              //Must be a power of 2
#define SAMPLING_FREQUENCY 40000 //Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT.

// Use ADC1 so that WiFi stuff doesnt interfere with ADC measurements
#define ADC_PIN 36 // 36 = PIN VP on Lolin D32

int amplitude = 200;
int greenpixels = 12;
int yellowpixels = 14;
unsigned int sampling_period_us;
unsigned long microseconds;
byte peak[] = {0, 0, 0, 0, 0, 0, 0, 0};
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime, oldTime;
uint8_t vuMeterBands[NUM_BANDS];
uint16_t bandSize = 36;
// LED Settings


void displayBand(int band, int dsize)
{
  int dmax = amplitude;
  if (dsize > dmax)
    dsize = dmax;
  if (dsize > peak[band])
  {
    peak[band] = dsize;
  }
}

void setup()
{
  
  Serial.begin(115200);
  delay( 3000 ); // power-up safety delay
  
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  pinMode(ADC_PIN, INPUT);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  // setup the custom effect
//  uint32_t colors[] = {BLUE, YELLOW, RED};
  //uint8_t vuMeterMode = ws2812fx.setCustomMode(F("VU Meter"), vuMeter);
  

  FastLED.show();
}

void loop()
{


  for (int i = 0; i < SAMPLES; i++)
  {
    newTime = micros() - oldTime;
    oldTime = newTime;
    vReal[i] = analogRead(ADC_PIN); // A conversion takes about 1mS on an ESP8266
    vImag[i] = 0;
    while (micros() < (newTime + sampling_period_us))
    {
      delay(0);
    }
  }
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  for (int i = 2; i < (SAMPLES / 2); i++)
  { // Don't use sample 0 and only first SAMPLES/2 are usable. Each array eleement represents a frequency and its value the amplitude.
    if (vReal[i] > 2000)
    { // Add a crude noise filter, 10 x amplitude or more
      if (i <= 2)
        displayBand(0, (int)vReal[i] / amplitude); // 125Hz
      if (i > 2 && i <= 3)
        displayBand(1, (int)vReal[i] / amplitude); // 250Hz
      if (i > 5 && i <= 20)
        displayBand(2, (int)vReal[i] / amplitude); // 500Hz
      if (i > 20)
        displayBand(3, (int)vReal[i] / amplitude); // 2000Hz
    }
  }
  if (millis() % 4 == 0)
  {
    for (byte band = 0; band < NUM_BANDS; band++)
    {
      if (peak[band] > 0)
        peak[band] /= 2;
    }
  } // Decay the peak
  for (byte band = 0; band < NUM_BANDS; band++)
  {
    uint16_t value = peak[band];
    vuMeterBands[band] = value < 1 ? 0 : map(value, 1, amplitude, 0, 255);
  }
  gen_led();
  Serial.println();

  //ws2812fx.service();
}

void gen_led() 
{
    
    int pos = 1;
    for(uint8_t i=0; i<NUM_BANDS; i++) 
    {
        
        //Serial.println(" ");Serial.print(i);Serial.println("+++++++");
        uint8_t scaledBand = (vuMeterBands[i] * bandSize) / 256;
            
        Serial.print(scaledBand);
        Serial.print("\t");

        for(uint16_t j=0; j<bandSize; j++) 
        {
          
            if(j <= scaledBand) {
                if(j < greenpixels) {
                  leds[j+pos] = CRGB::Green; 
                
                  //Serial.print(i);Serial.print('1-');
                  
                }
                else if(j < greenpixels + yellowpixels) {
                  leds[j+pos] = CRGB::Yellow; 
                
                  //Serial.print(i);Serial.print('2-');
                  }
                else {
                  leds[j+pos] = CRGB::Red; 
                
                  }
            } else {
                leds[j+pos] = CRGB::Black; 
                //Serial.print(i);Serial.print('0-');
            }
            
        }
        pos=pos+bandSize;
    }
    Serial.print(" ");Serial.println();
  FastLED.show();  
}
