#ifndef BUTTON_MODULE_H
#define BUTTON_MODULE_H

class ButtonModule {
public:
  static void init(int pin);
  static bool isPressed();
  static void update();

private:
  static int buttonPin;
  static int buttonState;
};

#endif
