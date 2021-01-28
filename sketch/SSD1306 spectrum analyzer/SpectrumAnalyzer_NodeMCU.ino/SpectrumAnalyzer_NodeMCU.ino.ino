#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
FASTLED_USING_NAMESPACE
#define DATA_PIN    D3
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    256
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          255


#include <Wire.h>
#include "arduinoFFT.h" // Standard Arduino FFT library
// https://github.com/kosme/arduinoFFT, in IDE, Sketch, Include Library, Manage Library, then search for FFT
arduinoFFT FFT = arduinoFFT();
/////////////////////////////////////////////////////////////////////////
// Comment out the display your nNOT using e.g. if you have a 1.3" display comment out the SSD1306 library and object
// #include "SH1106.h"     // https://github.com/squix78/esp8266-oled-ssd1306
// SH1106 display(0x3c, D3,D4); // 1.3" OLED display object definition (address, SDA, SCL) Connect OLED SDA , SCL pins to ESP SDA, SCL pins

//#include "SSD1306.h"  // https://github.com/squix78/esp8266-oled-ssd1306
//SSD1306 display(0x3c, D3,D4);  // 0.96" OLED display object definition (address, SDA, SCL) Connect OLED SDA , SCL pins to ESP SDA, SCL pins
/////////////////////////////////////////////////////////////////////////
#define SAMPLES 256              //Must be a power of 2
#define SAMPLING_FREQUENCY 8000 //Hz, must be 10000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT.
#define amplitude 75
unsigned int sampling_period_us;
unsigned long microseconds;
byte peak[] = {0,0,0,0,0,0,0};
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime, oldTime;
/////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Serial.println('Starting');
  
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);


//  Wire.begin(D3,D4); // SDA, SCL
//  display.init();
//  display.setFont(ArialMT_Plain_10);
//  display.flipScreenVertically(); // Adjust to suit or remove
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop() {
for(int i = 0; i<=NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow 
  
//  display.clear();
//  display.drawString(0,0,"0.1 0.2 0.5 1K  2K  4K  8K");
  for (int i = 0; i < SAMPLES; i++) {
    newTime = micros()-oldTime;
    oldTime = newTime;
    vReal[i] = analogRead(A0); // A conversion takes about 1mS on an ESP8266
    vImag[i] = 0;
    while (micros() < (newTime + sampling_period_us)) { /* do nothing to wait */ }
  }
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  for (int i = 2; i < (SAMPLES/2); i++){ // Don't use sample 0 and only first SAMPLES/2 are usable. Each array eleement represents a frequency and its value the amplitude.
    if (vReal[i] > amplitude*2) { // Add a crude noise filter, 4 x amplitude or more
      if (i<=4 )             displayBand(0,(int)vReal[i]/(amplitude*4)); // 125Hz
      if (i >4   && i<=7 )  displayBand(1,(int)vReal[i]/(amplitude*2.5)); // 250Hz
      if (i >9  && i<=15 )  displayBand(2,(int)vReal[i]/(amplitude*0.6)); // 500Hz
      if (i >15  && i<=32 )  displayBand(3,(int)vReal[i]/(amplitude*0.5)); // 1000Hz
      if (i >32  && i<=120 ) displayBand(4,(int)vReal[i]/(amplitude*0.4)); // 2000Hz
      //if (i >105 && i<=120 ) displayBand(5,(int)vReal[i]/amplitude); // 4000Hz
      //if (i >120 && i<=146 ) displayBand(6,(int)vReal[i]/amplitude); // 8000Hz
      //Serial.println(i);
    }
    for (byte band = 0; band <= 6; band++) {
  //    display.drawHorizontalLine(18*band,64-peak[band],14);
      // if(band < 5) leds[(band*27)+map(peak[band],0,50,0,27)] = CHSV( 0, 255, 100);

    }
  }
  if (millis()%1 == 0) {for (byte band = 0; band <= 6; band++) {if (peak[band] > 0) peak[band] -= 1;}} // Decay the peak
  FastLED.show();
//  display.display();
 
}

void displayBand(int band, int dsize) 
{
  int dmax = 50;
  if (dsize > dmax) dsize = dmax;

  for (int s = 0; s <= dsize; s++)
  {
  //    display.drawHorizontalLine(18*band,64-s, 14);
      int value = map(s, 0, 50, 1, 7);
      int pos = 0;

      if(band < 5) 
      {
          if( value % 2 == 0) {
              pos = (value * 32) + (32 - 1) - band*6;
          } else {
              pos = (value * 32) + band*6;
          }

          for (int i = 0; i < 5; i++) {
              if( value % 2 == 0) {
                  leds[pos-i] = CHSV( 150+s*2.3, 255, 100+s*2);
              } else {
                  leds[pos+i] = CHSV( 150+s*2.3, 255, 100+s*2);
              }
          }
      }
   }
   if (dsize > peak[band]) {peak[band] = dsize;}
   Serial.println(analogRead(A0));
}
