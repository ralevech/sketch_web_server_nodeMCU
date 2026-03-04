<a href="https://github.com/ralevech/sketch_web_server_nodeMCU">
  <img src="https://github.com/user-attachments/assets/8783f561-0cab-40a7-950d-5b1df280466e" width="360" alt="Логотип проекта">
</a>

# 🌐 WiFi Веб-сервер на NodeMCU v.3

[![GitHub license](https://img.shields.io/github/license/ralevech/sketch_web_server_nodeMCU)](https://github.com/ralevech/sketch_web_server_nodeMCU/blob/main/LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-45.7%25-00599C)](https://github.com/ralevech/sketch_web_server_nodeMCU)
[![HTML](https://img.shields.io/badge/HTML-54.3%25-E34F26)](https://github.com/ralevech/sketch_web_server_nodeMCU)
[![Platform](https://img.shields.io/badge/platform-ESP8266-blue)](https://www.espressif.com/en/products/socs/esp8266)
[![Arduino IDE](https://img.shields.io/badge/IDE-Arduino%20IDE-00979D)](https://www.arduino.cc/en/software)

Простой веб-сервер на NodeMCU (ESP8266) для управления нагрузкой через браузер.

---

## 📋 Содержание

*   [💡 О проекте](#-о-проекте)
*   [🛠 Аппаратное обеспечение](#-аппаратное-обеспечение)
*   [💻 Программное обеспечение](#-программное-обеспечение)
    *   [1. Среда разработки](#1-среда-разработки)
    *   [2. Драйвер USB-UART](#2-драйвер-usb-uart)
    *   [3. Библиотеки](#3-библиотеки)
    *   [4. Плагин для загрузки файлов](#4-плагин-для-загрузки-файлов-arduino-littlefs-upload-163vsix)
    *   [5. Настройка Wi-Fi](#5-настройка-wi-fi)
*   [🚀 Использование](#-использование)
*   [📄 Лицензия](#-лицензия)

---

## 💡 О проекте

<a id="о-проекте"></a>
Скетч превращает NodeMCU в веб-сервер. Плата подключается к Wi-Fi, создает веб-страницу. Заходите на неё с телефона или компьютера и управляете нагрузкой.

---

## 🛠 Аппаратное обеспечение

<a id="аппаратное-обеспечение"></a>
| Компонент | Характеристика |
| :--- | :--- |
| **Плата** | NodeMCU V.3 |
| **WiFi модуль** | ESP-12E |
| **Базовый чип** | ESP8266MOD |
| **Питание** | 5 В (USB) |
| **Логика** | 3.3 В |

> ⚠️ **Важно:** Все выводы платы работают на 3.3В. При подключении внешних устройств учитывайте это.

---

## 💻 Программное обеспечение

<a id="программное-обеспечение"></a>
### 1. Среда разработки

<a id="1-среда-разработки"></a>
Скачайте и установите **Arduino IDE**:
- **[Версия 2.3.8](https://amperka.ru/page/arduino-ide)**

**Настройка для ESP8266:**
1. **Файл** → **Параметры**
2. В поле **"Дополнительные ссылки для Менеджера плат"** вставьте: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
3. **Инструменты** → **Плата** → **Менеджер плат**
4. Найдите `esp8266`, установите **"esp8266 by ESP8266 Community"**
5. Выберите плату: **Инструменты** → **Плата** → **ESP8266 Boards** → **NodeMCU 1.0 (ESP-12E Module)**

### 2. Драйвер USB-UART

<a id="2-драйвер-usb-uart"></a>
Посмотрите на чип возле USB-разъема на плате. Установите нужный драйвер:

| Чип | Ссылка |
| :--- | :--- |
| **CH340 / CH341** | [wch-ic.com/downloads/CH341SER_EXE.html](https://www.wch-ic.com/downloads/CH341SER_EXE.html) |
| **CP2102** | [silabs.com/documents/public/software/CP210x_Universal_Windows_Driver.zip](https://www.silabs.com/documents/public/software/CP210x_Universal_Windows_Driver.zip) |
| **CH9102 / CH343** | [wch-ic.com/downloads/CH343SER_EXE.html](https://www.wch-ic.com/downloads/CH343SER_EXE.html) |

**Как проверить:**
- Подключите NodeMCU к компьютеру
- Откройте **Диспетчер устройств** → **Порты (COM и LPT)**
- Запомните номер порта (COM3, COM5...)

### 3. Библиотеки

<a id="3-библиотеки"></a>
| Библиотека | Где скачать | Как установить |
| :--- | :--- | :--- |
| **ESPAsyncWebServer** | [github.com/ESP32Async/ESPAsyncWebServer](https://github.com/ESP32Async/ESPAsyncWebServer) → Code → Download ZIP | **Скетч** → **Подключить библиотеку** → **Добавить .ZIP библиотеку...** |
| **ESP8266WiFi** | Встроенная, не требуется | — |

### 4. Плагин для загрузки файлов (arduino-littlefs-upload-1.6.3.vsix)

<a id="4-плагин-для-загрузки-файлов-arduino-littlefs-upload-163vsix"></a>
Нужен для загрузки веб-страницы в память платы.

1. Скачайте: **[github.com/earlephilhower/arduino-littlefs-upload/releases/tag/1.6.3](https://github.com/earlephilhower/arduino-littlefs-upload/releases/tag/1.6.3)** (файл `.vsix`)
2. Поместить этот файл сюда, создав папку C:\Users\<Имя_пользователя>\.arduinoIDE\plugins
3. Перезапустите Arduino IDE

**Как пользоваться:**
- В папке со скетчем создайте папку **`data`**
- Положите туда `index.html`
- Закройте монитор порта
- Нажмите **`Ctrl + Shift + P`** → выберите **"Upload LittleFS to Pico/ESP8266/ESP32"**

### 5. Настройка Wi-Fi

<a id="5-настройка-wi-fi"></a>
1. Переименуйте **`secrets.h-example`** в **`secrets.h`**
2. Откройте и впишите свои данные:
   ```cpp
   #define SECRET_SSID "Имя_вашей_WiFi_сети"
   #define SECRET_PASS "Пароль_от_WiFi"


## 🚀 Использование
<a id="использование"></a>
1. Подключите NodeMCU к компьютеру
2. В Arduino IDE выберите **плату** и **COM-порт**
3. Загрузите скетч в плату (➡️)
4. Откройте монитор порта, увидите IP-адрес, скопируйте его и вставьте в браузер. IP пример: http://192.168.0.101/
