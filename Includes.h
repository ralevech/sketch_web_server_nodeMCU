#pragma once

// ============ БИБЛИОТЕКИ ============
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

// ============ МОИ ФАЙЛЫ =============
#include "Messages.h"          // 1. Сообщения для монитора порта
#include "routes.h"            // 5.Навигация по страницам
#include "secrets.h"           // 2. WiFi логин и пароль
#include "DiagnosticMonitor.h" // 3. Диагностика памяти
#include "SetupManager.h"      // 4. Первоначальная настройка

