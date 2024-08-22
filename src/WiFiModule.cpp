#include "WiFiModule.h"

void WiFiModule::connect() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    log_i("Connecting to %s", WIFI_SSID);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
        delay(1000);
        log_i(".");
        attempts++;
    }
    logConnectionStatus();
}

void WiFiModule::disconnect() {
    log_i("Disconnecting from WiFi");
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}

bool WiFiModule::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiModule::reconnect() {
    if (!isConnected()) {
        log_i("Reconnecting to WiFi");
        WiFi.reconnect();
    }
}

void WiFiModule::setupAutoReconnect(bool enable) {
    WiFi.setAutoReconnect(enable);
    WiFi.persistent(enable);
}

String WiFiModule::getLocalIP() {
    return WiFi.localIP().toString();
}

void WiFiModule::logConnectionStatus() {
    if (isConnected()) {
        log_e("WiFi Connected. IP Address: %s", getLocalIP().c_str());
    } else {
        log_e("Failed to connect to WiFi");
    }

}