#ifndef POWER_MODULE_H
#define POWER_MODULE_H

#include <Arduino.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <driver/adc.h>

class PowerModule {
public:
    /**
     * @brief Initialises power efficient settings.
     * 
     * This method sets the CPU frequency to 80MHz and disables Bluetooth
     * to reduce power consumption.
     */
    static void init();

    /**
     * @brief Puts the device into deep sleep mode.
     */
    static void deepSleep();
};

#endif
