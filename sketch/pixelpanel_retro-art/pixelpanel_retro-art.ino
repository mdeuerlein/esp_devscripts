#include <avr/pgmspace.h>  // Needed to store stuff in Flash using PROGMEM
#include <FastLED.h>
//#include <Adafruit_NeoPixel.h>

/** BASIC CONFIGURATION  **/
#define BRIGHTNESS        100
#define FRAMES_PER_SECOND  60
#define LED_PIN 2

const int     Button_PIN = 15;
const uint8_t kMatrixWidth  = 16;
const uint8_t kMatrixHeight = 16;
const bool    kMatrixSerpentineLayout = true;

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)

// Create the array of retro arcade characters and store it in Flash memory
const long DigDug01[] PROGMEM =
{
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 
0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x0066cc, 0x000000, 0x0066cc, 0x000000, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 
0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0x000000, 0x0066cc, 0x000000, 0x0066cc, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 
0x000000, 0x000000, 0x000000, 0x0066cc, 0x0066cc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0xff0000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0xff0000, 0xff0000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x0066cc, 0x0066cc, 0xcccccc, 0x000000, 0x000000, 
0x000000, 0xff0000, 0xff0000, 0xff0000, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 
0x000000, 0x000000, 0xff0000, 0xff0000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0x0066cc, 0x0066cc, 0x0066cc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000,  
0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0xff0000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 
0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};

const long DigDug02[] PROGMEM =
{
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 
0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x0066cc, 0x000000, 0x0066cc, 0x000000, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000,  
0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0x000000, 0x0066cc, 0x000000, 0x0066cc, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 
0x000000, 0x000000, 0x000000, 0x0066cc, 0x0066cc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0xff0000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x0066cc, 0x0066cc, 0xcccccc, 0x000000, 0x000000, 
0x000000, 0xff0000, 0xff0000, 0xff0000, 0x0066cc, 0x0066cc, 0x0066cc, 0x0066cc, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 
0x000000, 0x000000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0x0066cc, 0x0066cc, 0x0066cc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000,  
0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};

const long Qbert01[] PROGMEM =
{
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
0x000000, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xffffcc, 0xffffcc, 0xff0033, 0xffffcc, 0xffffcc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 
0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033,  
0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 
0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0x000000, 0xff0033, 0xff0033, 0x000033, 0x000033, 0xff6600, 0x000000, 
0x000000, 0xff0033, 0x000033, 0x000033, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0x000000
};

const long Qbert02[] PROGMEM =
{
0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
0x000000, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xffffff, 0xffffff, 0xff0033, 0xffffff, 0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0xff0033, 0x000000, 
0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 
0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff0033,
0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 0xff6600, 0x000000, 
0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0x000000
};

const long BombJack01[] PROGMEM =
{
0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x0099ff, 0x333366, 0x333366, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x333366, 0x333366, 0x0099ff, 0x333366, 0x333366,
0x333366, 0x333366, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x0099ff, 0x0099ff, 0x0099ff, 0xffffff, 0xffffff, 0x0099ff, 0xffffff, 0xffffff, 0x0099ff, 0x0099ff, 0x0099ff, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x0099ff, 0x0099ff, 0xffffff, 0x000000, 0x0099ff, 0x000000, 0xffffff, 0x0099ff, 0x0099ff, 0x333366, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x0099ff, 0xffffff, 0x000000, 0x0099ff, 0x000000, 0xffffff, 0x0099ff, 0x333366, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0xffcc99, 0xffcc99, 0xffcc99, 0xffcc99, 0xffcc99, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0xffffff, 0xffcc99, 0xffcc99, 0xffcc99, 0xffcc99, 0xffcc99, 0xffffff, 0x333366, 0x333366, 0x333366, 0x333366,
0x333366, 0x333366, 0x333366, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0x333366, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0xff0000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x333366, 0x333366, 
0x333366, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x333366, 0x333366, 
0x333366, 0x333366, 0x000000, 0x000000, 0xffffff, 0x0099ff, 0x0099ff, 0x0099ff, 0xffff00, 0x0099ff, 0x0099ff, 0x0099ff, 0xffffff, 0x000000, 0x000000, 0x333366, 
0x333366, 0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0xffffff, 0x333366, 0x333366, 
0x333366, 0x333366, 0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0xffffff, 0x333366,  
0x333366, 0x333366, 0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xffffff, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x000000, 0x000000, 0x000000, 0x333366, 0x000000, 0x000000, 0x000000, 0x333366, 0x333366, 0x333366, 0x333366
};

