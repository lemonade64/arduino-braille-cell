#ifndef HAPTIC_MODULE_H
#define HAPTIC_MODULE_H

#include <Wire.h>
#include "Adafruit_DRV2605.h"

/**
 * @enum HapticEffect
 * @brief Enumeration of available haptic effects.
 */

enum class HapticEffect {
  ON,
  OFF,
  CAPTURE_PHOTO,
  SOLENOID_ON,
  SOLENOID_OFF
};
class HapticModule {
public:
  /**
   * @brief Initialises the haptic module.
   * 
   * This method sets up the I2C communication and configures the DRV2605 driver.
   */
  static void init();
    /**
   * @brief Plays a specified haptic effect.
   * 
   * @param effect The HapticEffect to be played.
   */
  static void playEffect(HapticEffect effect);

private:
  static Adafruit_DRV2605 drv;
};

#endif
