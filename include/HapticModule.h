#ifndef HAPTIC_MODULE_H
#define HAPTIC_MODULE_H

#include <Wire.h>
#include "Adafruit_DRV2605.h"

enum class HapticEffect {
  ON,
  OFF,
  CAPTURE_PHOTO,
  SOLENOID_ON,
  SOLENOID_OFF
};

class HapticModule {
public:
  static void init();
  static void playEffect(HapticEffect effect);

private:
  static Adafruit_DRV2605 drv;
};

#endif