const long BombJack02[] PROGMEM =
{
0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x0099ff, 0x333366, 0x333366, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x333366, 0x333366, 0x0099ff, 0x333366, 0x333366, 
0x333366, 0x333366, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x0099ff, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x0099ff, 0x0099ff, 0x0099ff, 0xffffff, 0x000000, 0x0099ff, 0x000000, 0xffffff, 0x0099ff, 0x0099ff, 0x0099ff, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x0099ff, 0x0099ff, 0xffffff, 0x000000, 0x0099ff, 0x000000, 0xffffff, 0x0099ff, 0x0099ff, 0x333366, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0x000000, 0x000000, 0x333366, 0x0099ff, 0xffffff, 0xffffff, 0xffcc99, 0xffffff, 0xffffff, 0x0099ff, 0x333366, 0x000000, 0x000000, 0x333366,
0x333366, 0x000000, 0x000000, 0xff0000, 0xffcc99, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xffcc99, 0xff0000, 0x000000, 0x000000, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0xff0000, 0xff0000, 0xffffff, 0xffcc99, 0xffcc99, 0xffcc99, 0xffcc99, 0xffcc99, 0xffffff, 0xff0000, 0xff0000, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xffffff, 0x333366, 0x333366, 0x333366, 
0x333366, 0x333366, 0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0x000000, 0xff0000, 0x000000, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0x333366, 0x333366, 
0x333366, 0x333366, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0xffffff, 0x333366, 0x333366, 
0x333366, 0x333366, 0xffffff, 0xffffff, 0xffffff, 0x0099ff, 0x0099ff, 0x0099ff, 0xffff00, 0x0099ff, 0x0099ff, 0x0099ff, 0xffffff, 0xffffff, 0xffffff, 0x333366,
0x333366, 0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x333366, 
0x333366, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 
0x333366, 0x333366, 0x333366, 0xffffff, 0xffffff, 0xff0000, 0xff0000, 0xffffff, 0xff0000, 0xff0000, 0xffffff, 0x333366, 0xffffff, 0xffffff, 0x333366, 0x333366, 
0x333366, 0x333366, 0x333366, 0x333366, 0x333366, 0x000000, 0x000000, 0x000000, 0x333366, 0x000000, 0x000000, 0x000000, 0x333366, 0x333366, 0x333366, 0x333366
};

// Pattern Setting
// Lists of pattern functions
typedef void (*SimplePatternList[])();
long randNumber;
// fx1 
// fx2_blobby_flow
// fx3 = blur
// fx4 matrix_sinelon

// Current Pattern
uint8_t gCurrentPatternNumber = 0; 


// The 16 bit version of our coordinates
static uint16_t x;
static uint16_t y;
static uint16_t z;

uint16_t speed = 6; // Speed (1-60) is set dynamically once we've started up
uint16_t scale = 30; // scale (Zoomed in = 1)  set dynamically once we've started up
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION]; // noise value array

CRGBPalette16 currentPalette( PartyColors_p );
uint8_t       colorLoop = 1;

// x,y, & time values
uint32_t v_time,hue_time,hxy;

// how many octaves to use for the brightness and hue functions
uint8_t octaves=1;
uint8_t hue_octaves=3;

// the 'distance' between x/y points for the hue noise
int hue_scale=1;

// how fast we move through time & hue noise
int time_speed=100;
int hue_speed=10;

