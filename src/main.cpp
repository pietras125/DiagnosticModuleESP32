#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

const char *ssid = "SatFilm0712";
const char *password = "b05dd4a2071283086";
WiFiServer server(80); // Port serwera

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(1000);

  // CONNECT WITH WIFI
  Serial.print("Connecting with WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());

  // RUN TCP SERVER
  server.begin();
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Connection established");

    while (client.connected()) 
    {
      if (client.available()) 
      {
        String request = client.readStringUntil('\r');
        Serial.print("Message received: ");
        Serial.println(request);

        //command to switch on LED
        if (request == "led_on")
        {
          digitalWrite(LED_BUILTIN, 1);
        }

        //command to switch off LED
        if (request == "led_off")
        {
          digitalWrite(LED_BUILTIN, 0);
        }

        //command do send test message to PC
        if (request == "test_connection")
        {
          client.println("Connection OK");
        }

        //command to disconnect current PC
        if (request == "disconnect")
        {
          client.stop();
          Serial.println("Connection closed");
          break;
        }
        
      }
    }
  }
}
