#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    12
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    93
#define ANALOG_THRESHOLD 680
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          255


uint8_t gHue = 0;

void setup() {
  Serial.begin(115200);
   delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  EVERY_N_MILLISECONDS( 50 ) { gHue++; }
  int value = analogRead(A0);
  value = value + analogRead(A0);
  value= value/2;
  value= map(value, 0, 4095, 0, 1023);
  Serial.println(value);
  
  int showleds= map(value, 0, 1023, 0, 144);
  if(value > ANALOG_THRESHOLD) {
     
    confetti(map(value, 0, 1023, 0, 255+10));
  } else {
    addGlitter(map(value, 0, 1023, 0, 255)+20,map(value, 0, 1023, 0, 20));
    }
 FastLED.setBrightness(map(value, 0, 1023, 0, 255+10));
 
 FastLED.show(); 
}
void confetti(int bright) 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  if (pos > 90) { pos = 90;}
  for (int i = 0; i < 4; i++) {
    leds[ pos+i ] += CHSV( 210 + random8(64), 255, 255);
  }
}

void addGlitter( int bright, fract8 chanceOfGlitter) 
{
 if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CHSV( 150 + random8(64), 255, 100);
    
    fadeToBlackBy( leds, NUM_LEDS, 10);
 } else{fadeToBlackBy( leds, NUM_LEDS, 5);}
}
