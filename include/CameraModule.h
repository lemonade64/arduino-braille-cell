#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H

#include <Arduino.h>
#include <esp_camera.h>
#include <soc/rtc_cntl_reg.h>

#include <string>
#include <base64.h>

#include "PinConfig.h"

class Camera {
public:
    /**
     * @brief Initialises and configures the ESP32 camera.
     * 
     * This method sets up the camera pins, configures the camera settings
     * and initialises the ESP32 camera hardware.
     */
    static void setup();

    /**
     * @brief Captures a photo using the ESP32 camera.
     * 
     * @return std::string Base64 encoded string of the captured image.
     * 
     * This method captures an image using the camera, converts it to a base64 encoded string
     * and returns the result. If the camera fails, it returns an error message.
     */
    static std::string capturePhoto();

private:
    /**
     * @brief Configures advanced settings for the camera sensor.
     * 
     * @param s Pointer to the camera sensor settings.
     * 
     * This private method is used to optimise various camera parameters
     */
    static void configureSettings(sensor_t* s);
};

#endif
