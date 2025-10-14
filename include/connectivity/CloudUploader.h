/**
 * @file CloudUploader.h
 * @brief Abstracts uploading sensor data to a cloud service.
 *
 * This implementation supports both HTTP uploads to ThingSpeak and
 * MQTT publishes to a broker. The active mechanism is selected at
 * runtime based on whether a valid ThingSpeak API key is defined.
 */

#ifndef CLOUD_UPLOADER_H
#define CLOUD_UPLOADER_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <PubSubClient.h>
#include "config.h"

/**
 * @class CloudUploader
 * @brief Handles uploading sensor readings to ThingSpeak or publishing
 *        them via MQTT.
 */
class CloudUploader {
public:
    CloudUploader();
    
    /**
     * Initialise internal clients. Should be called after WiFi is up.
     */
    void begin();

    /**
     * Upload a new set of sensor readings. Depending on configuration
     * this will either perform an HTTP GET request to ThingSpeak or
     * publish values to multiple MQTT topics.
     *
     * @param temperature Filtered temperature reading in °C
     * @param humidity    Filtered humidity reading in %
     * @param light       Filtered light reading (0‑4095)
     */
    void upload(float temperature, float humidity, int light);

private:
    WiFiClient _wifiClient;
    HTTPClient _httpClient;
    PubSubClient _mqttClient;

    void uploadThingSpeak(float temperature, float humidity, int light);
    void uploadMQTT(float temperature, float humidity, int light);
};

#endif // CLOUD_UPLOADER_H