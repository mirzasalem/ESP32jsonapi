//String url = "http://localhost:8070/data"; 

// const char* ssid = "CIS Tech Ltd.";
// const char* password = "cis@2022#";

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "CIS Tech Ltd.";
const char* password = "cis@2022#";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi!");
}

void loop() {
  // Your local server URL and endpoint to retrieve the JSON data
  String url = "http://192.168.68.109:8000/api/switch"; // Replace with your server's IP and port

  HTTPClient http;
  http.begin(url);

  // Send the GET request
  int httpCode = http.GET();

  // Check for a successful connection
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString(); // Get the JSON response payload

    // Print the received JSON data
    Serial.println("Received JSON data:");
    Serial.println(payload);
    delay(1000); // 5 seconds delay (adjust as needed)




    






  } else {
    Serial.print("HTTP GET request failed, error code: ");
    Serial.println(httpCode);
  }

  http.end(); // Close the connection

  // Wait for some time before making the next request
  
}