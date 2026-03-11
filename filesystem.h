#pragma once

void initFS() {
    Serial.println("Монтирование LittleFS...");
    
    // Форматируем если не монтируется
    if(!LittleFS.begin()) {
        Serial.println("Ошибка монтирования! Пробуем форматировать...");
        LittleFS.format();
        delay(1000);  // ВАЖНО: даем время на форматирование
        yield();      // Даем системе подышать
        
        if(!LittleFS.begin()) {
            Serial.println("❌ LittleFS не работает!");
            return;
        }
    }
    
    // Проверяем сколько места занято
    FSInfo fs_info;
    LittleFS.info(fs_info);
    
    Serial.println("✅ LittleFS смонтирована");
    Serial.print("Всего места: ");
    Serial.print(fs_info.totalBytes / 1024);
    Serial.println(" KB");
    Serial.print("Использовано: ");
    Serial.print(fs_info.usedBytes / 1024);
    Serial.println(" KB");
    Serial.print("Файлов: ");
    Serial.println(fs_info.totalBytes - fs_info.usedBytes);
}