/**
 * @file WiFiManager.cpp
 * @brief Implementation of the WiFiManager class.
 */

#include "config.h"
#include "secret.h"
#include "connectivity/WiFiManager.h"

WiFiManager::WiFiManager() : _lastAttempt(0) {}

bool WiFiManager::connect() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    DEBUG_PRINTLN("Connecting to WiFi...");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - start) < WIFI_TIMEOUT) {
        delay(500);
        DEBUG_PRINT(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        DEBUG_PRINTLN("");
        DEBUG_PRINT("Connected. IP address: ");
        DEBUG_PRINTLN(WiFi.localIP());
        return true;
    }
    DEBUG_PRINTLN("");
    DEBUG_PRINTLN("WiFi connection failed");
    return false;
}

bool WiFiManager::isConnected() const {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::loop() {
    // Attempt reconnection only after the configured retry interval
    if (!isConnected() && (millis() - _lastAttempt) > WIFI_RETRY_INTERVAL) {
        _lastAttempt = millis();
        connect();
    }
}