// (WiFi подключение)
#include "wifiManager.h"
#include <ESP8266WiFi.h>

const char* ssid = "Gorizont_2";
const char* password = "31123522";

void connectToWiFi() {
  Serial.println();
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}