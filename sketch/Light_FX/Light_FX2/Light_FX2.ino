const char* ssid     = "LaLaLand2";
const char* password = "2705531791998260";

#include "OTA_setup.h"
#include "SOUND_setup.h"
#include "LED_setup.h"
#include "FX1.h"

unsigned long entry;

void setup() {
  Serial.begin(115200);
  startOTA("LEDGLOBE");
  
  startLED();
}

void loop() {
  #ifndef ESP32_RTOS
    ArduinoOTA.handle();
  #endif
  EVERY_N_MILLISECONDS( 5 ) { 
    
    
  }
  get_sound();
  fx1();
  Serial.println(" ");
 }
