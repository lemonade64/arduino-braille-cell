#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include <Arduino.h>
#include <WiFi.h>

class WiFiModule {
public:
    static void connect();
    static void disconnect();
    static bool isConnected();
    static void reconnect();
    static void setupAutoReconnect(bool enable);
    static String getLocalIP();

private:
    static void logConnectionStatus();
};

#endif