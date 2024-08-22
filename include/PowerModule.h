#ifndef POWER_MODULE_H
#define POWER_MODULE_H

#include <Arduino.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <driver/adc.h>

class PowerModule {
public:
    static void init();

    static void deepSleep();
};

#endif
