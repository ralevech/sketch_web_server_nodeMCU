#pragma once

// ============ БИБЛИОТЕКИ ============
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <TaskScheduler.h>

// ============ МОИ ФАЙЛЫ =============
#include "secrets.h"           // WiFi логин и пароль
#include "tasks.h"             // Планировщик задач
#include "wifi.h"              // Подключение к WiFi
#include "filesystem.h"        // Файловая система LittleFS
#include "routes.h"            // Навигация
#include "server.h"            // Веб-сервер
#include "pin_config.h"        // Настройка пинов

// ============ ГЛОБАЛЬНЫЕ ОБЪЕКТЫ ============
extern AsyncWebServer server;
extern Scheduler runner;   // Планировщик задач (определён в tasks.h)