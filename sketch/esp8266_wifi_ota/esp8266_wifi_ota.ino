const char* ssid     = "";
const char* password = "";

#include "OTA_setup.h"

unsigned long entry;

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  setupOTA("ESP8266_4RELAY");
  delay(100);
}

void loop() {
  #ifndef ESP32_RTOS
  ArduinoOTA.handle();
  #endif
}
