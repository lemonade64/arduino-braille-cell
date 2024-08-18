#include <Arduino.h>

#include <esp_bt.h>
#include <esp_wifi.h>
#include <WiFi.h>

#include <driver/adc.h>
#include <driver/rtc_io.h>
#include <soc/rtc_cntl_reg.h>
#include <soc/soc.h>

#include <base64.h>
#include <string>

#include "WiFiSecrets.h"

WiFiClient client;

/**
 * @brief Connects to WiFi using credentials from WiFiSecrets.h.
 * 
 * Attempts to connect to WiFi for a maximum of 10 attempts before entering deep sleep if unsuccessful.
 */
void connectWiFi();

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

  connectWiFi();
}

void loop() {
  delay(1000);
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  log_e("Connecting to %s", WIFI_SSID);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
    delay(1000);
    log_e(".");
    attempts++;
  }
  if (WiFi.status() != WL_CONNECTED) {
    log_e("Failed to connect to: %s", WIFI_SSID);
    deepSleep();
  } else {
    log_e("WiFi Connected. IP Address: %s", WiFi.localIP().toString().c_str());
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
  }
}

void deepSleep()  {
  log_e("Entering Deep Sleep...");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  esp_wifi_stop();

  adc_power_release();

  esp_deep_sleep_start();
}