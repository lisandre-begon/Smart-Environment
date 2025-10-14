/**
 * @file DHTSensor.h
 * @brief Wrapper class around the Adafruit DHT library for reading
 *        temperature and humidity from a DHT11 sensor.
 *
 * The class encapsulates initialization, reading and basic validation of
 * sensor values. It defers filtering and thresholding to other modules.
 */

#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <DHT.h>
#include "config.h"

/**
 * @class DHTSensor
 * @brief Provides an interface to a DHT temperature/humidity sensor.
 */
class DHTSensor {
public:
    /**
     * Construct a new DHTSensor object.
     *
     * @param pin  The GPIO pin used for the sensor data line.
     * @param type The DHT sensor type (e.g. DHT11 or DHT22).
     */
    DHTSensor(uint8_t pin = DHT_PIN, uint8_t type = DHT_TYPE);

    /**
     * Initialise the underlying DHT library. Must be called in setup().
     */
    void begin();

    /**
     * Read the temperature in degrees Celsius.
     * @return The measured temperature, or NAN if invalid.
     */
    float readTemperature();

    /**
     * Read the relative humidity in percent.
     * @return The measured humidity, or NAN if invalid.
     */
    float readHumidity();

    /**
     * Helper to test whether a value lies within a valid range.
     *
     * @param value    Value to test
     * @param minValid Minimum acceptable value (inclusive)
     * @param maxValid Maximum acceptable value (inclusive)
     * @return true if value is finite and within bounds, false otherwise
     */
    static bool isValid(float value, float minValid, float maxValid);

private:
    DHT dht;  ///< Instance of the Adafruit DHT driver
};

#endif // DHT_SENSOR_H