#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include <Arduino.h>

class WiFiModule {
public:
    /**
     * @brief Connects to the WiFi network.
     *
     * This method attempts to connect to the WiFi network using credentials
     * defined in a WiFiSecrets.h.
     */
    static void connect();

    /**
     * @brief Disconnects from the current WiFi network.
     *
     * This method disconnects the ESP32 from the current WiFi network
     * and turns off the WiFi radio.
     */
    static void disconnect();

    /**
     * @brief Checks if the ESP32 is currently connected to a WiFi network.
     *
     * @return bool true if connected, false otherwise.
     */
    static bool isConnected();

    /**
     * @brief Attempts to reconnect to the WiFi network.
     *
     * This method attempts to reestablish the WiFi connection if it has been lost.
     */
    static void reconnect();

    /**
     * @brief Configures automatic reconnection to WiFi.
     *
     * @param enable if true, enables auto-reconnect feature; if false, disables it.
     */
    static void setupAutoReconnect(bool enable);

    /**
     * @brief Retrieves the local IP address of the ESP32.
     *
     * @return String Local IP address as a string.
     */
    static String getLocalIP();

private:
    /**
     * @brief Logs the current WiFi connection status.
     *
     * This private method is used internally to log whether the connection
     * was successful and if so, what the assigned IP address is.
     */
    static void logConnectionStatus();
};

#endif