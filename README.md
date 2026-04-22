<a href="https://github.com/ralevech/ESP8266_LED_Control">
  <img src="https://github.com/user-attachments/assets/8783f561-0cab-40a7-950d-5b1df280466e" width="360" alt="Логотип проекта">
</a>

# 🌐 WiFi Веб-сервер на NodeMCU v.3

[![GitHub license](https://img.shields.io/github/license/ralevech/ESP8266_LED_Control)](https://github.com/ralevech/ESP8266_LED_Control/blob/main/LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-45.7%25-00599C)](https://github.com/ralevech/ESP8266_LED_Control)
[![HTML](https://img.shields.io/badge/HTML-54.3%25-E34F26)](https://github.com/ralevech/ESP8266_LED_Control)
[![Platform](https://img.shields.io/badge/platform-ESP8266-blue)](https://www.espressif.com/en/products/socs/esp8266)
[![PlatformIO](https://img.shields.io/badge/platform-PlatformIO-orange)](https://platformio.org/)

Простой веб-сервер на NodeMCU (ESP8266) для управления нагрузкой через браузер. Проект переведён на **PlatformIO** с модульной структурой и файловой системой **LittleFS**.

---

## 📋 Содержание

*   [💡 О проекте](#-о-проекте)
*   [🛠 Аппаратное обеспечение](#-аппаратное-обеспечение)
*   [💻 Программное обеспечение](#-программное-обеспечение)
    *   [1. Среда разработки](#1-среда-разработки)
    *   [2. Драйвер USB-UART](#2-драйвер-usb-uart)
    *   [3. Библиотеки](#3-библиотеки)
    *   [4. Настройка Wi-Fi](#4-настройка-wi-fi)
*   [📁 Структура проекта](#-структура-проекта)
*   [🚀 Использование](#-использование)
*   [📄 Лицензия](#-лицензия)

---

## 💡 О проекте

Скетч превращает NodeMCU в веб-сервер. Плата подключается к Wi-Fi, создаёт веб-страницу. Заходите на неё с телефона или компьютера и управляете нагрузкой.

**Особенности:**
- ✅ Управление двумя LED (встроенный + внешний)
- ✅ Модульная структура (легко добавлять новые устройства)
- ✅ Файловая система LittleFS (HTML отдельно от кода)
- ✅ Автообновление статуса на веб-странице

---

## 🛠 Аппаратное обеспечение

| Компонент | Характеристика |
| :--- | :--- |
| **Плата** | NodeMCU V.3 |
| **WiFi модуль** | ESP-12E |
| **Базовый чип** | ESP8266MOD |
| **Питание** | 5 В (USB) |
| **Логика** | 3.3 В |

> ⚠️ **Важно:** Все выводы платы работают на 3.3В. При подключении внешних устройств учитывайте это.

**Подключение внешнего LED:**


---

## 💻 Программное обеспечение

### 1. Среда разработки

**Рекомендуется PlatformIO (VS Code):**

1. Установите **[Visual Studio Code](https://code.visualstudio.com/)**
2. Установите расширение **[PlatformIO IDE](https://platformio.org/install/ide?install=vscode)**
3. Откройте папку проекта

**Альтернатива (Arduino IDE):**

Скачайте и установите **Arduino IDE**:
- **[Версия 2.3.8](https://amperka.ru/page/arduino-ide)**

**Настройка для ESP8266:**
1. **Файл** → **Параметры**
2. В поле **"Дополнительные ссылки для Менеджера плат"** вставьте: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
3. **Инструменты** → **Плата** → **Менеджер плат**
4. Найдите `esp8266`, установите **"esp8266 by ESP8266 Community"**
5. Выберите плату: **Инструменты** → **Плата** → **ESP8266 Boards** → **NodeMCU 1.0 (ESP-12E Module)**

### 2. Драйвер USB-UART

Посмотрите на чип возле USB-разъема на плате. Установите нужный драйвер:

| Чип | Ссылка |
| :--- | :--- |
| **CH340 / CH341** | [wch-ic.com/downloads/CH341SER_EXE.html](https://www.wch-ic.com/downloads/CH341SER_EXE.html) |
| **CP2102** | [silabs.com/documents/public/software/CP210x_Universal_Windows_Driver.zip](https://www.silabs.com/documents/public/software/CP210x_Universal_Windows_Driver.zip) |

**Как проверить:**
- Подключите NodeMCU к компьютеру
- Откройте **Диспетчер устройств** → **Порты (COM и LPT)**
- Запомните номер порта (COM3, COM5...)

### 3. Библиотеки

Управляются через `platformio.ini`:

```ini
[env:nodemcuv2]
platform = espressif8266
board = nodemcuv2
framework = arduino
monitor_speed = 115200
board_build.filesystem = littlefs
```

Библиотеки подключаются автоматически:

ESP8266WebServer

ESP8266WiFi

LittleFS

### 4. Настройка Wi-Fi
Откройте src/wifiManager.cpp и введите свои данные:

```
const char* ssid = "Имя_вашей_WiFi_сети";
const char* password = "Пароль_от_WiFi";
```

### Структура проекта

```
sketch_web_server_nodeMCU/
├── data/
│   └── index.html          # Веб-интерфейс
├── src/
│   ├── main.cpp            # Точка входа
│   ├── ledControl.cpp      # Управление LED
│   ├── ledControl.h
│   ├── webServer.cpp       # Веб-сервер
│   ├── webServer.h
│   ├── wifiManager.cpp     # Подключение к WiFi
│   └── wifiManager.h
├── platformio.ini          # Конфигурация PlatformIO
└── .gitignore
```