// adjust these values to move along the x or y axis between frames
int x_speed=331;
int y_speed=1111;

// the 'distance' between points on the x and y axis
int xscale=57771;
int yscale=57771;

void blackout();
int oldMode = 0;  // assume switch closed because of pull-down resistor

CRGB leds[NUM_LEDS];



// FOR SYLON ETC
uint8_t thisbeat =  23;
uint8_t thatbeat =  28;
uint8_t thisfade =   2;                                     // How quickly does it fade? Lower = slower fade rate.
uint8_t thissat = 255;                                     // The saturation, where 255 = brilliant colours.
uint8_t thisbri = 255; 
int    myhue =   0;

//FOR JUGGLE
uint8_t numdots = 4;                                          // Number of dots in use.
uint8_t faderate = 2;                                         // How long should the trails be. Very low value = longer trails.
uint8_t hueinc = 16;                                          // Incremental change in hue between each dot.
uint8_t thishue = 0;                                          // Starting hue.
uint8_t curhue = 0; 
uint8_t thisbright = 255;                                     // How bright should the LED/display be.
uint8_t basebeat = 5; 
uint8_t max_bright = 255;

// Twinkle
float redStates[NUM_LEDS];
float blueStates[NUM_LEDS];
float greenStates[NUM_LEDS];
float Fade = 0.96;

//For Fireplace
CRGBPalette16 gPal;
#define FPS 48
#define FPS_DELAY 1000/FPS
#define COOLING 20  
#define HOT 100
#define MAXHOT HOT*kMatrixHeight

uint8_t gHue = 0; // rotating "base color" used by many of the patterns



///////Setup Function running when turned on

void setup() 
{
    Serial.begin(115200);
    Serial.println("Starting Setup");

    randomSeed(analogRead(0));

    // Connect 3.3V to AREF pin for any microphones using 3.3V    
    // analogReference(EXTERNAL);                                  

    // Init Push Button
    pinMode(Button_PIN, INPUT);

    // init  & Test LEDs
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    
    for (int i = 0; i < NUM_LEDS; i++) 
        leds[i] = CRGB(70, 70, 70);
    FastLED.show(); 

    // Initialize our coordinates to some random values
    x = random16(); y = random16(); z = random16();
    delay(1000);  
}


void loop ()
{
  // PUSHBUTTON
  int BtnState = digitalRead(Button_PIN);

  if ( BtnState == HIGH )
  {
    Serial.println("### BUTTON-PUSHED ###");
    if (oldMode == 13) { 
        oldMode = 0; 
    } else { 
        fadeToBlackBy( leds, NUM_LEDS, 25); 
        delay(500);
        oldMode++; 
    }
  }

  // switch patterbn
  switch(oldMode) {
    case 0:
        fadeToBlackBy( leds, NUM_LEDS, 25);
        blackout();
        break;
    case 1:
        solid_red();
        break;
    case 2:
        solid_warmwhite();
        break;
    case 3:
        solid_maxwhite();
        break;
    case 4:
        fx1();
        break;    
    case 5:
        fx2();
        break;
    case 6:
        fx3();
        break;;
    case 7:
        fx4();
        break;;
    case 8:
        fx5();
        break;
    case 9:
        fx6();
        break;
    case 10:
        fx7();
        break;
      case 11:
        fx8();
        break;
      case 12:
        fx9();
        break;
      case 13:
        fx10();
        break;
    default:
        blackout();
        break;
  }
}


//////////////////////////////////////////////

void solid_red() 
{
    Serial.println("sold_red");
    for (int i =0; i < NUM_LEDS; i++) 
        leds[i] = CHSV (0, 250, 100);
    FastLED.show();
    delay(500);
}

void solid_warmwhite() 
{
    Serial.println("solid_warmwhite");
    for (int i =0; i < NUM_LEDS; i++) 
        leds[i] = CRGB(255, 172, 68);
    FastLED.show();
    delay(500);
}


void blackout() 
{
    Serial.println("Blackout");
    for (int i =0; i < NUM_LEDS; i++) 
        leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(500);
}

