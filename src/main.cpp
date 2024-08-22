#include <Arduino.h>

#include <string>

#include "PowerModule.h"
#include "WiFiModule.h"
#include "CameraModule.h"
#include "OCRModule.h"
#include "SolenoidModule.h"

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  PowerModule::init();

  WiFiModule::connect();
  WiFiModule::setupAutoReconnect(true);

  Camera::setup();
  const std::string base64String = Camera::capturePhoto();

  const std::string ocrResult = OCRModule::performOCR(base64String);
  
  SolenoidModule::setup();
  SolenoidModule::displayBraille(ocrResult);
}

void loop() {
  delay(1000);
  if (!WiFiModule::isConnected()) {
    WiFiModule::reconnect();
  }
}