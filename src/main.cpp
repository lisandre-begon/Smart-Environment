/**
 * @file main.cpp
 * @brief Entry point for the Smart Environment Node firmware.
 *
 * The firmware reads temperature, humidity and light levels, filters the
 * readings, displays them on an OLED screen, indicates alerts via an LED
 * and periodically uploads the data to a cloud service.
 */

#include <Arduino.h>
#include "config.h"

#include "sensors/DHTSensor.h"
#include "sensors/LightSensor.h"
#include "display/OledDisplay.h"
#include "connectivity/WiFiManager.h"
#include "connectivity/CloudUploader.h"
#include "utils/DataFilter.h"
#include "utils/AlertManager.h"

// Instantiate global objects
DHTSensor dhtSensor;
LightSensor lightSensor;
OledDisplay oledDisplay;
WiFiManager wifiManager;
CloudUploader cloudUploader;
DataFilter tempFilter;
DataFilter humidFilter;
DataFilter lightFilter;
AlertManager alertManager;

// Timing variables
static unsigned long lastSensorTime = 0;
static unsigned long lastDisplayTime = 0;
static unsigned long lastUploadTime = 0;

void setup() {
    // Initialize serial for debugging
    Serial.begin(SERIAL_BAUD_RATE);
    DEBUG_PRINTLN();
    DEBUG_PRINTLN(F("Starting " DEVICE_NAME " (FW " FIRMWARE_VERSION ")"));

    // Initialise sensors
    dhtSensor.begin();
    lightSensor.begin();

    // Initialise display
    if (!oledDisplay.begin()) {
        DEBUG_PRINTLN(F("OLED init failed"));
    }

    // Setup alert LED
    alertManager.begin();

    // Establish WiFi connection
    wifiManager.connect();

    // Initialise cloud uploader
    cloudUploader.begin();

    // Clear initial display
    oledDisplay.showStatus("Booting...");
}

void loop() {
    unsigned long now = millis();

    // Maintain WiFi connection
    wifiManager.loop();

    // Read sensors at configured interval
    if (now - lastSensorTime >= SENSOR_READ_INTERVAL) {
        lastSensorTime = now;
        float t = dhtSensor.readTemperature();
        float h = dhtSensor.readHumidity();
        int   l = lightSensor.readRaw();
        // Add valid readings to filters
        if (DHTSensor::isValid(t, TEMP_MIN_VALID, TEMP_MAX_VALID)) {
            tempFilter.addValue(t);
        }
        if (DHTSensor::isValid(h, HUMID_MIN_VALID, HUMID_MAX_VALID)) {
            humidFilter.addValue(h);
        }
        if (l >= LIGHT_MIN_VALID && l <= LIGHT_MAX_VALID) {
            lightFilter.addValue(static_cast<float>(l));
        }
    }

    // Update display at configured interval
    if (now - lastDisplayTime >= DISPLAY_UPDATE_INTERVAL) {
        lastDisplayTime = now;
        float avgTemp  = tempFilter.getAverage();
        float avgHumid = humidFilter.getAverage();
        int   avgLight = static_cast<int>(lightFilter.getAverage());
        oledDisplay.showReadings(avgTemp, avgHumid, avgLight);
        // Update alerts and LED
        alertManager.update(avgTemp, avgHumid, avgLight);
    }

    // Upload data at configured interval
    if (now - lastUploadTime >= CLOUD_UPLOAD_INTERVAL) {
        lastUploadTime = now;
        if (wifiManager.isConnected()) {
            float avgTemp  = tempFilter.getAverage();
            float avgHumid = humidFilter.getAverage();
            int   avgLight = static_cast<int>(lightFilter.getAverage());
            cloudUploader.upload(avgTemp, avgHumid, avgLight);
        }
    }

    // Small delay to prevent watchdog resets on some boards
    delay(10);
}