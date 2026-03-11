#pragma once
#include "Includes.h"

extern AsyncWebServer server;

void setupRoutes() {
    // Универсальный обработчик
    server.onNotFound([](AsyncWebServerRequest *request) {
        Serial.println("Запрос к: " + request->url());
        if (request->url() == "/") {
            request->send(LittleFS, "/index.html", "text/html");
        } else {
            request->send(404, "text/plain", "404: Страница не найдена");
        }
    });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/style.css", "text/css");
    });

    server.on("/page1", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/page_1.html", "text/html");
    });

    server.on("/page2", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/page_2.html", "text/html");
    });

    server.on("/page3", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/page_3.html", "text/html");
    });

    server.on("/page4", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/page_4.html", "text/html");
    });

    // Управление D4 - читаем состояние из пина
    server.on("/D4/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(D4, LOW);
        request->send(200, "text/plain", "D4 ON");
        Serial.println("D4 включен");
    });

    server.on("/D4/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(D4, HIGH);
        request->send(200, "text/plain", "D4 OFF");
        Serial.println("D4 выключен");
    });

    // Управление D1
    server.on("/D1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(D1, HIGH);
        request->send(200, "text/plain", "D1 ON");
        Serial.println("D1 включен");
    });

    server.on("/D1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(D1, LOW);
        request->send(200, "text/plain", "D1 OFF");
        Serial.println("D1 выключен");
    });

    // Статус - читаем из пинов
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        String json = "{";
        json += "\"d4\":" + String(digitalRead(D4) == LOW ? "true" : "false") + ",";
        json += "\"d1\":" + String(digitalRead(D1) == HIGH ? "true" : "false");
        json += "}";
        request->send(200, "application/json", json);
    });
}