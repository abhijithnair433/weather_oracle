
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "DHT.h"


const char* ssid = "BSNL-LEKHA";
const char* password = "12345678";
//const char* authkey = "333f918e658874db4a8f2eaec4f93737d3a83d76"

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define DHTPIN 15 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;



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

  unsigned status;
  status = bmp.begin(0x76);
  dht.begin();

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500);

  StaticJsonDocument<200> doc;
  doc["station"] = 1;
  doc["temperature"] = bmp.readTemperature();
  doc["humidity"] = dht.readHumidity();
  doc["barometric_pressure"] = bmp.readPressure();

  String jsonString;
  serializeJson(doc, jsonString);

  Serial.println(jsonString);


  HTTPClient http;
  http.begin("http://192.168.1.6:8000/api/readings/");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Token 333f918e658874db4a8f2eaec4f93737d3a83d76");

  int responseCode = http.POST(jsonString);
  http.end();

  Serial.println("##########################################################");



  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");

  Serial.print(F("Humidity = "));
  Serial.print(dht.readHumidity());
  Serial.println(" %");

  Serial.println("##########################################################");

  Serial.println(responseCode);


  esp_sleep_enable_timer_wakeup(10 * 60 * 1000000); // 10 minutes in microseconds
  esp_deep_sleep_start();



}

void loop() {
  // put your main code here, to run repeatedly:

}
