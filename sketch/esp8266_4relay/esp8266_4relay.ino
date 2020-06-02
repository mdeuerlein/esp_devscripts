void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);
  delay(100);

}

void loop() {
  digitalWrite(12, HIGH);  //  OFF : Rasensprenger
  digitalWrite(13, LOW);   //  ON  : Springbrunnen
  digitalWrite(14, LOW);   //  ON  : Teichumpe
  digitalWrite(16, LOW);   //. ON  : Buddhafigur
}
