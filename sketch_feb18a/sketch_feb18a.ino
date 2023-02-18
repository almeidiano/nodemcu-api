#define LED 2 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

void setup() {
  Serial.begin(115200); // initialize serial communication
  WiFi.begin("SSID", "PASS"); // connect to WiFi network
  pinMode(LED, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
} 

void apiErrorBlink() {
  digitalWrite(LED, LOW); // Turn the LED on (Note that LOW is the voltage level)
  delay(500); // Wait for a second
  digitalWrite(LED, HIGH); // Turn the LED off by making the voltage HIGH
  delay(500); // Wait for two seconds
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http; // create HTTP client object
    WiFiClient wifiClient; // Create WifiClient object
    http.begin(wifiClient, "https://example.com"); // specify API endpoint
    int httpCode = http.GET(); // send GET request

    if (httpCode > 0) { // if response received
      digitalWrite(LED, LOW); // Turn the LED on
    }else{
      apiErrorBlink(); // Blink
    }

    http.end(); // close HTTP connection
  }

  delay(5000); // wait 5 seconds before making next request
}