#include <FastLED.h>
FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
  #warning "Requires FastLED 3.1 or later!"
#endif

// BASE CONFIGURATION
const int Poti_PIN = 34;

#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    256
#define BRIGHTNESS  250


CRGB leds[NUM_LEDS];

// EFFECT SETTINGS
uint8_t effect_color    = 0; 
uint8_t effect_delay    = 4155;

uint8_t addPixel_count  = 3;
uint8_t addPixel_chance = 60;
uint8_t fadeOutBy_value = 7; 


void setup() {
  Serial.begin(9600);
  delay(1000); 
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

  
void loop() {

  // add and fade pixel
  int PotiData = analogRead(Poti_PIN);

  if(PotiData>500) {addPixel_count = 1;}
  if(PotiData>1000) {addPixel_count = 2;}
  if(PotiData>1500) {addPixel_count = 3;}
  if(PotiData>2000) {addPixel_count = 4;}
  if(PotiData>2500) {addPixel_count = 5;}
  if(PotiData>3000) {addPixel_count = 6;}
  if(PotiData>3500) {addPixel_count = 7;}
  if(PotiData>4000) {addPixel_count = 8;}
  Serial.println(addPixel_count);
  EVERY_N_MILLISECONDS( effect_delay ) { 
    addPixel();
    fadeToBlackBy( leds, NUM_LEDS, fadeOutBy_value);
    FastLED.show();

  }

  // cycle the effect_color through the rainbow
  EVERY_N_MILLISECONDS( 300 ) { 
      effect_color++; 
  } 

}
 
void addPixel() 
{
   // do for the defined count of pixels
   for( int i = 0; i < addPixel_count; i++) 
   { 
       // chance of Pixel to be added
       if( random8() < addPixel_chance) 
       {
           leds[random16(NUM_LEDS)] += CHSV( effect_color + random8(-5,15), 200, random8(50,BRIGHTNESS));
       }
   }
}
