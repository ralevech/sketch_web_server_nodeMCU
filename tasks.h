#pragma once

// Планировщик задач (глобальный)
Scheduler runner;

// ====== ЗАДАЧА 1: Индикация жизни (мигание D4) ======
void aliveCallback() {
    static bool state = false;
    state = !state;
    digitalWrite(D4, state ? LOW : HIGH); // D4: LOW = вкл
}
Task tAlive(1000, TASK_FOREVER, &aliveCallback);

// ====== ЗАДАЧА 2: Мониторинг WiFi ======
void wifiMonitorCallback() {
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 30000) { // раз в 30 секунд
        lastCheck = millis();
        if (WiFi.status() != WL_CONNECTED && WiFi.getMode() == WIFI_STA) {
            Serial.println("⚠️ WiFi потерян, переподключаюсь...");
            WiFi.reconnect();
        }
    }
}
Task tWifiMonitor(5000, TASK_FOREVER, &wifiMonitorCallback);

// ====== ЗАДАЧА 3: Статус в Serial ======
void statusCallback() {
    Serial.print("📊 RAM: ");
    Serial.print(ESP.getFreeHeap());
    Serial.print(" | WiFi: ");
    Serial.print(WiFi.status() == WL_CONNECTED ? "STA" : "---");
    if (WiFi.getMode() == WIFI_AP || WiFi.getMode() == WIFI_AP_STA) {
        Serial.print(" | AP clients: ");
        Serial.print(WiFi.softAPgetStationNum());
    }
    Serial.println();
}
Task tStatus(10000, TASK_FOREVER, &statusCallback);

// ====== ЗАДАЧА 4: Чтение кнопок (если есть) ======
void buttonCallback() {
    static bool lastD5 = HIGH;
    static bool lastD6 = HIGH;
    
    bool nowD5 = digitalRead(D5);
    bool nowD6 = digitalRead(D6);
    
    if (nowD5 == LOW && lastD5 == HIGH) {
        Serial.println("🔘 Кнопка D5 нажата");
    }
    if (nowD6 == LOW && lastD6 == HIGH) {
        Serial.println("🔘 Кнопка D6 нажата");
    }
    
    lastD5 = nowD5;
    lastD6 = nowD6;
}
Task tButton(50, TASK_FOREVER, &buttonCallback);

// ====== Функция инициализации задач ======
void setupTasks() {
    runner.init();
    
    runner.addTask(tAlive);
    runner.addTask(tWifiMonitor);
    runner.addTask(tStatus);
    runner.addTask(tButton);
    
    tAlive.enable();
    tWifiMonitor.enable();
    tStatus.enable();
    tButton.enable();
    
    Serial.println("✅ Задачи TaskScheduler запущены");
}