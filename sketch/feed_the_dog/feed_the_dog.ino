#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define BUZZER_PIN 4

const char* ssid     = "";
const char* password = "";

// Den Servo und den Webserver definieren:
Servo servo;
ESP8266WebServer WebServer ( 80 );

// In dieser Variablen steht die momentane Stellung des Servos
int SERVOCurrent = 0;

// Aufgaben beim Start des ESP8266 erledigen
void setup()
{
  Serial.begin(115200);
  delay(200);
  Serial.println("Starting");
  servo.attach(12); // 2 = D4
  connectWifi();
  beginServer();
  Serial.println("Servo auf START stellen");

  servo.write(90);

  tone(BUZZER_PIN, 600, 200);
  delay(100 * 1.3);
  tone(BUZZER_PIN, 700, 200);
  delay(100 * 1.3);
  tone(BUZZER_PIN, 800, 200);
  delay(100 * 1.3);

}

// die Hauptschleife fragt endlos ab ob jemand auf der Webseite etwas geklickt hat:
void loop() {
  WebServer.handleClient();
}


// Funktion welches die WiFi Verbindung aufbaut und uns das Ergebnis in dem Seriellen Monitor ausgibt
void connectWifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi verbunden");
  Serial.println("IP Addresse: ");
  Serial.println(WiFi.localIP());
}

// Funktion die den Webserver startet. Das es Port 80 ist wurde am Anfang definiert.
void beginServer()
{
  WebServer.on ( "/", handleRoot ); // Wenn die URL aufgerufen wird (ohne etwas hinter dem /) wird die Funktion "handleRoot" gestartet
  WebServer.begin();
  Serial.println ( "HTTP Webserver gestartet!" );
}

// Wird von der Funktion "beginServer" aufgerufen
void handleRoot() {
  if ( WebServer.hasArg("SERVO") ) { // Wir wurden mit dem Argument "SERVO" aufgerufen - es gibt also gleich etwas zu tun!
    handleSubmit();
  } else {
    // Einfach nur die Webseite ausliefern
    WebServer.send ( 200, "text/html", getPage() );
  }
}

// Button click
void handleSubmit() {
  Serial.println("Beeping");
  play_melody();
  Serial.println("moving feeder");
  servo.write(20);
  delay(500 * 1.3);
  Serial.println("returning");
  servo.write(90);
  noTone(BUZZER_PIN);
  delay(3000 * 1.3);
  Serial.println("DONE");

  // Webseite wieder aktualiseren
  WebServer.send ( 200, "text/html", getPage() );
}
void play_melody() {
  tone(BUZZER_PIN, 370, 1000);
  delay(200 * 1.3);
  tone(BUZZER_PIN, 450, 500);
  delay(200 * 1.3);
  tone(BUZZER_PIN, 500, 500);
  delay(200 * 1.3);
  tone(BUZZER_PIN, 600, 500);
  delay(200 * 1.3);

  tone(BUZZER_PIN, 450, 500);
  delay(200 * 1.3);
  tone(BUZZER_PIN, 500, 500);
  delay(200 * 1.3);
  tone(BUZZER_PIN, 600, 500);
  delay(200 * 1.3);
  tone(BUZZER_PIN, 700, 500);
  delay(100 * 1.3);
  tone(BUZZER_PIN, 700, 500);
  delay(100 * 1.3);
  tone(BUZZER_PIN, 700, 4000);
  return;
}
// HTML Page
String getPage() {
  String ServoString = String(SERVOCurrent); // Holt die aktuelle Einstellung und wandelt diese in einen String. Ist untem im Code eingebaut.
  String page = "<html lang=de-DE><head>";
  //page += "<meta http-equiv='refresh' content='60'/>";
  page += "<title>Feed The Dog</title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }";
  page += ".button {display: inline-block; padding: 15px 15px; font-size: 25px; cursor: pointer; text-align: center; text-decoration: none;";
  page += "outline: none; color: #ffffff; background-color: #4db2ec; border: none; border-radius: 5px;}";
  page += ".button:hover {background-color: #4DCAEC; color:#ffffff;}";
  page += ".button:active {background-color: #4DCAEC; box-shadow: 0 3px #666; transform: translateY(3px); }</style>";
  page += "</head><body><center><h1>Feed The Dog Machine</h1>";
  page += "<br><br>";
  page += "<form action='/' method='POST'>";
  page += "<button class='button' type='submit' name='SERVO' value='90'>Feed the dog</button>       ";
  page += "</form>";
  page += "</center></body>";
  return page;
}
