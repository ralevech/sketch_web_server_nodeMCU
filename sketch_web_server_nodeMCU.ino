#include "Includes.h"

void setup() {
    Serial.begin(74880);
    delay(500);
    
    setupPins();        // Настройка пинов
    connectToWiFi();    // Подключение к WiFi
    initFS();           // Монтирование LittleFS
    RunWebServer();     // Запуск веб-сервера
}

void loop() {
    // ESP8266
}