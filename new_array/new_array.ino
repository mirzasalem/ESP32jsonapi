#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "CIS Tech Ltd.";
const char* password = "cis@2022#";

int a=0;
int b=0;
int c=0;

const char* serverUrl = "http://192.168.68.112:8000/api/switch"; // Replace with your server URL



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

  // Make an HTTP GET request
  // HTTPClient http;
  // http.begin(serverUrl);

  // int httpCode = http.GET();

  // Check if the request was successful
  //if (httpCode == HTTP_CODE_OK) {
    // Parse JSON data
    // const size_t capacity = JSON_OBJECT_SIZE(6) + 80;
    // DynamicJsonDocument doc(capacity);

    // String jsonString = http.getString();
    // DeserializationError error = deserializeJson(doc, jsonString);

    // if (error) {
    //   Serial.println("Failed to parse JSON data.");
    //   return;
    // }

    // // Access the 'fan' value from the JSON object
    // int fanValue = doc["fan"];
    // int lightValue = doc["light"];
    // int bellValue = doc["bell"];


    // a= fanValue;
    // b= lightValue;
    // c= bellValue;
    // Serial.print("Fan Value: ");
    // Serial.println(fanValue);
    // Serial.print("light Value: ");
    // Serial.println(lightValue);
    // Serial.print("Fan Value: ");
    // Serial.println(bellValue);
  //}
  // else {
    //Serial.print("HTTP request failed with error code: ");
    //Serial.println(httpCode);
  //}

  // http.end();
}

void loop() {

    HTTPClient http;
    http.begin(serverUrl);
    int httpCode = http.GET();
    const size_t capacity = JSON_OBJECT_SIZE(6) + 80;
    DynamicJsonDocument doc(capacity);

    String jsonString = http.getString();
    DeserializationError error = deserializeJson(doc, jsonString);

    // if (error) {
    //   Serial.println("Failed to parse JSON data.");
    //   return;
    // }

    // Access the 'fan' value from the JSON object
    int fanValue = doc["fan"];
    int lightValue = doc["light"];
    int bellValue = doc["bell"];


    // a= fanValue;
    // b= lightValue;
    // c= bellValue;
    Serial.println(a);
    Serial.println(b);
    Serial.println(c);
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


