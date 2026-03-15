#include "Includes.h"

void setup() {
    Serial.begin(74880);
    delay(500);
    
    setupPins();           // Настройка пинов
    connectToWiFi();       // WiFi (STA или AP)
    initFS();              // LittleFS
    setupTasks();          // Задачи TaskScheduler
    runWebServer();        // Веб-сервер

    Serial.print("Свободно RAM: ");
    Serial.println(ESP.getFreeHeap());
}

void loop() {
    runner.execute();      // Запуск планировщика задач
    MDNS.update();         // Обновление mDNS
}