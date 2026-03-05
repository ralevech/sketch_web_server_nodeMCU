#pragma once

namespace Msg {
  // Успехи
  const char FS_OK[] = "🟢 LittleFS смонтирована";
  const char WIFI_OK[] = "🟢 WiFi подключен";

  // Предупреждения (желтый)
  const char FS_WARN[] = "⚠️ Мало памяти";
  
  // Ошибки  
  const char FS_ERR[] = "❌ Ошибка монтирования FS";
  const char WIFI_ERR[] = "❌ Ошибка WiFi";
  
  // Информация
  const char IP[] = "📶 IP адрес";
  const char COMPILE_TIME[] = "🕒 Время компиляции: " __DATE__ " " __TIME__;
  const char SEPARATOR[] = "========================";
  
  // Сообщения для сервера
  const char SERVER_STARTED[] = "HTTP-сервер запущен";
  const char IP_LABEL[] = "IP-адрес: ";
}