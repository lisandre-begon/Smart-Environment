/**
 * @file config.h
 * @brief Global configuration and pin definitions for Smart Environment Node
 *
 * This header centralizes all hardware pin assignments, timing constants,
 * network credentials and system parameters used throughout the project.
 * By keeping these definitions in a single place the code becomes easier
 * to maintain and portable between different boards or environments.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================================
// HARDWARE PIN DEFINITIONS
// ============================================================================

// DHT11 Sensor
#define DHT_PIN         4           // GPIO4 - DHT11 data pin
#define DHT_TYPE        DHT11       // Sensor type

// Light Sensor (LDR)
#define LDR_PIN         34          // GPIO34 (ADC1_CH6) - Analog input
#define LDR_RESOLUTION  12          // 12‑bit ADC resolution (0‑4095)

// OLED Display (I2C)
#define OLED_SDA        21          // GPIO21 - I2C Data
#define OLED_SCL        22          // GPIO22 - I2C Clock
#define OLED_WIDTH      128         // Display width in pixels
#define OLED_HEIGHT     64          // Display height in pixels
#define OLED_ADDRESS    0x3C        // I2C address

// Alert LED
#define LED_PIN         2           // GPIO2 - Built‑in LED
#define LED_ALERT_PIN   LED_PIN     // Alias for clarity

// ============================================================================
// TIMING CONSTANTS (in milliseconds)
// ============================================================================

#define SENSOR_READ_INTERVAL    5000    // Read sensors every 5 seconds
#define DISPLAY_UPDATE_INTERVAL 2000    // Update display every 2 seconds
#define CLOUD_UPLOAD_INTERVAL   30000   // Upload to cloud every 30 seconds
#define WIFI_TIMEOUT            15000   // WiFi connection timeout
#define WIFI_RETRY_INTERVAL     30000   // Retry WiFi every 30 seconds if disconnected

// ============================================================================
// DATA FILTERING
// ============================================================================

#define FILTER_WINDOW_SIZE      5       // Moving average window size
#define TEMP_MIN_VALID          -40.0f  // Minimum valid temperature (°C)
#define TEMP_MAX_VALID          80.0f   // Maximum valid temperature (°C)
#define HUMID_MIN_VALID         0.0f    // Minimum valid humidity (%)
#define HUMID_MAX_VALID         100.0f  // Maximum valid humidity (%)
#define LIGHT_MIN_VALID         0       // Minimum valid light reading
#define LIGHT_MAX_VALID         4095    // Maximum valid light reading

// ============================================================================
// ALERT THRESHOLDS
// ============================================================================

#define TEMP_HIGH_THRESHOLD     30.0f   // High temperature alert (°C)
#define TEMP_LOW_THRESHOLD      15.0f   // Low temperature alert (°C)
#define HUMID_HIGH_THRESHOLD    80.0f   // High humidity alert (%)
#define HUMID_LOW_THRESHOLD     30.0f   // Low humidity alert (%)
#define LIGHT_LOW_THRESHOLD     500     // Low light alert (darkness)

// ============================================================================
// NETWORK CONFIGURATION
// ============================================================================

// ThingSpeak Configuration

#define THINGSPEAK_SERVER       "api.thingspeak.com"
#define THINGSPEAK_PORT         80

#ifndef MQTT_PORT
#define MQTT_PORT               1883
#endif

#define MQTT_CLIENT_ID          "ESP32_EnvNode"
#define MQTT_TOPIC_TEMP         "envnode/temperature"
#define MQTT_TOPIC_HUMID        "envnode/humidity"
#define MQTT_TOPIC_LIGHT        "envnode/light"
#define MQTT_TOPIC_STATUS       "envnode/status"

// ============================================================================
// SERIAL DEBUGGING
// ============================================================================

#define SERIAL_BAUD_RATE        115200
#define DEBUG_ENABLED           true    // Enable/disable debug output

#if DEBUG_ENABLED
    #define DEBUG_PRINT(x)      Serial.print(x)
    #define DEBUG_PRINTLN(x)    Serial.println(x)
    #define DEBUG_PRINTF(...)   Serial.printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
    #define DEBUG_PRINTF(...)
#endif

// ============================================================================
// SYSTEM INFORMATION
// ============================================================================

#define FIRMWARE_VERSION        "1.0.0"
#define DEVICE_NAME             "Smart Environment Node"
#define HARDWARE_REVISION       "v1.0"

// ============================================================================
// OPTIONAL: Include secrets file (add secrets.h to .gitignore!)
// ============================================================================

#ifdef USE_SECRETS_FILE
#include "secrets.h"
#endif

#endif // CONFIG_H