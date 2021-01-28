
// -- DISPLAY SETTINGS ------ //

#include "SH1106.h"     // https://github.com/squix78/esp8266-oled-ssd1306
SH1106 display(0x3c, 21,22); // 1.3" OLED display object definition (address, SDA, SCL) Connect OLED SDA , SCL pins to ESP SDA, SCL pins

// -- LED SETTINGS --------- //

#include <FastLED.h>
#define LED_PIN     12
#define LED_COUNT   93
#define LED_BRIGHT  250
#define LED_TYPE    WS2811
#define LED_COLORS GRB

CRGB leds[LED_COUNT];

int avg_peak=0;
int fade_value=20;

// -- SOUND SETTINGS ------- //

#include <Wire.h>
#include "arduinoFFT.h" // https://github.com/kosme/arduinoFFT,

#define SAMPLES 512              // Must be a power of 2
#define SAMPLING_FREQUENCY 40000 // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define amplitude 200            // Depending on your audio source level, you may need to increase this value

arduinoFFT FFT = arduinoFFT();

unsigned int  sampling_period_us;
unsigned long microseconds;

byte peak[]    = {0,0,0,0,0,0,0};
byte maxpeak[] = {0,0,0,0,0,0,0};
byte maxmax[]  = {0,0,0,0,0,0,0};
byte maxval[]  = {0,0,0,0,0,0,0};
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime, oldTime;



void setup() 
{
    Serial.begin(115200);
    Wire.begin(5,4); // SDA, SCL ?????

    delay(500);
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

void fx_bass (int peak,int band)  
{
    display.drawHorizontalLine(18*band,0,10);
    display.drawHorizontalLine(18*band,1,10);

    int gain = 1;
    int pos = random8(LED_COUNT);

    pos = (pos >= LED_COUNT-gain) ? LED_COUNT-gain-1 : pos;
    
    for (int i = 0; i<gain; i++) 
    {
        leds[ pos+i ] = CHSV( 210+random8(30), 255, 120+random8(80));
    }
    addGlitter(10);
    addBluedots(20);
}

void fx_low (int peak,int band)  
{
    display.drawHorizontalLine(18*band,0,10);
    display.drawHorizontalLine(18*band,1,10);

    int gain = 1;//map(peak, 0,50,0,2);
    

    
    for (int i = 0; i<gain; i++) 
    {
       leds[ random16(LED_COUNT) ] = CHSV( 190+random8(15), 255, 100+random8(15));
    }
    
}

void fx_mid (int peak, int band)  
{
    display.drawHorizontalLine(18*band,0,10);
    display.drawHorizontalLine(18*band,1,10);

    int gain = random8(3);//map(peak, 0,50,1,4);
    int pos = random8(LED_COUNT);
        
    pos = (pos >= LED_COUNT-gain) ? LED_COUNT-gain-1 : pos;

    for (int i = 0; i<gain; i++) 
    {
        leds[ pos+i ] = CHSV( 170-random8(22), 250, 100+random8(15));
    }
}

void fx_high (int peak,int band) 
{
    
    display.drawHorizontalLine(18*band,0,10);
    display.drawHorizontalLine(18*band,1,10);

    int gain = random8(3);//map(peak, 0,50,1,6);
    for (int i = 0; i<=gain; i++) 
    {
        leds[ random16(LED_COUNT) ] = CHSV( 150+random8(20), 250, 80+random8(20));
    }
    
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(LED_COUNT) ] = CHSV( 145+random8(40), 255, random8(70));
  }
}

void addBluedots( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(LED_COUNT) ] = CHSV( 160, 255, random8(80));
  }
}
void loop() 
{
    display.clear();
    //display.drawString(0,0,"0.1 0.2 0.5 1K  2K  4K  8K");

    for (int i = 0; i < SAMPLES; i++) 
    {
        newTime = micros();
        vReal[i] = analogRead(A0); // A conversion takes about 1uS on an ESP32
        vImag[i] = 0;
        while ((micros() - newTime) < sampling_period_us) 
        {
            // do nothing to wait
        }
    }
  
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  
    for (int i = 2; i < (SAMPLES/2); i++) // Don't use sample 0 and only first SAMPLES/2 are usable. Each array eleement represents a frequency and its value the amplitude.
    { 
        if (vReal[i] > 2000)  // Add a crude noise filter, 10 x amplitude or more
        {
                 if (i <=2 ) displayBand(0,(int)vReal[i]/950); // 125Hz
            else if (i <=4 ) displayBand(1,(int)vReal[i]/750); // 250Hz
            else if (i <=5 ) displayBand(2,(int)vReal[i]/280); // 500Hz
            else if (i <=12) displayBand(3,(int)vReal[i]/800); // 1000Hz
            else if (i <=14) displayBand(4,(int)vReal[i]/300); // 2000Hz
            else if (i <=24) displayBand(5,(int)vReal[i]/700); // 4000Hz
            else if (i <=48) displayBand(6,(int)vReal[i]/600); // 8000Hz
        }

        for (byte band = 0; band <= 6; band++) display.drawHorizontalLine(18*band,64-peak[band],10);
    }

    if (millis()%1 == 0) 
    {
        for (byte band = 0; band <= 6; band++) 
        {
            if (peak[band] > 0) peak[band] -= 1;
        }
    }

    maxval[0] = map(maxpeak[0], 0, 29, 0, 50);
    maxval[1] = map(maxpeak[1], 0,  55, 0, 50);
    maxval[2] = map(maxpeak[2], 0,  29, 0, 50);
    maxval[3] = map(maxpeak[3], 0, 140, 0, 50);
    maxval[4] = map(maxpeak[4], 0,  55, 0, 50);
    maxval[5] = map(maxpeak[5], 0, 135, 0, 50);
    maxval[6] = map(maxpeak[6], 0, 160, 0, 50);

    fadeToBlackBy( leds, LED_COUNT, fade_value);
    Serial.print(fade_value);Serial.print(" ");
    if(maxval[0]>45 || maxval[1]>40) 
    {
        fade_value = (fade_value > 80) ? 80 : fade_value + 8;
    } else {
        fade_value = (fade_value < 20) ? 20 : fade_value - 5;
    }
    //Serial.print(fade_value);Serial.print(" ");

    
    if(maxval[0]>30) fx_bass(maxval[0],0);
    if(maxval[1]>40) fx_bass(maxval[1],1);
    if(maxval[2]>30) fx_mid(maxval[2],2);
    if(maxval[3]>30) fx_mid(maxval[3],3);
    if(maxval[4]>20) fx_mid(maxval[4],4);
    if(maxval[5]>20) fx_high(maxval[5],5);
    if(maxval[6]>20) fx_high(maxval[6],6);
    if(maxval[6]>50) addGlitter(40);
    addBluedots(50);

    FastLED.show();
    display.display();
    int avg_val = 0;
    for(int i = 0; i<= 6;i++) 
    {
      avg_val += maxval[i];
      Serial.print(maxpeak[i]);
      Serial.print(" ");
      maxpeak[i] =0;
      
    }
      avg_peak = (avg_peak*50 + avg_val)/51;
      
    
    Serial.println(" ");
}

void displayBand(int band, int dsize)
{
    int dmax = 50;
    dsize = (dsize > dmax) ? dmax : dsize;
    for (int s = 0; s <= dsize; s=s+2)
    {
        display.drawHorizontalLine(18*band,64-s, 10);
        maxpeak[band]++;
    }
    if (dsize > peak[band]) peak[band] = dsize;
}
