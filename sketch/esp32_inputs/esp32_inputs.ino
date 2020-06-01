// A - STANDARD PUSH BUTTON
// Button is connected to GPIO 15
const int Button_PIN = 15;

// B - STANDARD POTI
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int Poti_PIN = 34;

// C - MAX9814
// Microphone is connected to GPIO 35 (Analog ADC1_CH6) 
const int Audio_PIN = 35;

// SETUP FUNCTION
void setup() 
{
  Serial.begin(115200);
  Serial.println("Starting Setup");
  delay(1000);
  
  // A - SETUP STANDARD PUSH BUTTON
  pinMode(Button_PIN, INPUT);

  // B - STANDARD POTI

  Serial.println("Setup done");
}


// LOOP FUNCTION
void loop()
{
  // A - READ BUTTON
  int BtnState = digitalRead(Button_PIN);
  if ( BtnState == HIGH )
  { 
    Serial.println("BUTTON PUSHED!");
  }
  
  // B - READ POTI
  int PotiData = analogRead(Poti_PIN);;
  Serial.print("POTI: ");
  Serial.print(PotiData);
  
  // SOUND MODULE
  int AudioData = analogRead(Audio_PIN);
  Serial.print("AUDIO: ");
  Serial.println(AudiData);
  
  delay(500);
  
}
