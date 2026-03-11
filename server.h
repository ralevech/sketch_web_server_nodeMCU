#pragma once
#include "Includes.h"

AsyncWebServer server(80);

void RunWebServer() {
    setupRoutes();
    server.begin();
    Serial.println("Server started");
}