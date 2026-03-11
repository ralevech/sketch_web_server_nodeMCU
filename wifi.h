#pragma once

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void connectToWiFi() {
    Serial.println("\n=== НАСТРОЙКА WiFi ===");
    
    // Пытаемся подключиться к WiFi сети
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    Serial.print("Подключение к WiFi");
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) { // 20 попыток * 500мс = 10 секунд
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("✅ WiFi подключен");
        Serial.print("IP адрес: ");
        Serial.println(WiFi.localIP());
        
    } else {
        Serial.println("⚠️  Не удалось подключиться к WiFi");
        Serial.println("🔄 Запуск точки доступа...");
        
        // Переключаемся в режим точки доступа
        WiFi.disconnect(true);
        delay(100);
        WiFi.mode(WIFI_OFF);
        delay(100);
        WiFi.mode(WIFI_AP);
        
        // Настраиваем точку доступа
        WiFi.softAP("ESP_AP", "12345678", 1, false);
        delay(500);
        
        // Выводим информацию о точке доступа
        Serial.println("✅ Точка доступа запущена");
        Serial.println("📡 Имя сети: ESP_AP");
        Serial.println("🔑 Пароль: 12345678");
        Serial.print("🌐 IP адрес: ");
        Serial.println(WiFi.softAPIP());
    }
    
    Serial.println("========================\n");
}