#include <Wire.h>
#include "SH1106.h"     // https://github.com/squix78/esp8266-oled-ssd1306

#define ANALOG_PIN A0
#define SDA_PIN    4  // D3
#define SCL_PIN    5  // D4

int analog_avg = 0;  // variable to store the value coming from the sensor
int analog_val = 0;  // variable to store the value coming from the sensor
int avg_times  = 10;
SH1106 display(0x3c, SDA_PIN, SCL_PIN); 


void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);
  Serial.print('VAL');Serial.print(' ');
  Serial.print('AVG');Serial.println(' ');
  Wire.begin(SDA_PIN, SCL_PIN); // SDA, SCL
  display.init();
  display.flipScreenVertically(); // Adjust to suit or remove
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Hello world");
  display.display();
  delay(1000);
}

void loop() {
  // read the value from the sensor:
  analog_val = analogRead(ANALOG_PIN);
  analog_avg = (analog_avg*avg_times+analog_val)/(avg_times+1);
  Serial.print(analog_val);Serial.print(' ');
  Serial.print(analog_avg);Serial.println(' ');
  display.clear();
  display.drawString(0,0,String(analog_val));
  display.drawString(0,20,String(analog_avg));
  display.display();
  delay(5);
}
