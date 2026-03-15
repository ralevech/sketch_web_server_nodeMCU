#pragma once
#include "Includes.h"

// Определяем пути к файлам
const char* CSS_PATH = "style.css";
const char* INDEX_PATH = "index.html";
const char* PAGE_1_PATH = "page_1.html";
const char* PAGE_2_PATH = "page_2.html";
const char* PAGE_3_PATH = "page_3.html";

extern AsyncWebServer server;

// Структура для файловых маршрутов
struct Route {
    const char* path;
    const char* filePath;
    const char* contentType;
};

// Структура для пинов
struct PinRoute {
    const char* name;
    int pin;
    bool invert;  // true для D4 (LOW = вкл), false для остальных (HIGH = вкл)
};

void setupRoutes() {
    // ========== ФАЙЛОВЫЕ МАРШРУТЫ ==========
    Route fileRoutes[] = {
        {"/style.css", CSS_PATH, "text/css"},
        {"/", INDEX_PATH, "text/html"},
        {"/page1", PAGE_1_PATH, "text/html"},
        {"/page2", PAGE_2_PATH, "text/html"},
        {"/page3", PAGE_3_PATH, "text/html"}
    };

    for (const auto& route : fileRoutes) {
        server.on(route.path, HTTP_GET, [route](AsyncWebServerRequest *request) {
            if(!LittleFS.exists(route.filePath)) {
                request->send(404, "text/plain", "File not found");
                return;
            }
            request->send(LittleFS, route.filePath, route.contentType);
        });
    }

    // ========== МАРШРУТЫ ДЛЯ ПИНОВ ==========
    PinRoute pins[] = {
        {"D4", D4, true},   // D4: invert=true (LOW = вкл)
        {"D1", D1, false},  // D1: invert=false (HIGH = вкл)
        {"D2", D2, false},
        {"D3", D3, false},
        {"D5", D5, false},
        {"D6", D6, false},
        {"D7", D7, false},
        {"D8", D8, false}
    };

    // Создаем обработчики для каждого пина
    for (const auto& p : pins) {
        // Включение
        String onPath = String("/") + p.name + "/on";
        server.on(onPath.c_str(), HTTP_GET, [p](AsyncWebServerRequest *request) {
            static unsigned long lastTime = 0;
            if (millis() - lastTime > 300) {
                digitalWrite(p.pin, p.invert ? LOW : HIGH);
                Serial.printf("%s включен\n", p.name);
                lastTime = millis();
            }
            request->send(200, "text/plain", String(p.name) + " ON");
        });
        
        // Выключение
        String offPath = String("/") + p.name + "/off";
        server.on(offPath.c_str(), HTTP_GET, [p](AsyncWebServerRequest *request) {
            static unsigned long lastTime = 0;
            if (millis() - lastTime > 300) {
                digitalWrite(p.pin, p.invert ? HIGH : LOW);
                Serial.printf("%s выключен\n", p.name);
                lastTime = millis();
            }
            request->send(200, "text/plain", String(p.name) + " OFF");
        });
    }

    // ========== СТАТУС ==========
    server.on("/status", HTTP_GET, [pins](AsyncWebServerRequest *request) {
        String json = "{";
        for (int i = 0; i < 8; i++) {
            bool state;
            if (pins[i].invert) {
                state = (digitalRead(pins[i].pin) == LOW);  // D4
            } else {
                state = (digitalRead(pins[i].pin) == HIGH); // остальные
            }
            
            json += "\"" + String(pins[i].name) + "\":" + (state ? "true" : "false");
            if (i < 7) json += ",";
        }
        json += "}";
        request->send(200, "application/json", json);
    });

    // ========== 404 ==========
    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "404: Not found");
    });
}