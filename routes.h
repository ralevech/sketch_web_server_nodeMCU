#pragma once
#include "Includes.h"

// Определяем пути к файлам
const char* CSS_PATH = "style.css";
const char* INDEX_PATH = "index.html";
const char* PAGE_1_PATH = "page_1.html";
const char* PAGE_2_PATH = "page_2.html";
const char* PAGE_3_PATH = "page_3.html";
const char* PAGE_4_PATH = "page_4.html";

extern AsyncWebServer server;

// Структура для маршрута
struct Route {
    const char* path;
    const char* filePath;
    const char* contentType;
};

void setupRoutes() {
    // Массив всех файловых маршрутов
    Route fileRoutes[] = {
        {"/style.css", CSS_PATH, "text/css"},
        {"/", INDEX_PATH, "text/html"},
        {"/page1", PAGE_1_PATH, "text/html"},
        {"/page2", PAGE_2_PATH, "text/html"},
        {"/page3", PAGE_3_PATH, "text/html"},
        {"/page4", PAGE_4_PATH, "text/html"}
    };

    // Создаем обработчики
    for (const auto& route : fileRoutes) {
        server.on(route.path, HTTP_GET, [route](AsyncWebServerRequest *request) {
            Serial.printf("Запрос: %s -> %s\n", route.path, route.filePath);
            
            if(!LittleFS.exists(route.filePath)) {
                Serial.printf("❌ Файл не найден: %s\n", route.filePath);
                request->send(404, "text/plain", "File not found");
                return;
            }
            
            request->send(LittleFS, route.filePath, route.contentType);
            Serial.printf("✅ Отправлен: %s\n", route.filePath);
        });
    }

    // Обработчик для несуществующих маршрутов (404)
    server.onNotFound([](AsyncWebServerRequest *request) {
        Serial.println("404 - Страница не найдена: " + request->url());
        request->send(404, "text/plain", "404: Страница не найдена");
    });

    // Управление D4 с защитой от дребезга
    server.on("/D4/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        static unsigned long lastD4On = 0;
        if (millis() - lastD4On > 300) {
            digitalWrite(D4, LOW);
            Serial.println("D4 включен");
            lastD4On = millis();
        }
        request->send(200, "text/plain", "D4 ON");
    });

    server.on("/D4/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        static unsigned long lastD4Off = 0;
        if (millis() - lastD4Off > 300) {
            digitalWrite(D4, HIGH);
            Serial.println("D4 выключен");
            lastD4Off = millis();
        }
        request->send(200, "text/plain", "D4 OFF");
    });

    // Управление D1 с защитой от дребезга
    server.on("/D1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        static unsigned long lastD1On = 0;
        if (millis() - lastD1On > 300) {
            digitalWrite(D1, HIGH);
            Serial.println("D1 включен");
            lastD1On = millis();
        }
        request->send(200, "text/plain", "D1 ON");
    });

    server.on("/D1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        static unsigned long lastD1Off = 0;
        if (millis() - lastD1Off > 300) {
            digitalWrite(D1, LOW);
            Serial.println("D1 выключен");
            lastD1Off = millis();
        }
        request->send(200, "text/plain", "D1 OFF");
    });

    // Статус
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        String json = "{";
        json += "\"d4\":" + String(digitalRead(D4) == LOW ? "true" : "false") + ",";
        json += "\"d1\":" + String(digitalRead(D1) == HIGH ? "true" : "false");
        json += "}";
        request->send(200, "application/json", json);
    });

}