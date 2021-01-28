#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    D2
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    2
#define BRIGHTNESS  255
int bright = 0;
CRGB leds[NUM_LEDS];

uint8_t gHue = 0;

void startLED() {
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    for(int i = 0; i < NUM_LEDS; i++) 
    {
        fadeToBlackBy( leds, NUM_LEDS, 10);
        leds[i] += CRGB::Red;
        FastLED.show(); 
        delay(2);
    }
    for(int i = NUM_LEDS; i > 0; i--) 
    {
        fadeToBlackBy( leds, NUM_LEDS, 10);
        leds[i] += CRGB::Green;
        FastLED.show(); 
        delay(2);
    }
      fadeToBlackBy( leds, NUM_LEDS, 100);
      FastLED.show(); 
      delay(50);
        leds[NUM_LEDS] += CRGB::Black;
      FastLED.show(); 
        leds[0] += CRGB::Red;
        leds[1] += CRGB::Green;
        leds[2] += CRGB::Yellow;
        FastLED.show(); 
        delay(3000);



}
