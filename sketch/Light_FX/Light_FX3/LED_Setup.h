#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    D4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS   93
#define BRIGHTNESS  100

CRGB leds[NUM_LEDS];

uint8_t gHue = 0;

void startLED() {
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    for(int i = 0; i < NUM_LEDS; i++) 
    {
        
        leds[i] += CRGB::Red;
        FastLED.show(); 
        delay(1);
    }
      delay(500);
    for(int i = 0; i < NUM_LEDS; i++) 
    {
        
        leds[i] += CRGB::Black;
        FastLED.show(); 
        delay(1);
    }
      delay(500);

}
