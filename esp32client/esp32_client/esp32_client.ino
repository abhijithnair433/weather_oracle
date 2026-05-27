
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "BSNL-LEKHA";
const char* password = "12345678";
//const char* authkey = "333f918e658874db4a8f2eaec4f93737d3a83d76"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("connected!");

  StaticJsonDocument<200> doc;
  doc["station"] = 1;
  doc["temperature"] = 28.4;
  doc["humidity"] = 79.5;
  doc["barometric_pressure"] = 1013.25;

  String jsonString;
  serializeJson(doc, jsonString);

  Serial.println(jsonString);


  HTTPClient http;
  http.begin("http://192.168.1.6:8000/api/readings/");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Token 333f918e658874db4a8f2eaec4f93737d3a83d76");

  int responseCode = http.POST(jsonString);
  http.end();

  Serial.print("##########################################################");

  Serial.println(responseCode);

  esp_sleep_enable_timer_wakeup(10 * 60 * 1000000); // 10 minutes in microseconds
  esp_deep_sleep_start();

}

void loop() {
  // put your main code here, to run repeatedly:

}
