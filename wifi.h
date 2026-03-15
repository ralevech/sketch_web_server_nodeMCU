#pragma once

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void connectToWiFi() {
    Serial.println("\n=== НАСТРОЙКА WiFi ===");
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    Serial.print("Подключение к WiFi");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("✅ WiFi подключен");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        
        // mDNS в режиме STA
        if (MDNS.begin("host")) {
            Serial.println("✅ mDNS запущен: http://host.local");
            MDNS.addService("http", "tcp", 80);
        }
        
    } else {
        Serial.println("⚠️  Не удалось подключиться");
        Serial.println("🔄 Запуск точки доступа...");
        
        WiFi.disconnect(true);
        delay(100);
        WiFi.mode(WIFI_OFF);
        delay(100);
        WiFi.mode(WIFI_AP);
        
        WiFi.softAPConfig(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));
        WiFi.softAP("ESP_AP", "12345678", 1, false);
        delay(500);
        
        // mDNS в режиме AP
        if (MDNS.begin("host")) {
            Serial.println("✅ mDNS запущен: http://host.local");
            MDNS.addService("http", "tcp", 80);
        }
        
        Serial.println("✅ Точка доступа запущена");
        Serial.println("📡 SSID: ESP_AP");
        Serial.println("🔑 Пароль: 12345678");
        Serial.print("🌐 IP: ");
        Serial.println(WiFi.softAPIP());
    }
    
    Serial.println("========================\n");
}