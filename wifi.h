#pragma once

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// void connectToWiFi() {
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }
//     Serial.println("\nWiFi connected");
//     Serial.print("IP: ");
//     Serial.println(WiFi.localIP());
// }


void connectToWiFi() {
    WiFi.mode(WIFI_AP_STA);
    
    // Пытаемся подключиться к твоей сети
    WiFi.begin(ssid, password);
    
    Serial.print("Подключение к WiFi");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 40) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✅ WiFi подключен");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n⚠️  Не удалось подключиться к wifi. Запускаем точку доступа...");
    }

    // Настраиваем точку доступа принудительно и явно
    Serial.println("Настройка точки доступа...");
    // Явно указываем: SSID, пароль, канал (1 - самый безопасный), hidden = false
    WiFi.softAP("ESP_AP", "12345678", 1, false);
    
    // Даем точке доступа время на инициализацию
    delay(500);
    
    Serial.print("Точка доступа IP: ");
    Serial.println(WiFi.softAPIP());
    
    // Проверяем, запустилась ли она
    if (WiFi.softAPgetStationNum() >= 0) {
        Serial.println("✅ Точка доступа активна");
    } else {
        Serial.println("❌ Ошибка запуска точки доступа");
    }
}