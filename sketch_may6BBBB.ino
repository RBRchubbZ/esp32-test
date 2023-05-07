#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ===========================
// Enter your WiFi credentials
// ===========================
const char* ssid = "NETWORK_NAME";
const char* password = "NETWORK_PASSWORD";

String serverName = "http://192.168.0.75:8000";

void setup()
{
  Serial.begin(115200);
   
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi");
}

void getData(){
    HTTPClient http;

    String serverPath = serverName;

    http.begin(serverPath.c_str()); // dont need c_str

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      String payload = http.getString();
      Serial.println(payload);
      }else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
  }

void postData(){
  HTTPClient http;
  String serverPath = serverName + "/sayhi";

  http.begin(serverPath.c_str());

  http.addHeader("Content-Type", "application/json");
  // Send HTTP POST request
  int httpResponseCode = http.POST("{\"name\" : \"harry\"}");

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  String payload = http.getString();
  Serial.println(payload);

  http.end();

}

void loop()
{
  getData();
  postData();
  delay(6000);
}