/* ESP8266/32 Audio Spectrum Analyser on an SSD1306/SH1106 Display
 * The MIT License (MIT) Copyright (c) 2017 by David Bird. 
 * The formulation and display of an AUdio Spectrum using an ESp8266 or ESP32 and SSD1306 or SH1106 OLED Display using a Fast Fourier Transform
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, but not to use it commercially for profit making or to sub-license and/or to sell copies of the Software or to 
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:  
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 * See more at http://dsbird.org.uk 
*/
#include <FastLED.h>

#define LED_PIN     12
#define LED_COUNT   93
#define LED_BRIGHT  105
#define LED_TYPE    WS2811
#define LED_COLORS GRB

CRGB leds[LED_COUNT];


#include <Wire.h>
#include "arduinoFFT.h" // Standard Arduino FFT library 
// https://github.com/kosme/arduinoFFT, in IDE, Sketch, Include Library, Manage Library, then search for FFT
arduinoFFT FFT = arduinoFFT();
/////////////////////////////////////////////////////////////////////////
// Comment out the display your nNOT using e.g. if you have a 1.3" display comment out the SSD1306 library and object
#include "SH1106.h"     // https://github.com/squix78/esp8266-oled-ssd1306
SH1106 display(0x3c, 21,22); // 1.3" OLED display object definition (address, SDA, SCL) Connect OLED SDA , SCL pins to ESP SDA, SCL pins

/////////////////////////////////////////////////////////////////////////
#define SAMPLES 512              // Must be a power of 2
#define SAMPLING_FREQUENCY 40000 // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define amplitude 200            // Depending on your audio source level, you may need to increase this value
unsigned int sampling_period_us;
unsigned long microseconds;
byte peak[] = {0,0,0,0,0,0,0};
byte maxpeak[] = {0,0,0,0,0,0,0};
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime, oldTime;
int avg=0;
int maxval = 0;
/////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  esp_log_level_set("gpio", ESP_LOG_WARN);
  Wire.begin(5,4); // SDA, SCL
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLORS>(leds, LED_COUNT).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  LED_BRIGHT );
  FastLED.show();
  display.init();
  display.setFont(ArialMT_Plain_10);
    display.clear();
  display.drawString(0,0,"starting....");
  display.display();
delay(500);
    display.clear();
    display.display();

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void fx1_high (int peak)  
{
        display.drawHorizontalLine(0,0,10);
    display.drawHorizontalLine(0,1,10);

    int gain = map(peak, 0,250,0,4);
    int pos = random8(LED_COUNT);
    if (pos > LED_COUNT-gain) { pos = LED_COUNT-gain;}
    for (int i = 0; i<=gain; i++) {
        leds[ pos+i ] = CHSV( 210+random8(10), 255, map(peak, 0,250,0,250));
        
    }
    
}
void fx1_mid (int peak)  
{
        display.drawHorizontalLine(18*2,0,10);
    display.drawHorizontalLine(18*2,1,10);

    int gain = map(peak, 0,250,0,4);
    int pos = random8(LED_COUNT);
    if (pos > LED_COUNT-gain) { pos = LED_COUNT-gain;}
    for (int i = 0; i<=gain; i++) {
    leds[ pos+1 ] = CHSV( 180+random8(10), 255, map(peak, 0,250,0,250));
    }
    
}
void fx1_low (int peak)  
{
    
        display.drawHorizontalLine(18*4,0,10);
    display.drawHorizontalLine(18*4,1,10);

    int gain = map(peak, 0,250,0,4);
    int pos = random8(LED_COUNT);
    if (pos > LED_COUNT-gain) { pos = LED_COUNT-gain;}

    for (int i = 0; i<=gain; i++) {
        leds[ pos+i ] = CHSV( 160+random8(10), 250, map(peak, 0,250,0,200));
    }
}
void fx1_lowest (int peak) 
{
      display.drawHorizontalLine(18*6,0,10);
    display.drawHorizontalLine(18*6,1,10);

    int gain = map(peak, 0,250,0,6);
    int pos = random16(LED_COUNT);
    if (pos > LED_COUNT-gain) { pos = LED_COUNT-gain;}
    for (int i = 0; i<=gain; i++) {
        leds[ pos+i ] = CHSV( 140, 250, map(peak, 0,250,0,180));
    }
    
    
}

void loop() {
  display.clear();
  //display.drawString(0,0,"0.1 0.2 0.5 1K  2K  4K  8K");
  int avg =0;
  for (int i = 0; i < SAMPLES; i++) {
    newTime = micros();
    vReal[i] = analogRead(A0); // A conversion takes about 1uS on an ESP32
    vImag[i] = 0;
    while ((micros() - newTime) < sampling_period_us) {
      // do nothing to wait
    }
  }
  
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  for (int i = 2; i < (SAMPLES/2); i++){ // Don't use sample 0 and only first SAMPLES/2 are usable. Each array eleement represents a frequency and its value the amplitude.
    
    if (vReal[i] > 2000) { // Add a crude noise filter, 10 x amplitude or more
      if (i <=2 )             displayBand(0,(int)vReal[i]/1000); // 125Hz
      else if (i <=4 )             displayBand(1,(int)vReal[i]/800); // 250Hz
      else if (i <=5   )   displayBand(2,(int)vReal[i]/500); // 500Hz
      else if (i <=12 )  displayBand(3,(int)vReal[i]/400); // 1000Hz
      else if (i <=14 )  displayBand(4,(int)vReal[i]/400); // 2000Hz
      else if (i <=24 )  displayBand(5,(int)vReal[i]/600); // 4000Hz
      else if (i <=48 ) displayBand(6,(int)vReal[i]/400); // 8000Hz
      
      //Serial.println(i);
    }
    
    for (byte band = 0; band <= 6; band++) display.drawHorizontalLine(18*band,64-peak[band],10);
  }
  if (millis()%1 == 0) {
    for (byte band = 0; band <= 6; band++) {
      if (peak[band] > 0) peak[band] -= 1;
      
    }
  }
  

  int curr_avg=0;
  //display.drawString(0,0,String(maxpeak[0]));
  //display.drawString(90,0,String(maxpeak[5]));
    fadeToBlackBy( leds, LED_COUNT, 80);
    FastLED.show(); 
         if(maxpeak[0]>25) fx1_high(maxpeak[0]);
         if(maxpeak[2]>25) fx1_mid(maxpeak[2]);
         if(maxpeak[4]>25) fx1_low(maxpeak[4]);
         if(maxpeak[6]>25) fx1_lowest(maxpeak[6]);
         FastLED.show(); 

  for(int i = 0; i<= 6;i++) {
    if(maxval< maxpeak[i]) maxval = maxpeak[i];
    
    curr_avg += maxpeak[i];
    Serial.print(maxpeak[i]);Serial.print(" ");
    maxpeak[i] =0;
  }
  Serial.print(curr_avg);

  display.display();
    
    Serial.println(" ");
}

void displayBand(int band, int dsize){
  
  
  int dmax = 50;
  if (dsize > dmax) dsize = dmax;
  //if (band == 7) display.drawHorizontalLine(18*6,0, 18);
  for (int s = 0; s <= dsize; s=s+2){display.drawHorizontalLine(18*band,64-s, 10);
    maxpeak[band]++;
  }
  if (dsize > peak[band]) {peak[band] = dsize;}
}
