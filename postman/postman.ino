#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

const char *ssid = "Smart Things";
const char *password = "amibolteparina";
const int ledPin = 2; // Change this to the appropriate pin for your board

AsyncWebServer server(80);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print the IP address
  Serial.println(WiFi.localIP());

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(ledPin, LOW); // Initially turn off the LED

  // Route handlers for different pin operations
  server.on("/", HTTP_GET, connectionTest);
  server.on("/pinMode", HTTP_POST, handlePinMode);
  server.on("/digitalWrite", HTTP_POST, handleDigitalWrite);
  server.on("/digitalRead", HTTP_POST, handleDigitalRead);
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
}

void loop() {
  // Handle incoming client requests
  // server.handleClient();
}

void connectionTest(AsyncWebServerRequest* request) {
  request->send(200, "text/plain", "Connection Success");
}

void handlePinMode(AsyncWebServerRequest* request) {
  if (request->hasParam("pin") && request->hasParam("mode")) {
    String pin = request->getParam("pin")->value();
    String mode = request->getParam("mode")->value();

    int pinNumber = pin.toInt();
    int pinModeValue = mode.toInt();

    pinMode(pinNumber, pinModeValue);

    request->send(200, "text/plain", "Pin mode set.");
  } else {
    request->send(400, "text/plain", "Invalid request.");
  }
}

void handleDigitalWrite(AsyncWebServerRequest* request) {
  if (request->hasParam("pin") && request->hasParam("value")) {
    String pin = request->getParam("pin")->value();
    String value = request->getParam("value")->value();

    int pinNumber = pin.toInt();
    int pinValue = value.toInt();

    digitalWrite(pinNumber, pinValue);

    request->send(200, "text/plain", "Pin value set.");
  } else {
    request->send(400, "text/plain", "Invalid request.");
  }
}

void handleDigitalRead(AsyncWebServerRequest* request) {
  if (request->hasParam("pin")) {
    String pin = request->getParam("pin")->value();
    int pinNumber = pin.toInt();
    int pinValue = digitalRead(pinNumber);

    request->send(200, "text/plain", String(pinValue));
  } else {
    request->send(400, "text/plain", "Invalid request.");
  }
}

void handleNotFound(AsyncWebServerRequest* request) {
  request->send(404, "text/plain", "Not found.");
}