#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "secrets.h"
#include "routes.h"  // ← подключаем файл с роутингами

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Создаём асинхронный веб-сервер
AsyncWebServer server(80);

// Определение пинов
const int D4_PIN = D4;
const int D1_PIN = D1;

// Реверс сигналов
const bool OUT_OFF = LOW;
const bool OUT_ON = HIGH;

// Текущее состояние пинов
bool isState_D4 = false;
bool isState_D1 = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n=================================");
  Serial.println("Запуск ESP8266 Web Server");
  Serial.println("=================================");
  
  // Настройка пинов
  pinMode(D4_PIN, OUTPUT);
  pinMode(D1_PIN, OUTPUT);
  
  // Начальное состояние: всё выключено
  digitalWrite(D4_PIN, OUT_OFF);
  digitalWrite(D1_PIN, OUT_OFF);
  
  Serial.println("Пины настроены");
  
  // Подключение к Wi-Fi
  Serial.print("Подключение к Wi-Fi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    if (attempts > 40) {
      Serial.println("\n❌ Не удалось подключиться к Wi-Fi!");
      return;
    }
  }
  
  Serial.println("\n✅ Wi-Fi подключен!");
  Serial.print("IP адрес: ");
  Serial.println(WiFi.localIP());
  
  // Монтируем файловую систему
  if (!LittleFS.begin()) {
    Serial.println("❌ Ошибка монтирования LittleFS");
    return;
  }
  Serial.println("✅ LittleFS смонтирована");
  
  // ========== ВАЖНО! ВЫЗЫВАЕМ НАСТРОЙКУ МАРШРУТОВ ИЗ ФАЙЛА ROUTES.H ==========
  setupRoutes();
  
  // Запускаем сервер
  server.begin();
  Serial.println("✅ Веб-сервер запущен!");
  Serial.print("Открой браузер по адресу: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Мигание светодиодом для индикации работы
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 1000) {
    if (!isState_D4) {
      digitalWrite(D4_PIN, !digitalRead(D4_PIN));
    }
    lastBlink = millis();
  }
}