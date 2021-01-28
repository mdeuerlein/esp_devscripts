#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Zugangsdaten zu eurem WLAN:
const char* ssid     = "LaLaLand2";
const char* password = "2705531791998260";

// Den Servo und den Webserver definieren:
Servo Servo_A;
Servo Servo_B;
ESP8266WebServer WebServer ( 80 );

// In dieser Variablen steht die momentane Stellung des Servos
int SERVO_A_Current = 90;
int SERVO_B_Current = 90;

// Aufgaben beim Start des ESP8266 erledigen
void setup()
{
  // Wir debuggen auf die serielle Schnittstelle (Seriellen Monitor im der Adruino-Programm starten!)
  Serial.begin(115200);
  delay(200);
  Serial.println("Verbinde Servo.");
  // Die möglichen Pin-Nummern. In der Zeichnung wird D4 verwendet
  // D1 = 5     D2 = 4     D3 = 0    D4 = 2
  // TX = 1     RX = 3     D0 = 16   D5 = 14
  // D6 = 12    D7 = 13    D8 = 15
  Servo_A.attach(2); // 2 = D4
  Servo_B.attach(4); // 2 = D4
  Serial.println("Servo auf 0 Grad stellen");

    Servo_A.write(SERVO_A_Current); 
    delay(500); 
    Servo_B.write(SERVO_B_Current); 
    delay(500); 
 

  connectWifi();
  beginServer();
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

// jemand hat auf der Webseite eine der Schaltflächen / Buttons gedrückt
void handleSubmit() {
  // Wir holen uns den übermittelten Wert
  String SERVOValue;
  SERVOValue = WebServer.arg("DATA");
  String SERVONr;
  SERVONr = WebServer.arg("SERVO");
  int setservo = SERVOValue.toInt();
  if ( setservo > 180 ) setservo = 180;
  if ( setservo < 5 ) setservo = 5;


    if(SERVONr == "1" && SERVO_A_Current < setservo) {
      for (SERVO_A_Current; SERVO_A_Current < setservo; SERVO_A_Current++) 
      { 
        Servo_A.write(SERVO_A_Current); 
        delay(50);
      }
    }
    if(SERVONr == "1" && SERVO_A_Current > setservo) {
      for (SERVO_A_Current; SERVO_A_Current > setservo; SERVO_A_Current--) 
      { 
        Servo_A.write(SERVO_A_Current); 
        delay(50);
      }
    }
    if(SERVONr == "2" && SERVO_B_Current < setservo) {
      for (SERVO_B_Current; SERVO_B_Current < setservo; SERVO_B_Current++) 
      { 
        Servo_B.write(SERVO_B_Current); 
        delay(50);
      }
    }
    if(SERVONr == "2" && SERVO_B_Current > setservo) {
      for (SERVO_B_Current; SERVO_B_Current > setservo; SERVO_B_Current--) 
      { 
        Servo_B.write(SERVO_B_Current); 
        delay(50);
      }
    }


  
  WebServer.send ( 200, "text/html", getPage() );
}

// Hier folgt die Webseite als HTML-Code.
String getPage() {
  String ServoStringA = String(SERVO_A_Current); // Holt die aktuelle Einstellung und wandelt diese in einen String. Ist untem im Code eingebaut.
  String ServoStringB = String(SERVO_B_Current); 
  String page = "<html lang=de-DE><head>";
  //page += "<meta http-equiv='refresh' content='60'/>";
  page += "<title>Wemos D1 Mini + Servo SG90 Test</title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }";
  page += ".button {display: inline-block; padding: 15px 15px; font-size: 25px; cursor: pointer; text-align: center; text-decoration: none;";
  page += "outline: none; color: #ffffff; background-color: #4db2ec; border: none; border-radius: 5px;}";
  page += ".button:hover {background-color: #4DCAEC; color:#ffffff;}";
  page += ".button:active {background-color: #4DCAEC; box-shadow: 0 3px #666; transform: translateY(3px); }</style>";
  page += "</head><body><center><h1>Wemos D1 Mini - Servo SG90 - WebServer</h1>";
  page += "<hr><h2>A: " + ServoStringA + " // B: " + ServoStringB + "</h1><hr>";
  page += "<h3>Feste Werte</h3>";
  page += "<form action='/' method='POST'>";
  page += "<select name='SERVO'><option value='1'>A</option><option value='2'>B</option></select>";
  page += "<INPUT class='button' type='submit' name='DATA' value='5'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='15'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='30'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='45'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='60'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='75'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='90'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='105'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='120'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='135'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='150'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='165'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='180'>";
  page += "<h3>+/-</h3>";
  page += "<form action='/' method='POST'>";
  page += "<INPUT class='button' type='submit' name='DATA' value='-15'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='90'>       ";
  page += "<INPUT class='button' type='submit' name='DATA' value='+15'>";
  page += "</center></body>";
  return page;
}
