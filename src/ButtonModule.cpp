#include "ButtonModule.h"
#include <Arduino.h>

int ButtonModule::buttonPin = 0;
int ButtonModule::buttonState = HIGH;

void ButtonModule::init(int pin) {
  buttonPin = pin;
  pinMode(buttonPin, INPUT_PULLUP);
}

bool ButtonModule::isPressed() {
  return buttonState == LOW;
}

void ButtonModule::update() {
  buttonState = digitalRead(buttonPin);
}