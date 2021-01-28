
// -- DISPLAY SETTINGS ------ //


// -- LED SETTINGS --------- //

#include <FastLED.h>
#define LED_PIN     D2
#define LED_COUNT   6
#define LED_BRIGHT  250
#define LED_TYPE    WS2811
#define LED_COLORS RGB

CRGB leds[LED_COUNT];

int avg_peak=0;
int fade_value=20;

// -- SOUND SETTINGS ------- //

#include <Wire.h>
#include "arduinoFFT.h" // https://github.com/kosme/arduinoFFT,

#define SAMPLES 256              // Must be a power of 2
#define SAMPLING_FREQUENCY 5000 // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define amplitude 200            // Depending on your audio source level, you may need to increase this value

arduinoFFT FFT = arduinoFFT();

unsigned int  sampling_period_us;
unsigned long microseconds;

byte peak[]    = {0,0,0,0,0,0,0};
byte maxpeak[] = {0,0,0,0,0,0,0};
byte curval[]  = {0,0,0,0,0,0,0};

int cur_avg =0;

double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime, oldTime;



void setup() 
{
    Serial.begin(115200);

    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLORS>(leds, LED_COUNT);
    FastLED.setBrightness(  LED_BRIGHT );
    FastLED.show();
    sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void fx_bass (int peak,int band)  
{
    
    

 leds[ 1 ] = CRGB::Red;
 leds[ 0 ] = CRGB::Red;
}

void fx_low (int peak,int band)  
{
 leds[ 1 ] = CHSV( 210+random8(30), 255, 120+random8(80));
 leds[ 0 ] = CHSV( 210+random8(30), 255, 10+random8(80));
    
}

void fx_mid (int peak, int band)  
{
 leds[ 1 ] = CHSV( 170+random8(30), 255, 120+random8(80));
 leds[ 0 ] = CHSV( 170+random8(30), 255, 120+random8(80));
}

void fx_high (int peak,int band) 
{
    
 leds[ 1 ] = CHSV( 210+random8(30), 255, 20+random8(80));
 leds[ 0 ] = CHSV( 210+random8(30), 255, 20+random8(80));
}


void addBluedots( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(LED_COUNT) ] = CHSV( 160, 255, random8(80));
  }
}
void loop() 
{
    
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
        if (vReal[i] > 1000)  // Add a crude noise filter, 10 x amplitude or more
        {

                 if (i <=2 ) peak[0]=(peak[0]+(int)vReal[i]/40)/2;
            else if (i <=4 ) peak[1]=(peak[1]+(int)vReal[i]/44)/2;
            else if (i <=5 ) peak[2]=(peak[2]+(int)vReal[i]/8)/2;
            else if (i <=12) peak[3]=(peak[3]+(int)vReal[i]/16)/2;
            else if (i <=14) peak[4]=(peak[4]+(int)vReal[i]/8)/2;
            else if (i <=24) peak[5]=(peak[5]+(int)vReal[i]/8)/2;
            else if (i <=48) peak[6]=(peak[6]+(int)vReal[i]/7)/2;
        }

        
    }
int cur_val=0;
    for(int i = 0; i<= 6;i++) 
    {
        if(peak[i]>maxpeak[i]) maxpeak[i] = peak[i];
        if(peak[i]>0) {
          curval[i] = map(peak[i], 0, maxpeak[i], 0, 255);
        } else { curval[i] =20;}
        
        cur_val+=peak[i];
        peak[i] =0;
        //Serial.print(curval[i]);
        // Serial.print(" "); 
      
    }
    cur_val/=7;
    cur_avg=(cur_avg*5+cur_val)/6;
    Serial.print(cur_avg);
        Serial.print(" "); 
      leds[ 0 ] =CRGB::DarkBlue;
      leds[ 1 ] =CRGB::DarkBlue;
      leds[1].fadeToBlackBy(180);
      leds[0].fadeToBlackBy(180);
      
      
      FastLED.show();
      leds[ 1 ] += CHSV( 170+random16(5), 255, curval[2]);
      leds[ 0 ] += CHSV( 170+random16(5), 255, curval[3]);
      if(curval[0]>100) leds[ 0 ] += CHSV( 210+random16(5), 255, curval[0]);
      if(curval[1]>150) leds[ 1 ] += CHSV( 210+random16(5), 255, curval[1]);
      if(curval[1]>230) leds[ 1 ] =CRGB::DeepPink;
      if(curval[0]>230) leds[ 0  ] =CRGB::DarkViolet;
  
     
     FastLED.show();


    
    Serial.println(" ");
}

void displayBand(int band, int dsize)
{
    int dmax = 250;
    dsize = (dsize > dmax) ? dmax : dsize;
    for (int s = 0; s <= dsize; s=s+2)
    {
        maxpeak[band]++;
    }
    if (dsize > peak[band]) peak[band] = dsize;
}
