#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "elias";
const char* password = "123elias";
const char* serverIP = "10.74.167.135"; // Your ESP32 IP

#define TRIG_PIN D6  // GPIO12
#define ECHO_PIN D7  // GPIO13
#define LED_PIN  D5  // GPIO14

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

long readDistanceCM() {
  // Trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Echo pulse width
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance_cm = duration * 0.034 / 2;
  return distance_cm;
}

void loop() {
  long distance = readDistanceCM();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  int motionDetected = (distance > 0 && distance < 50) ? 1 : 0; // e.g., object within 50cm

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String url = "http://" + String(serverIP) + "/motion?value=" + String(motionDetected);
    http.begin(client, url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String command = http.getString();
      Serial.print("Command from ESP32: ");
      Serial.println(command);

      if (command == "ON") {
        digitalWrite(LED_PIN, HIGH);  // LED ON
      } else {
        digitalWrite(LED_PIN, LOW);   // LED OFF
      }
    } else {
      Serial.print("Error in sending: ");
      Serial.println(httpCode);
    }
    http.end();
  }
  delay(3000); // Adjust polling time as needed
}
