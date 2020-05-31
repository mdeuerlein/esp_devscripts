#include <ESP8266WiFi.h>

const char* ssid     = "MeineFritzBox";
const char* password = "MeinWLANSchlüssel";

String http_header; // Variable for http requests

WiFiServer server(80); // Set Webserver on Port 80

void setup() 
{
  Serial.begin(115200);
  Serial.println("Started");
  Serial.println("Connecting WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("
  Serial.print("Connected! Local IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
    WiFiClient client = server.available();  

    if (client) { 
        Serial.println("Incoming request");
        String currentLine = "";

        while (client.connected()) 
        {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                header += c;

                if (c == '\n') {

                    if (currentLine.length() == 0) {

                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        if (header.indexOf("GET /index") >= 0) {
                            Serial.println("index");
                        } 
                        else 
                        if (header.indexOf("GET /page_one") >= 0) {
                            Serial.println("page_one");
                        }
            
                        client.println("<!DOCTYPE html><html>...");
                        client.println();
                        break;

                    } else { 
                        currentLine = "";
                    }
                } 
               else if (c != '\r') currentLine += c;      
            }
        } // end of while
    
        header = "";
        client.stop();
        Serial.println("Request finished");
    }
}
