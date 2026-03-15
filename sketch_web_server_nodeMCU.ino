#include "Includes.h"

void setup() {
    Serial.begin(74880);
    delay(500);
    
    setupPins();        // Настройка пинов
    connectToWiFi();    // Подключение к WiFi
    initFS();           // Монтирование LittleFS
    runWebServer();     // Запуск веб-сервера

    Serial.print("Свободно RAM: ");
    Serial.println(ESP.getFreeHeap());
}

void loop() {
    MDNS.update();
}