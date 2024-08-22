#ifndef OCR_MODULE_H
#define OCR_MODULE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <string>

#include <ArduinoJson.h>

#include "URLSecrets.h"

class OCRModule {
public:
    /**
     * @brief Performs OCR on a base64 encoded image.
     * 
     * This method sends a image through base64 encoded image data to an OCR 
     * endpoint and returns the sanitizsd text.
     * 
     * @param base64String Base64 encoded image data.
     * @return std::string Sanitised text result.
     */
    static std::string performOCR(const std::string& base64String);

private:
    /**
     * @brief Sends an HTTP POST request.
     * 
     * This method sends an HTTP POST request to the specified URL with the given JSON data.
     * 
     * @param url URL for the POST request.
     * @param jsonData JSON data for request body.
     * @return std::string Response from the server.
     */
    static std::string httpPOST(const char* url, const char* jsonData);
};

#endif
