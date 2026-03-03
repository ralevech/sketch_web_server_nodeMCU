#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>  // Современная замена SPIFFS_
#include "secrets.h"  // Файл должен быть в той же папке! измени название secrets.h-EXAMPLE

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Создаём асинхронный веб-сервер
AsyncWebServer server(80);

// Определение пинов
const int D4_PIN = D4;
const int D1_PIN = D1;

// Реверс сигналов. Из-за особенностей чипа ESP-12E модуля
const bool OUT_OFF = LOW;    //  выход выключен 
const bool OUT_ON = HIGH;    //  включен выход   

// Текущее состояние пинов
bool d4State = false;
bool d1State = false;

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
    if (attempts > 40) { // 20 секунд попыток
      Serial.println("\n❌ Не удалось подключиться к Wi-Fi!");
      Serial.println("Проверьте имя сети и пароль");
      return;
    }
  }
  
  Serial.println("\n✅ Wi-Fi подключен!");
  Serial.print("IP адрес: ");
  Serial.println(WiFi.localIP());
  
  // Монтируем файловую систему LittleFS
  if (!LittleFS.begin()) {
    Serial.println("❌ Ошибка монтирования LittleFS");
    return;
  }

  Serial.println("✅ LittleFS смонтирована");
  
  // Настраиваем маршруты
  
  // Главная страница - отдаём index.html
  //server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //  request->send(LittleFS, "/index.html", "text/html");
  //});


// Универсальный обработчик для всех непойманных запросов
server.onNotFound([](AsyncWebServerRequest *request) {
  Serial.println("Запрос к: " + request->url());
  
  // Если запрошен корень - отдаем index.html
  if (request->url() == "/") {
    request->send(LittleFS, "/index.html", "text/html");
  } 
  // Если запрошен неизвестный путь
  else {
    request->send(404, "text/plain", "404: Страница не найдена");
  }
});

  // Управление пином D4
  server.on("/D4/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(D4_PIN, !OUT_ON);   // включить "светодиод"
    d4State = true;
    request->send(200, "text/plain", "D4 ON");
    Serial.println("D4 включен");
  });
  
  server.on("/D4/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(D4_PIN, !OUT_OFF);  // выключить "светодиод"
    d4State = false;
    request->send(200, "text/plain", "D4 OFF");
    Serial.println("D4 выключен");
  });
  
  // Управление пином D1
  server.on("/D1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(D1_PIN, OUT_ON);  // включить "светодиод"
    d1State = true;
    request->send(200, "text/plain", "D1 ON");
    Serial.println("D1 включен");
  });
  
  server.on("/D1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(D1_PIN, OUT_OFF);   // выключить "светодиод"
    d1State = false;
    request->send(200, "text/plain", "D1 OFF");
    Serial.println("D1 выключен");
  });
  
  // Маршрут для получения статуса (опционально)
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    String json = "{\"d4\":" + String(d4State ? "true" : "false") + 
                  ",\"d1\":" + String(d1State ? "true" : "false") + "}";
    request->send(200, "application/json", json);
  });
  
  // Запускаем сервер
  server.begin();
  Serial.println("✅ Веб-сервер запущен!");
  Serial.print("Открой браузер по адресу: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Всё работает асинхронно, тут ничего не нужно
  // Но можно добавить мигание светодиодом для индикации работы
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 1000) {
    // Быстро мигаем встроенным светодиодом, показывая что сервер работает
    // Но только если он не используется для управления
    if (!d4State) {
      digitalWrite(D4_PIN, !digitalRead(D4_PIN));
    }
    lastBlink = millis();
  }
} 