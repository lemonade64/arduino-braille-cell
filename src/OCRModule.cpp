#include "OCRModule.h"

std::string OCRModule::performOCR(const std::string& base64String) {
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

std::string OCRModule::httpPOST(const char* url, const char* jsonData) {
    HTTPClient http;
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