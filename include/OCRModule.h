#ifndef OCR_MODULE_H
#define OCR_MODULE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <string>

#include <ArduinoJson.h>

#include "URLSecrets.h"

class OCRModule {
public:
    static std::string performOCR(const std::string& base64String);

private:
    static std::string httpPOST(const char* url, const char* jsonData);
};

#endif
