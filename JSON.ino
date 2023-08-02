#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>



const char* ssid = "CIS Tech Ltd.";
const char* password = "cis@2022#";





const char* serverUrl = "http://192.168.68.109:8000/api/switch"; // Replace with your server URL


void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Make an HTTP GET request
  HTTPClient http;
  http.begin(serverUrl);

  int httpCode = http.GET();

  // Check if the request was successful
  if (httpCode == HTTP_CODE_OK) {
    // Parse JSON data
    const size_t capacity = JSON_ARRAY_SIZE(4) + 10 * JSON_OBJECT_SIZE(5); // Adjust the size based on your JSON data structure.
    DynamicJsonDocument doc(capacity);

    String jsonString = http.getString();
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
      Serial.println("Failed to parse JSON data.");
      return;
    }

    // Access the JSON array
    JsonArray jsonArray = doc.as<JsonArray>();

    // Loop through the JSON array
    for (JsonObject obj : jsonArray) {
      // Extract the values from each JSON object in the array
      const char* sensorType = obj["sensor"];
      float sensorValue = obj["data"];

      // Print the extracted data
      Serial.print("Sensor: ");
      Serial.print(sensorType);
      Serial.print(", Value: ");
      Serial.println(sensorValue);
    }
  } else {
    Serial.print("HTTP request failed with error code: ");
    Serial.println(httpCode);
  }

  http.end();
}

void loop() {
  // Your code here, if any
}
