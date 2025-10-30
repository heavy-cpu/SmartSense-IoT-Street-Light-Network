#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "elias";
const char* password = "123elias";

WebServer server(80);

String latestLdrValue = "1";     // Defaults - HIGH=day, LOW=night
String latestMotionValue = "0";  // Defaults - 1=motion detected

void handleLdrUpdate() {
  latestLdrValue = server.arg("value");
  Serial.print("LDR update: ");
  Serial.println(latestLdrValue);
  server.send(200, "text/plain", "LDR received: " + latestLdrValue); // Optionally respond
}

void handleMotionUpdate() {
  latestMotionValue = server.arg("value");
  Serial.print("Motion update: ");
  Serial.println(latestMotionValue);

  // Simple light logic: only ON if NIGHT (ldr=0) AND motion=1
  if (latestLdrValue == "1" && latestMotionValue == "1") {
    server.send(200, "text/plain", "ON");
  } else {
    server.send(200, "text/plain", "OFF");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/ldr", HTTP_GET, handleLdrUpdate);
  server.on("/motion", HTTP_GET, handleMotionUpdate);
  server.begin();
}

void loop() {
  server.handleClient();
}
