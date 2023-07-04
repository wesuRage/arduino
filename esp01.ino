#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

WiFiClientSecure wifiClient;
const char* ssid = "wifi-to-connect";
const char* password = "wifi-to-connect";

const char* ssid_esp = "test";
const char* password_esp = "12345678";

void setup() {
  Serial.begin(115200);
  delay(4000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    wifiClient.setInsecure();

    http.begin(wifiClient, "https://api.openai.com/v1/chat/completions");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer KEY");

    char json[] = "{\"model\":\"gpt-3.5-turbo\",\"messages\":[{\"role\":\"user\",\"content\":\""+ +"\"}],\"temperature\":0.7}";
    int httpResponseCode = http.POST(json);

    if (httpResponseCode > 0) {

      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);

    } else {

      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(100000);
}
