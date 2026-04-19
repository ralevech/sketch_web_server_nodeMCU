// (LED реализация)
#include "ledControl.h"
#include <Arduino.h>

bool led1State = false;
bool led2State = false;

void initLEDs() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  digitalWrite(LED1_PIN, HIGH);  // Выключен
  digitalWrite(LED2_PIN, HIGH);  // Выключен
  
  Serial.println("LEDs initialized");
}

// LED1 (встроенный)
void toggleLED1() {
  led1State = !led1State;
  
  if(led1State) {
    digitalWrite(LED1_PIN, LOW);
    Serial.println("LED1 ON");
  } else {
    digitalWrite(LED1_PIN, HIGH);
    Serial.println("LED1 OFF");
  }
}

void setLED1(bool state) {
  led1State = state;
  digitalWrite(LED1_PIN, state ? LOW : HIGH);
  Serial.print("LED1 set to ");
  Serial.println(state ? "ON" : "OFF");
}

String getLED1Status() {
  return led1State ? "ON" : "OFF";
}

// LED2 (внешний)
void toggleLED2() {
  led2State = !led2State;
  
  if(led2State) {
    digitalWrite(LED2_PIN, LOW);
    Serial.println("LED2 ON");
  } else {
    digitalWrite(LED2_PIN, HIGH);
    Serial.println("LED2 OFF");
  }
}

void setLED2(bool state) {
  led2State = state;
  digitalWrite(LED2_PIN, state ? LOW : HIGH);
  Serial.print("LED2 set to ");
  Serial.println(state ? "ON" : "OFF");
}

String getLED2Status() {
  return led2State ? "ON" : "OFF";
}

