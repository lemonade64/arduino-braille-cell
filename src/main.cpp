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

#include "URLSecrets.h"

#include "WiFiModule.h"
#include "CameraModule.h"

/**
 * @brief Performs a HTTP POST request.
 * 
 * @param url URL of where the POST request is sent to.
 * @param jsonData JSON data to be sent in the request body.
 * @return std::string Response from the server.
 */
std::string httpPOST(const char * url, const char * jsonData);

/**
 * @brief Sends a base64 encoded image to an OCR API endpoint and retrieves the result.
 * 
 * @param base64String Base64 encoded image data.
 * @return std::string OCR result.
 */
std::string performOCR(const std::string& base64String);

/**
 * @brief Puts the ESP32 into deep sleep mode.
 * 
 * Disconnects WiFi, releases ADC power and starts deep sleep.
 */
void deepSleep();

HTTPClient http;

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

  const std::string ocrResult = performOCR(base64String);
}

void loop() {
  delay(1000);
  if (!WiFiModule::isConnected()) {
    WiFiModule::reconnect();
  }
}

std::string httpPOST(const char* url,
  const char* jsonData) {

  std::string response;
  if (http.begin(url)) {
    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    http.setReuse(true);
    http.setTimeout(15000);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonData);
    log_e("HTTP Response Code: %s", httpResponseCode);

    response = (httpResponseCode == HTTP_CODE_OK) ? http.getString().c_str() : http.errorToString(httpResponseCode).c_str();
  } else {
    response = "No HTTPS Connection";
  }
  http.end();
  return response;
}


std::string performOCR(const std::string& base64String) {
  const char* url = URL;

  std::string base64ImageData = "data:image/png;base64," + base64String;
  std::string jsonData = "{\"imageData\":\"" + base64ImageData + "\", \"outputOptions\": \"sanitised\"]}";
  const char* jsonDataCString = jsonData.c_str();
  log_e("Request Body: %s", jsonData.c_str());
  log_e("Sending OCR POST Request...");
  const std::string ocrResult = httpPOST(url, jsonDataCString);
  log_e("OCR POST Response: %s", ocrResult.c_str());
  if (ocrResult == "HTTP Request Error" || ocrResult == "No HTTP Connection") {
    return ocrResult;
  }

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, ocrResult);

  if (error) {
    log_e("Error: %s", error.c_str());
    return "deserializeJson() failed:";
  }

  const char* sanitisedText = doc["response"]["sanitised"];
  log_e("Sanitised Text: %s", sanitisedText);
  return sanitisedText;
}

void deepSleep()  {
  log_e("Entering Deep Sleep...");
  WiFiModule::disconnect();
  esp_wifi_stop();

  adc_power_release();

  esp_deep_sleep_start();
}