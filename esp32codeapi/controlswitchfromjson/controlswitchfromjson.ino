//String url = "http://localhost:8070/data"; 

// const char* ssid = "CIS Tech Ltd.";
// const char* password = "cis@2022#";

  // Your local server URL and endpoint to retrieve the JSON data
 // String url = "http://192.168.68.109:8000/api/switch"; // Replace with your server's IP and port

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "CIS Tech Ltd.";
const char* password = "cis@2022#";


//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.68.109:8000/api/switch";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

String sensorReadings;
float sensorReadingsArr[8];

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  //Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
              
      sensorReadings = httpGETRequest(serverName);
      //Serial.println(sensorReadings);
      JSONVar myObject = JSON.parse(sensorReadings);
  

      
    
      // myObject.keys() can be used to get an array of all the keys in the object
      JSONVar keys = myObject.keys();
      // JSONVar v = myObject[keys[2]];
      //Serial.println(v);

 

    

      // for (int i = 0; i < 3; i++) {
      //   JSONVar value = v[i];
      //   // Serial.print(v[0]);
      //   // Serial.print(v[1]);
      //   // Serial.print(v[2]);
      //   if(v[i] == fan){
      //     fan = v[i]['fan']
      //   }
        // Serial.println(v[i]);
        // Serial.println(v[i]["light"]);
        // Serial.println(v[i]["fan"]);
        // Serial.println(v[i]["bell"]);
        // Serial.println(value["fan"]);
        // Serial.println(myObject);
        Serial.println(keys);
      
         }

    

     }
  //   else {
  //     Serial.println("WiFi Disconnected");
  //   }
  //   lastTime = millis();
  // }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
