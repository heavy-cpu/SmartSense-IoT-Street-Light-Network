#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "elias";
const char* password = "123elias";
const char* serverIP = "10.74.167.135"; // Your ESP32 IP

#define LDR_DIGITAL_PIN D2  // GPIO4

void setup() {
  Serial.begin(115200);
  pinMode(LDR_DIGITAL_PIN, INPUT);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected!");
}

void loop() {
  int ldrDigitalValue = digitalRead(LDR_DIGITAL_PIN);

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;  // ***NEW: Create WiFiClient object
    HTTPClient http;
    String url = "http://" + String(serverIP) + "/ldr?value=" + String(ldrDigitalValue);
    http.begin(client, url);  // ***NEW: Pass both client and url to begin()
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("Server Response: ");
      Serial.println(payload);
    } else {
      Serial.print("Error in sending: ");
      Serial.println(httpCode);
    }
    http.end();
  }
  delay(10000);
}
