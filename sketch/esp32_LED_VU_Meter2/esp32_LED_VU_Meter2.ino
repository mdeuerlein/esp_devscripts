#include <arduinoFFT.h>      //https://github.com/kosme/arduinoFFT
#include <FastLED.h>

#define LED_PIN     12
#define LED_COUNT   144
#define LED_BRIGHT  150
#define LED_TYPE    WS2811
#define LED_COLORS GRB

CRGB leds[LED_COUNT];


#define NUM_BANDS  6
#define READ_DELAY 50
#define USE_RANDOM_DATA false
#define SAMPLES 512              //Must be a power of 2
#define SAMPLING_FREQUENCY 40000 //Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT.
#define ADC_PIN A0 // 36 = PIN VP on Lolin D32

arduinoFFT FFT = arduinoFFT();


int amplitude = 200;

unsigned int sampling_period_us;
unsigned long microseconds, newTime, oldTime;

byte      peak[] = {0, 0, 0, 0, 0, 0, 0, 0};
double    vReal[SAMPLES];
double    vImag[SAMPLES];

uint8_t   vuMeterBands[NUM_BANDS];




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
  delay( 1000 );   
  Serial.begin(115200);
  delay( 1000 );   
  
  FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLORS>(leds, LED_COUNT).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  LED_BRIGHT );
  FastLED.show();

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  pinMode(ADC_PIN, INPUT);

}

void loop()
{
    for (int i = 0; i < SAMPLES; i++)
    {
        newTime = micros() - oldTime;
        oldTime = newTime;
        vReal[i] = analogRead(ADC_PIN); 
        vImag[i] = 0;
        while (micros() < (newTime + sampling_period_us))
        {
            
        }
    }
  
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    for (int i = 2; i < (SAMPLES / 2); i++) 
    {
      if (vReal[i] > 1000) {
      if (i > 200)
        displayBand(7, (int)vReal[i] / amplitude); // 16000Hz
      else if (i > 53 && i <= 200)
        displayBand(6, (int)vReal[i] / amplitude); // 8000Hz
      else if (i > 30 && i <= 53)
        displayBand(5, (int)vReal[i] / amplitude); // 4000Hz
      else if (i > 15 && i <= 30)
        displayBand(4, (int)vReal[i] / amplitude); // 2000Hz
      else if (i > 7 && i <= 15)
        displayBand(3, (int)vReal[i] / amplitude); // 1000Hz
      else if (i > 5 && i <= 7)
        displayBand(2, (int)vReal[i] / amplitude); // 500Hz
      
      else if (i >= 2 && i <= 5)
        displayBand(1, (int)vReal[i] / amplitude); // 250Hz
      
      if(i<=3 && i>0) displayBand(0, (int)vReal[i] / amplitude); // 125Hz
      
      
      
    }}


    for (byte band = 0; band < NUM_BANDS; band++)
    {
      if (peak[band] > 0)
        peak[band] /= 2;
    }
  for (byte band = 0; band < NUM_BANDS; band++)
  {
    uint16_t value = peak[band];
    vuMeterBands[band] = value < 1 ? 0 : map(value, 1, 40, 0, LED_COUNT/NUM_BANDS);
    Serial.print(peak[band]);
    Serial.print("\t");
  }
    Serial.println(" ");
    gen_led();
    //ws2812fx.service();
}

void gen_led() 
{
    
    int pos = 1;
    for(uint8_t i=0; i<NUM_BANDS; i++) 
    {
        uint8_t scaledBand = vuMeterBands[i];
        
        for(uint16_t j=0; j<(LED_COUNT/NUM_BANDS)-5; j++) 
        {
          
            if(j <= scaledBand) {
                  leds[j+pos] = CRGB::Green; 
            } else {
                leds[j+pos] = CRGB::Black; 

            }
            
        }
        pos=pos+LED_COUNT/NUM_BANDS;
    }
    Serial.print(" ");Serial.println();
  FastLED.show();  
}
