// (обработчики)
#include "webServer.h"
#include "ledControl.h"
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);

// Функция для определения MIME типа
String getContentType(String filename) {
  if (filename.endsWith(".css")) return "text/css";
  if (filename.endsWith(".js")) return "application/javascript";
  if (filename.endsWith(".html")) return "text/html";
  return "text/plain";
}

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  String html = file.readString();
  file.close();
  server.send(200, "text/html", html);
}

// Обработчики для LED1
void handleToggle1() {
  toggleLED1();
  server.send(200, "text/plain", getLED1Status());
}

void handleStatus1() {
  server.send(200, "text/plain", getLED1Status());
}

// Обработчики для LED2
void handleToggle2() {
  toggleLED2();
  server.send(200, "text/plain", getLED2Status());
}

void handleSystem() {
  String json = "{";
  json += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
  json += "\"uptime\":" + String(millis() / 1000) + ",";
  json += "\"heap\":" + String(ESP.getFreeHeap());
  json += "}";
  server.send(200, "application/json", json);
}

void handleStatus2() {
  server.send(200, "text/plain", getLED2Status());
}

void startWebServer() {
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
    return;
  }

  // ДИАГНОСТИКА: показываем все файлы
  Serial.println("Files in LittleFS:");
  Dir dir = LittleFS.openDir("/");
  int fileCount = 0;
  while (dir.next()) {
    Serial.print("  - ");
    Serial.println(dir.fileName());
    fileCount++;
  }
  
  if (fileCount == 0) {
    Serial.println("  (no files found!)");
    Serial.println("You need to upload filesystem image!");
  }
  
  // Проверяем index.html
  if (LittleFS.exists("/index.html")) {
    Serial.println("✅ index.html FOUND!");
  } else {
    Serial.println("❌ index.html NOT found!");
  }

  // ========== УНИВЕРСАЛЬНЫЙ ОБРАБОТЧИК ДЛЯ CSS/JS ==========
  server.onNotFound([]() {
    String path = server.uri();
    
    if (LittleFS.exists(path)) {
      File file = LittleFS.open(path, "r");
      String contentType = getContentType(path);
      server.streamFile(file, contentType);
      file.close();
    } else {
      server.send(404, "text/plain", "File not found: " + path);
    }
  });
  // ========================================================

  // Основная страница
  server.on("/", handleRoot);
  // LED1
  server.on("/toggle1", handleToggle1);
  server.on("/status1", handleStatus1);
  // LED2
  server.on("/toggle2", handleToggle2);
  server.on("/status2", handleStatus2);
  //
  server.on("/system", handleSystem);
  
  // запускаем сервер
  server.begin();
  // тех. информация в консоль
  Serial.println("HTTP server started");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void handleClient() {
  server.handleClient();
}