#pragma once

AsyncWebServer server(80);

void runWebServer() {
    setupRoutes();
    server.begin();
    Serial.println("✅ Веб-сервер запущен");
}