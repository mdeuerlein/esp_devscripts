#define FASTLED_ESP8266_RAW_PIN_ORDER

const char* ssid     = "LaLaLand2";
const char* password = "2705531791998260";

// #include "OTA_setup.h"
#include "SOUND_setup.h"
#include "LED_setup.h"
#include "FX1.h"

unsigned long entry;

void setup() {
  
  // startOTA("fx3");
    Serial.begin(115200);
  Serial.println("Starting");
  startLED();
}

void loop() {
  get_sound();
  fx1();
  
 }
