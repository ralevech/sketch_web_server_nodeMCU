#pragma once 
#include "Includes.h"

// Объявляем, что эти переменные есть в основном файле
extern AsyncWebServer server;
extern const int D4_PIN;
extern const int D1_PIN;
extern const bool OUT_ON;
extern const bool OUT_OFF;
extern bool isState_D4;
extern bool isState_D1;

// Функция настройки маршрутов
void setupRoutes(AsyncWebServer &server, 
                const int D4_PIN, 
                const int D1_PIN, 
                const bool OUT_OFF, 
                const bool OUT_ON,
                bool &isState_D4, 
                bool &isState_D1) {
  
  // Универсальный обработчик
  server.onNotFound([](AsyncWebServerRequest *request) {
    Serial.println("Запрос к: " + request->url());
    if (request->url() == "/") {
      request->send(LittleFS, "/index.html", "text/html");
    } else {
      request->send(404, "text/plain", "404: Страница не найдена");
    }
  });

  // CSS
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/style.css", "text/css");
  });

  // Страницы
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

  // Управление D4 - ЗАХВАТЫВАЕМ ВСЕ НУЖНЫЕ ПЕРЕМЕННЫЕ
  server.on("/D4/on", HTTP_GET, [D4_PIN, OUT_ON, &isState_D4](AsyncWebServerRequest *request) {
    digitalWrite(D4_PIN, !OUT_ON);
    isState_D4 = true;
    request->send(200, "text/plain", "D4 ON");
    Serial.println("D4 включен");
  });
  
  server.on("/D4/off", HTTP_GET, [D4_PIN, OUT_OFF, &isState_D4](AsyncWebServerRequest *request) {
    digitalWrite(D4_PIN, !OUT_OFF);
    isState_D4 = false;
    request->send(200, "text/plain", "D4 OFF");
    Serial.println("D4 выключен");
  });
  
  // Управление D1 - ЗАХВАТЫВАЕМ ВСЕ НУЖНЫЕ ПЕРЕМЕННЫЕ
  server.on("/D1/on", HTTP_GET, [D1_PIN, OUT_ON, &isState_D1](AsyncWebServerRequest *request) {
    digitalWrite(D1_PIN, OUT_ON);
    isState_D1 = true;
    request->send(200, "text/plain", "D1 ON");
    Serial.println("D1 включен");
  });
  
  server.on("/D1/off", HTTP_GET, [D1_PIN, OUT_OFF, &isState_D1](AsyncWebServerRequest *request) {
    digitalWrite(D1_PIN, OUT_OFF);
    isState_D1 = false;
    request->send(200, "text/plain", "D1 OFF");
    Serial.println("D1 выключен");
  });
  
  // Статус - ЗАХВАТЫВАЕМ СОСТОЯНИЯ
  server.on("/status", HTTP_GET, [&isState_D4, &isState_D1](AsyncWebServerRequest *request) {
    String json = "{\"d4\":" + String(isState_D4 ? "true" : "false") + 
                  ",\"d1\":" + String(isState_D1 ? "true" : "false") + "}";
    request->send(200, "application/json", json);
  });
}