// (главный файл)
#include <Arduino.h>
#include "wifiManager.h"
#include "ledControl.h"
#include "webServer.h"

void setup() {
  Serial.begin(115200);
  
  initLEDs();        // Инициализируем оба LED
  connectToWiFi();   // Подключаемся к WiFi
  startWebServer();  // Запускаем сервер
}

void loop() {
  handleClient();    // Обрабатываем запросы
}