void solid_maxwhite() 
{
    Serial.println("Maxium White");
    for (int i =0; i < NUM_LEDS; i++) 
        leds[i] = CRGB(255, 255, 255);
    FastLED.show();
    delay(500);
}

void fx1() 
{
    Serial.println("FX1: Matrix / Booby Flow");
    fill_2dnoise16(LEDS.leds(), 
        kMatrixWidth, kMatrixHeight, kMatrixSerpentineLayout,
        octaves,x,xscale,y,yscale,v_time,
        hue_octaves,hxy,hue_scale,hxy,hue_scale,hue_time, false
    );
    LEDS.show();
  
    x += x_speed;
    y += y_speed;
    v_time += time_speed;
    hue_time += hue_speed;
}


void fx2()
{
    Serial.println("FX 2: Matrix / Booby Flow");
  
    // generate noise data
    fillnoise8(); 
    get_noise(); // convert the noise data to colors from current palette

    LEDS.show();
}


void fx3() 
{
    Serial.println("FX 3: Blur");
    EVERY_N_MILLISECONDS(40) 
    {
        uint8_t blurAmount = dim8_raw( beatsin8(3,64, 192) );       // A sinewave at 3 Hz with values ranging from 64 to 192.
        blur1d( leds, NUM_LEDS, blurAmount);                        // Apply some blurring to whatever's already on the strip, which will eventually go black.
        uint8_t  i = beatsin8(  9, 0, NUM_LEDS-1);
        uint8_t  j = beatsin8( 7, 0, NUM_LEDS-1);
        uint8_t  k = beatsin8(  5, 0, NUM_LEDS-1);
  
        // The color of each point shifts over time, each at a different speed.
        uint16_t ms = millis();  
        leds[(i+j)/2] = CHSV( ms / 29, 200, 255);
        leds[(j+k)/2] = CHSV( ms / 41, 200, 255);
        leds[(k+i)/2] = CHSV( ms / 73, 200, 255);
        leds[(k+i+j)/3] = CHSV( ms / 53, 200, 255);
        FastLED.show();
    }
 
}


//////Matrix Sinelon
void fx4() 
{
    Serial.println("fx4 matrix_sinelon");
    
    fadeToBlackBy( leds, NUM_LEDS, 25);
    int pos = beatsin16( 19, 0, kMatrixWidth-1 );

    for(int i = 0; i < kMatrixWidth; i++) {
        leds[XY(i, pos)] += CHSV( gHue, 240, 140);
    }
    for(int i = 0; i < kMatrixHeight; i++) {
        leds[XY(pos, i)] += CHSV( gHue+100, 240, 140);
    }
    FastLED.show();
    EVERY_N_MILLISECONDS( 50 ) { gHue++; } // slowly cycle the "base color" through the rainbow

}

