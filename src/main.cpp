#include <Arduino.h>

#include <string>

#include "PowerModule.h"
#include "WiFiModule.h"
#include "CameraModule.h"
#include "OCRModule.h"
#include "SolenoidModule.h"
#include "HapticModule.h"
#include "ButtonModule.h"

/**
 * @brief Processes a captured image and converts it to Braille.
 *
 * @see Camera::capturePhoto()
 * @see OCRModule::performOCR()
 * @see HapticModule::playEffect()
 * @see SolenoidModule::displayBraille()
 */
void processImageToBraille();

void processImageToBraille() {
  HapticModule::playEffect(HapticEffect::ON);

  const std::string base64String = Camera::capturePhoto();

  const std::string ocrResult = OCRModule::performOCR(base64String);
  
  HapticModule::playEffect(HapticEffect::SOLENOID_ON);
  SolenoidModule::displayBraille(ocrResult);

  HapticModule::playEffect(HapticEffect::OFF);
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  PowerModule::init();

  WiFiModule::connect();
  WiFiModule::setupAutoReconnect(true);

  HapticModule::init();

  ButtonModule::init(2);

  Camera::setup();
  const std::string base64String = Camera::capturePhoto();

  const std::string ocrResult = OCRModule::performOCR(base64String);
  
  SolenoidModule::setup();
  SolenoidModule::displayBraille(ocrResult);

  HapticModule::playEffect(HapticEffect::OFF);
}

void loop() {
  if (!WiFiModule::isConnected()) {
    WiFiModule::reconnect();
  }

  ButtonModule::update();
  if (ButtonModule::isPressed()) {
    processImageToBraille();
  }

  delay(100);
}