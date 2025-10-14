/**
 * @file WiFiManager.h
 * @brief Helper class to manage WiFi connectivity for the ESP32.
 *
 * Provides a non‑blocking API to connect and maintain a WiFi connection.
 */

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

/**
 * @class WiFiManager
 * @brief Encapsulates connection and reconnection logic for WiFi.
 */
class WiFiManager {
public:
    WiFiManager();

    /**
     * Attempt to connect to the configured WiFi network. This method
     * blocks until either a connection is established or the timeout
     * defined in config.h expires.
     *
     * @return true if connected, false otherwise
     */
    bool connect();

    /**
     * Return whether the device is currently connected to WiFi.
     */
    bool isConnected() const;

    /**
     * Should be called frequently in loop(). Handles reconnection
     * attempts if the connection is lost.
     */
    void loop();

private:
    unsigned long _lastAttempt; ///< Time of the last reconnection attempt
};

#endif // WIFI_MANAGER_H