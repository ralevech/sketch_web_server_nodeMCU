// (LED управление)
#ifndef LED_CONTROL_H
#define LED_CONTROL_H
#include <Arduino.h>

// Пины для LED
#define LED1_PIN LED_BUILTIN  // Встроенный LED (D4 на NodeMCU)
#define LED2_PIN D1           // Внешний LED на пине D1 (GPIO5)

// Состояния LED
extern bool led1State;
extern bool led2State;

void initLEDs();
void toggleLED1();
void toggleLED2();
void setLED1(bool state);
void setLED2(bool state);
String getLED1Status();
String getLED2Status();

#endif