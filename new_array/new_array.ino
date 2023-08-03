#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "CIS Tech Ltd.";
const char* password = "cis@2022#";

const char* serverUrl = "https://homeautomation.cisstaging.com/api/switch"; // Replace with your server URL

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(23, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

}

void loop() {

    HTTPClient http;
    http.begin(serverUrl);
    int httpCode = http.GET();
    const size_t capacity = JSON_OBJECT_SIZE(6) + 80;
    DynamicJsonDocument doc(capacity);

    String jsonString = http.getString();
    DeserializationError error = deserializeJson(doc, jsonString);

    int fanValue = doc["fan"];
    int lightValue = doc["light"];
    int bellValue = doc["bell"];

    delay(1000);
  if(fanValue == 1){

    digitalWrite(4,HIGH);

  }else{
    digitalWrite(4,LOW);
  
  }

  if(lightValue == 1){

    digitalWrite(2,HIGH);

  }else{
    digitalWrite(2,LOW);
  
  }
  if(bellValue == 1){

    digitalWrite(23,HIGH);

  }else{
    digitalWrite(23,LOW);
  
  }
}


