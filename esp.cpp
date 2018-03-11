#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  sensors.begin();
  Serial.begin(115200);
  WiFiMulti.addAP("Orange-E0B7", "32804607");
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
    delay(200);
  }
  pinMode(5, INPUT_PULLUP);
}
int dodania = 0;
void loop() {
  if (digitalRead(5) == LOW){
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      dodania = dodania + 1;
      sensors.requestTemperatures();
      HTTPClient http;
      String content = "http://smarthomeluna.cba.pl/add.php?a=";
      content += sensors.getTempCByIndex(0);

      content += "&b=";
      content += dodania;

      Serial.print("[HTTP] begin...\n");
      http.begin(content);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        }
      }
      else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
  }
}
