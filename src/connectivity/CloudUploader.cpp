/**
 * @file CloudUploader.cpp
 * @brief Implementation of CloudUploader for HTTP/MQTT uploads.
 */

#include "config.h"
#include "secret.h"
#include "connectivity/CloudUploader.h"

CloudUploader::CloudUploader() : _mqttClient(_wifiClient) {}

void CloudUploader::begin() {
    // Configure MQTT server; connection will be attempted lazily on publish
    _mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

void CloudUploader::upload(float temperature, float humidity, int light) {
    // Determine whether to use ThingSpeak: require API key not equal to default
    const bool useThingSpeak = (strlen(THINGSPEAK_API_KEY) > 0 &&
                                String(THINGSPEAK_API_KEY) != String("YourThingSpeakAPIKey"));
    if (useThingSpeak) {
        uploadThingSpeak(temperature, humidity, light);
    } else {
        uploadMQTT(temperature, humidity, light);
    }
}

void CloudUploader::uploadThingSpeak(float temperature, float humidity, int light) {
    if (WiFi.status() != WL_CONNECTED) {
        return; // Cannot upload without WiFi
    }
    // Build the URL with query parameters for fields 1‑3
    String url = String("http://") + THINGSPEAK_SERVER + "/update?api_key=" + THINGSPEAK_API_KEY;
    url += "&field1=" + String(temperature, 2);
    url += "&field2=" + String(humidity, 2);
    url += "&field3=" + String(light);
    _httpClient.begin(_wifiClient, url);
    int httpCode = _httpClient.GET();
    // Optionally print the server response for debugging
    DEBUG_PRINTF("ThingSpeak HTTP response code: %d\n", httpCode);
    _httpClient.end();
}

void CloudUploader::uploadMQTT(float temperature, float humidity, int light) {
    // Ensure the MQTT client is connected
    if (!_mqttClient.connected()) {
        // Create a unique client ID for this session
        String clientId = String(MQTT_CLIENT_ID) + String("-") + String(millis(), HEX);
        _mqttClient.connect(clientId.c_str());
    }
    if (!_mqttClient.connected()) {
        // Failed to connect; skip publishing
        DEBUG_PRINTLN("MQTT connection failed");
        return;
    }
    // Publish values to their respective topics
    char payload[16];
    dtostrf(temperature, 6, 2, payload);
    _mqttClient.publish(MQTT_TOPIC_TEMP, payload);
    dtostrf(humidity, 6, 2, payload);
    _mqttClient.publish(MQTT_TOPIC_HUMID, payload);
    itoa(light, payload, 10);
    _mqttClient.publish(MQTT_TOPIC_LIGHT, payload);
    // Also publish a status message containing timestamp
    String status = String("OK ") + millis();
    _mqttClient.publish(MQTT_TOPIC_STATUS, status.c_str());
    // Allow the MQTT client to process outgoing data
    _mqttClient.loop();
}