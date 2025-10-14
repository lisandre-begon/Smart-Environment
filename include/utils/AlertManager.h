/**
 * @file AlertManager.h
 * @brief Evaluates sensor values against thresholds and drives an alert LED.
 */

#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include <Arduino.h>
#include "config.h"

/**
 * Enumeration of possible alert conditions.
 */
enum AlertState {
    ALERT_OK,          ///< All readings within thresholds
    ALERT_TEMP_HIGH,   ///< Temperature above high threshold
    ALERT_TEMP_LOW,    ///< Temperature below low threshold
    ALERT_HUMID_HIGH,  ///< Humidity above high threshold
    ALERT_HUMID_LOW,   ///< Humidity below low threshold
    ALERT_LIGHT_LOW    ///< Light intensity below low threshold
};

/**
 * @class AlertManager
 * @brief Monitors sensor readings and indicates abnormal conditions via an LED.
 */
class AlertManager {
public:
    /**
     * Create a new AlertManager object.
     *
     * @param ledPin The GPIO pin driving the alert LED.
     */
    explicit AlertManager(uint8_t ledPin = LED_ALERT_PIN);

    /**
     * Initialise the LED pin. Must be called in setup().
     */
    void begin();

    /**
     * Update the alert state based on the latest sensor values. This will
     * set the LED accordingly.
     *
     * @param temperature Filtered temperature reading
     * @param humidity    Filtered humidity reading
     * @param light       Filtered light reading
     * @return The new alert state
     */
    AlertState update(float temperature, float humidity, int light);

    /**
     * Get the current alert state without modifying it.
     *
     * @return The current alert state
     */
    AlertState getState() const;

private:
    uint8_t _ledPin;         ///< Pin connected to the LED
    AlertState _state;       ///< Current alert state

    /**
     * Turn the LED on or off.
     *
     * @param on true to drive LED high, false to drive it low
     */
    void setLED(bool on);
};

#endif // ALERT_MANAGER_H