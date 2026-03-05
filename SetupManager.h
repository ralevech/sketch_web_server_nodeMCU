#pragma once
#include "Includes.h"


void runSetup(const char* ssid, 
              const char* password, 
              const int D4_PIN, 
              const int D1_PIN, 
              const bool OUT_OFF, 
              const bool OUT_ON,
              AsyncWebServer &server, 
              bool &isState_D4, 
              bool &isState_D1) {  // Обрати внимание: isState_D4 используется дважды? Опечатка?
  
  // Настройка пинов
  pinMode(D4_PIN, OUTPUT);
  pinMode(D1_PIN, OUTPUT);
  digitalWrite(D4_PIN, OUT_OFF);
  digitalWrite(D1_PIN, OUT_OFF);

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  printWifiInfo(WiFi.status(), WiFi.localIP());

  // Монтируем файловую систему
  if (!LittleFS.begin()) {
    Serial.println(Msg::FS_ERR);
    return;
  }

  Serial.println();
  Serial.println();
  Serial.println(Msg::SEPARATOR);
  Serial.println(Msg::FS_OK);
  Serial.println(Msg::SEPARATOR);

  // Настройка маршрутов
  setupRoutes(server, D4_PIN, D1_PIN, OUT_OFF, OUT_ON, isState_D4, isState_D1);
 

  // Информация о памяти
  printFSInfo();

  // Запуск сервера
  server.begin();
  Serial.println(Msg::SERVER_STARTED);
  Serial.print(Msg::IP_LABEL);
  Serial.println(WiFi.localIP());

  // Время компиляции
  Serial.println(Msg::COMPILE_TIME);
}