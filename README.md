<a href="https://github.com/ralevech/sketch_web_server_nodeMCU">
    <img src="https://github.com/user-attachments/assets/8783f561-0cab-40a7-950d-5b1df280466e" width="360" alt="Логотип проекта">
</a>

# 🌐 Веб-сервер на NodeMCU для управления нагрузкой через браузер

[![GitHub license](https://img.shields.io/github/license/ralevech/sketch_web_server_nodeMCU)](https://github.com/ralevech/sketch_web_server_nodeMCU/blob/main/LICENSE)
[![Languages](https://img.shields.io/github/languages/top/ralevech/sketch_web_server_nodeMCU)](https://github.com/ralevech/sketch_web_server_nodeMCU)
[![Platform](https://img.shields.io/badge/platform-ESP8266-blue)](https://www.espressif.com/en/products/socs/esp8266)
[![Arduino IDE](https://img.shields.io/badge/IDE-Arduino%20IDE-00979D)](https://www.arduino.cc/en/software)

Простой и эффективный веб-сервер на базе платы **NodeMCU (ESP8266)**. Проект позволяет подключаться к плате через Wi-Fi и управлять подключенной нагрузкой (например, светодиодами или реле) прямо из браузера на вашем компьютере или смартфоне. Идеальное решение для старта в мир интернета вещей (IoT) и домашней автоматизации.

[![Watch the video](https://img.shields.io/badge/📺-Демонстрация%20работы-green)](https://github.com/ralevech/sketch_web_server_nodeMCU)
[![Get Started](https://img.shields.io/badge/🚀-Начать%20сейчас-blue)](#-использование)

---

## 📋 Содержание

*   [О проекте](#-о-проекте)
*   [Возможности](#-возможности)
*   [Аппаратное обеспечение](#-аппаратное-обеспечение)
*   [Программное обеспечение](#-программное-обеспечение)
    *   [Среда разработки](#1-среда-разработки)
    *   [Драйверы USB-UART](#2-драйвер-для-соединения-usb-с-платой-nodemcu)
    *   [Необходимые библиотеки](#3-библиотеки-для-создания-web-сервера)
    *   [Плагин для загрузки файлов](#arduino-littlefs-upload-163vsix)
    *   [Настройка Wi-Fi](#4-настройка-wi-fi)
*   [Использование](#-использование)
*   [Лицензия](#-лицензия)

---

## 💡 О проекте

Этот скетч превращает вашу плату NodeMCU в точку доступа или подключает её к существующей Wi-Fi сети, создавая простой веб-интерфейс. Управление нагрузкой происходит путем перехода по соответствующим ссылкам в браузере.

<details>
  <summary>📁 Посмотреть структуру проекта (нажмите, чтобы развернуть)</summary>
