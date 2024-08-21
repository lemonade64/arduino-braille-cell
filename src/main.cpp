#include <Arduino.h>

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <driver/adc.h>
#include <driver/rtc_io.h>
#include <soc/rtc_cntl_reg.h>
#include <soc/soc.h>
#include <string>

#include <ArduinoJson.h>

#include "WiFiModule.h"
#include "CameraModule.h"
#include "SolenoidModule.h"

/**
 * @brief Puts the ESP32 into deep sleep mode.
 * 
 * Disconnects WiFi, releases ADC power and starts deep sleep.
 */
void deepSleep();

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  setCpuFrequencyMhz(80);
  btStop();
  esp_bt_controller_disable();

  WiFiModule::connect();
  WiFiModule::setupAutoReconnect(true);

  Camera::setup();
  std::string base64String = Camera::capturePhoto();

  log_e("Image Captured: %s", base64String.c_str());

  const std::string ocrResult = "";
  
  SolenoidModule::setup();
  SolenoidModule::displayBraille(ocrResult);
}

void loop() {
    delay(1000);
    if (!WiFiModule::isConnected()) {
        WiFiModule::reconnect();
    }
}

void deepSleep()  {
  log_e("Entering Deep Sleep...");
  WiFiModule::disconnect();
  esp_wifi_stop();

  adc_power_release();

  esp_deep_sleep_start();
}