void fx5() 
{
    Serial.println("fx5 rainbow");
    // FastLED's built-in rainbow generator
    fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void fx6() 
{
    Serial.println("FX6: Rainbow Glitter");
    // built-in FastLED rainbow, plus some random sparkly glitter
    fx5();
    addGlitter(80);
}



void fx7()
{
    Serial.println("FX7: BPM");
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    for( int i = 0; i < NUM_LEDS; i++) { //9948
        leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    }
}

void fx8() 
{
    Serial.println("FX8: Juggle");
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy( leds, NUM_LEDS, 20);
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
        leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}

void fx9()
{
    Serial.println("FX9: XY Matrix");
    uint32_t ms = millis();
    int32_t yHueDelta32 = ((int32_t)cos16( ms * (27/1) ) * (350 / kMatrixWidth));
    int32_t xHueDelta32 = ((int32_t)cos16( ms * (39/1) ) * (310 / kMatrixHeight));
    DrawOneFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
    if( ms < 5000 ) {
        FastLED.setBrightness( scale8( BRIGHTNESS, (ms * 256) / 5000));
    } else {
        FastLED.setBrightness(BRIGHTNESS);
    }
    FastLED.show();
}



//

void fx10() 
{
    Serial.println("FX10: Matrix Code");
    EVERY_N_MILLIS(75) // falling speed
    {
        // move code downward
        // start with lowest row to allow proper overlapping on each column
        for (int8_t row=kMatrixHeight-1; row>=0; row--)
        {
            for (int8_t col=0; col<kMatrixWidth; col++)
            {
                if (leds[getIndex(row, col)] == CRGB(175,255,175))
                {
                    leds[getIndex(row, col)] = CRGB(27,130,39); // create trail
                    if (row < kMatrixHeight-1) leds[getIndex(row+1, col)] = CRGB(175,255,175);
                }
            }
        }

        // fade all leds
        for(int i = 0; i < NUM_LEDS; i++) {
            if (leds[i].g != 255) leds[i].nscale8(192); // only fade trail
        }
        // check for empty screen to ensure code spawn
        bool emptyScreen = true;
        for(int i = 0; i < NUM_LEDS; i++) {
            if (leds[i]) {
                emptyScreen = false;
                break;
            }
        }

        // spawn new falling code
        if (random8(3) == 0 || emptyScreen) // lower number == more frequent spawns
        {
            int8_t spawnX = random8(kMatrixWidth);
            leds[getIndex(0, spawnX)] = CRGB(175,255,175 );
        }
        FastLED.show();
    }
}
void pic(int pic_nr) {
    if(pic_nr == 0) { long pic1 = Qbert01;long pic2 = Qbert02;}
    if(pic_nr == 1) { long pic1 = DigDug01;long pic2 = DigDug01;} 
    if(pic_nr == 2) { long pic1 = BombJack01;long pic2 = BombJack01;} 

    for(int passtime = 0; passtime < 8; passtime++) 
    { 
        FastLED.clear();
        for(int i = 0; i < NUM_LEDS; i++) {
            leds[i] = pgm_read_dword(&(pic1[i]));  // Read array from Flash
        }
        FastLED.show();
    
        delay(500)

        FastLED.clear();
        for(int i = 0; i < NUM_LEDS; i++) {
            leds[i] = pgm_read_dword(&(pic2[i]));  // Read array from Flash
        }
        FastLED.show();
    }
}


void addGlitter( fract8 chanceOfGlitter) 
{
    Serial.println("add glitter");
    if( random8() < chanceOfGlitter) {
        leds[ random16(NUM_LEDS) ] += CRGB::White;
    }
}

void confetti() 
{
    Serial.println("add confetti");
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy( leds, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS-1);
    leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy( leds, NUM_LEDS, 20);
    int pos = beatsin16( 13, 0, NUM_LEDS-1 );
    leds[pos] += CHSV( gHue, 255, 192);
}




void getPalette(int nr)
{
    nr = random(0,9);
    if (nr == 0) {    // RANDOM PALETTE
        currentPalette = CRGBPalette16( 
              CHSV( random8(), 255, 32), 
              CHSV( random8(), 255, 255), 
              CHSV( random8(), 128, 255), 
              CHSV( random8(), 255, 255)
        ); 
    }

    if(nr == 1) { // B&W PALETTE
        fill_solid( currentPalette, 16, CRGB::Black);
        currentPalette[0] = CRGB::White;
        currentPalette[4] = CRGB::White;
        currentPalette[8] = CRGB::White;
        currentPalette[12] = CRGB::White;
    }

    // Purple, Green, Black
    if(nr == 2) {
        CRGB purple = CHSV( HUE_PURPLE, 255, 255);
        CRGB green  = CHSV( HUE_GREEN, 255, 255);
        CRGB black  = CRGB::Black;
        currentPalette = CRGBPalette16( 
            green,  green,  black,  black,
            purple, purple, black,  black,
            green,  green,  black,  black,
            purple, purple, black,  black 
        );
    }
    if( nr == 3 ) { currentPalette = RainbowColors_p;}
    if( nr == 4 ) { currentPalette = LavaColors_p;   }
    if( nr == 5 ) { currentPalette = ForestColors_p; }
    if( nr == 6 ) { currentPalette = CloudColors_p;  }
    if( nr == 7 ) { currentPalette = OceanColors_p;  }
    if( nr == 8 ) { currentPalette = PartyColors_p;  }
    if( nr == 9 ) { currentPalette = RainbowStripeColors_p; }    
}




// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8() 
{
    uint8_t dataSmoothing = 0;
    if( speed < 50) { dataSmoothing = 200 - (speed * 4); }
  
    for(int i = 0; i < MAX_DIMENSION; i++) 
    {
        int ioffset = scale * i;
        for(int j = 0; j < MAX_DIMENSION; j++) 
        {
            int joffset = scale * j;
            uint8_t data = inoise8(x + ioffset,y + joffset,z);
            // The range of the inoise8 function is roughly 16-238.
            // These two operations expand those values out to roughly 0..255
            // You can comment them out if you want the raw noise data.
            data = qsub8(data,16);
            data = qadd8(data,scale8(data,39));

           if( dataSmoothing ) {
               uint8_t olddata = noise[i][j];
               uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
               data = newdata;
           }
           noise[i][j] = data;
       }
   }
  
    // apply slow drift to X and Y, just for visual variation.
    z += speed; x += speed / 8; y -= speed / 16;
}

void get_noise()
{
    static uint8_t ihue=0;
    for(int i = 0; i < kMatrixWidth; i++) {
        for(int j = 0; j < kMatrixHeight; j++) {
            // We use the value at the (i,j) coordinate in the noise
            // array for our brightness, and the flipped value from (j,i)
            // for our pixel's index into the color palette.
            uint8_t index = noise[j][i];
            uint8_t bri =   noise[i][j];
            // if this palette is a 'loop', add a slowly-changing base value
            if( colorLoop) { index += ihue; }

            // brighten up, as the color palette itself often contains the 
            // light/dark dynamic range desired
            if( bri > 127 ) {  
              bri = 255;
            } else {
              bri = dim8_raw( bri * 2);
            }
            CRGB color = ColorFromPalette( currentPalette, index, bri);
            leds[XY(i,j)] = color;
        }
    }
    ihue+=1;
}


void DrawOneFrame( byte startHue8, int8_t yHueDelta8, int8_t xHueDelta8)
{
    byte lineStartHue = startHue8;
    for( byte y = 0; y < kMatrixHeight; y++) {
        lineStartHue += yHueDelta8;
        byte pixelHue = lineStartHue;      
        for( byte x = 0; x < kMatrixWidth; x++) {
            pixelHue += xHueDelta8;
            leds[ XY(x, y)]  = CHSV( pixelHue, 255, 255);
        }
    }
}



// convert x/y cordinates to LED index on zig-zag grid
uint16_t getIndex(uint16_t x, uint16_t y)
{
    uint16_t index;
    if (y == 0) {
        index = x;
    } else if (y % 2 == 0) {
        index = y * kMatrixWidth + x;
    } else {
        index = ((y * kMatrixWidth) + (kMatrixWidth-1)) - x;
    }
    return index;
}

//
// Mark's xy coordinate mapping code.  See the XYMatrix for more information on it.
//
uint16_t XY( uint8_t x, uint8_t y)
{
    uint16_t i;
    if( kMatrixSerpentineLayout == false) i = (y * kMatrixWidth) + x;
    if( kMatrixSerpentineLayout == true) 
    {
        // Odd rows run backwards
        if( y & 0x01) { 
            uint8_t reverseX = (kMatrixWidth - 1) - x;
            i = (y * kMatrixWidth) + reverseX;
        } 
        else {
            // Even rows run forwards
            i = (y * kMatrixWidth) + x;
        }
    }
    return i;
}
SimplePatternList gPatterns = { fx1, fx2, fx3, fx4, fx5, fx6, fx7, fx8, fx9, fx10 };  //non-reactive patterns
