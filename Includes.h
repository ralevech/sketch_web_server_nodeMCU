#pragma once

// ============ БИБЛИОТЕКИ ============
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>

// ============ МОИ ФАЙЛЫ =============
#include "secrets.h"           // WiFi логин и пароль
#include "wifi.h"              // Подключение к WiFi
#include "filesystem.h"        // Файловая система LittleFS
#include "routes.h"            // НАВИГАЦИЯ - ПЕРЕНЕСТИ СЮДА
#include "server.h"            // Веб-сервер - ПОТОМ СЮДА
#include "pin_config.h"        // Настройка пинов
