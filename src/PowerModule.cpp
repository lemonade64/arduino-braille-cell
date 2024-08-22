#include "PowerModule.h"
#include "WiFiModule.h"

void PowerModule::init() {
    setCpuFrequencyMhz(80);
    btStop();
    esp_bt_controller_disable();
}

void PowerModule::deepSleep() {
    log_e("Entering Deep Sleep...");
    WiFiModule::disconnect();
    esp_wifi_stop();

    adc_power_release();

    esp_deep_sleep_start();
}