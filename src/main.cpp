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
#include <Adafruit_MCP23X17.h>

#include "WiFiModule.h"
#include "CameraModule.h"

/**
 * @brief Sets up the MCP23017 I2C port expander.
 * 
 * Initialises the I2C communication with the MCP23017 chip and configures
 * the first 6 pins as outputs. If initialisation fails, it tries again.
 */
void setupMCP23017();

/**
 * @brief Configures the pins for the Braille display.
 * 
 * Sets up the control pins (1-6) of the MCP23017 as outputs for controlling
 * the Braille dots.
 */
void setupBraille();

/**
 * @brief Displays the given text in Braille.
 * 
 * Converts each character of the input text to its Braille representation
 * and activates the corresponding dots on the Braille display. Each character
 * is displayed for 1 second before moving to the next.
 * 
 * @param text The string to be displayed in Braille.
 */
void displayBraille(const std::string text);

/**
 * @brief Puts the ESP32 into deep sleep mode.
 * 
 * Disconnects WiFi, releases ADC power and starts deep sleep.
 */
void deepSleep();

Adafruit_MCP23X17 mcp;

const int braille[26][6] = {
  {1,0,0,0,0,0},
  {1,1,0,0,0,0},
  {1,0,0,1,0,0},
  {1,0,0,1,1,0},
  {1,0,0,0,1,0},
  {1,1,0,1,0,0},
  {1,1,0,1,1,0},
  {1,1,0,0,1,0},
  {0,1,0,1,0,0},
  {0,1,0,1,1,0},
  {1,0,1,0,0,0},
  {1,1,1,0,0,0},
  {1,0,1,1,0,0},
  {1,0,1,1,1,0},
  {1,0,1,0,1,0},
  {1,1,1,1,0,0},
  {1,1,1,1,1,0},
  {1,1,1,0,1,0},
  {0,1,1,1,0,0},
  {0,1,1,1,1,0},
  {1,0,1,0,0,1},
  {1,1,1,0,0,1},
  {0,1,0,1,1,1},
  {1,0,1,1,0,1},
  {1,0,1,1,1,1},
  {1,0,1,0,1,1},
};

const int controlPins[6] = {1,2,3,4,5,6};

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

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
  
  setupMCP23017();

  setupBraille();
  displayBraille(ocrResult);
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


void setupMCP23017() {
  Wire.begin(15,14);
  if (!mcp.begin_I2C()) {
    log_e("MCP23017 Error");
    while (1);
  }
  for (int i = 1; i < 6; i++) {
    mcp.pinMode(i, OUTPUT);
  }
}

void setupBraille() {
  for(int i=0; i<6; i++){
    mcp.pinMode(controlPins[i], OUTPUT);
  }
}

void displayBraille(const std::string text) {
  int length = text.length();
  char letter;
  int index;

  for(int i=0; i<length; i++){
    letter = text[i];
    for(int j = 0; j<26; j++){
      if(letter == alphabet[j]){
        index = j;
        break;
      }
    }
    
    for(int k = 0; k<=5; k++){
      mcp.digitalWrite(controlPins[k], braille[index][k]);
    }
    
    delay(1000);
  } 
}
