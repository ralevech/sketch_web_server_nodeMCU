#pragma once

void setupPins() {
    // Цифровые выходы (по умолчанию). Для входа замените OUTPUT на INPUT.
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT); // Встроенный светодиод (NodeMCU)
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);

    // Пины UART (обычно не трогаем, раскомментируйте при необходимости)
    // pinMode(D9,  INPUT);  // RX — приём (вход)
    // pinMode(D10, OUTPUT); // TX — передача (выход)

    // Аналоговый вход
    pinMode(A0, INPUT);  // Чтение аналога (0–1023)
}