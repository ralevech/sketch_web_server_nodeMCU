#pragma once
#include "Includes.h"

AsyncWebServer server(80);

void runWebServer() {
    setupRoutes();
    server.begin();
    Serial.println("Server started");
}