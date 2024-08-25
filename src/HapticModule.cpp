#include "HapticModule.h"

Adafruit_DRV2605 HapticModule::drv;

void HapticModule::init() {
  Wire.begin(13, 12);
  if (!drv.begin()) {
    log_e("DRV2605 Failed");
    while (1) delay(10);
  }

  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);
}

void HapticModule::playEffect(HapticEffect effect) {
  switch (effect) {
    case HapticEffect::ON:
      drv.setWaveform(0, 82);
      break;
    case HapticEffect::OFF:
      drv.setWaveform(0, 70);
      break;
    case HapticEffect::CAPTURE_PHOTO:
      drv.setWaveform(0, 1);
      break;
    case HapticEffect::SOLENOID_ON:
    case HapticEffect::SOLENOID_OFF:
      drv.setWaveform(0, 14);
      break;
  }
  
  drv.setWaveform(1, 0);
  drv.go();
}
