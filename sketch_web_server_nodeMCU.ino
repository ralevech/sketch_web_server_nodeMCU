#include "Includes.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Создаём асинхронный веб-сервер
AsyncWebServer server(80);

const int D4_PIN = D4;
const int D1_PIN = D1;
const bool OUT_OFF = LOW;
const bool OUT_ON = HIGH;

bool isState_D4 = false;
bool isState_D1 = false;

void setup() {
  Serial.begin(74880);
  delay(500);

  runSetup(ssid, password, D4_PIN, D1_PIN, OUT_OFF, OUT_ON, server, isState_D4, isState_D1);
}

void loop() {
  // Мигание светодиодом для индикации работы
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 1000) {
    if (!isState_D4) {
      digitalWrite(D4_PIN, !digitalRead(D4_PIN));
    }
    lastBlink = millis();
  }
}
