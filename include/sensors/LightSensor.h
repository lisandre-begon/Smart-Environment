/**
 * @file LightSensor.h
 * @brief Simple driver for an analog light sensor (LDR).
 *
 * The light sensor consists of a voltage divider formed by an LDR and a resistor
 * connected to an ADC pin. This class abstracts the raw analog reading
 * and provides basic range checking.
 */

#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>
#include "config.h"

/**
 * @class LightSensor
 * @brief Reads an analog value from a light dependent resistor (LDR).
 */
class LightSensor {
public:
    /**
     * Construct a new LightSensor object.
     *
     * @param pin The ADC pin connected to the LDR voltage divider.
     */
    explicit LightSensor(uint8_t pin = LDR_PIN);

    /**
     * Initialise the ADC resolution. Call this once in setup().
     */
    void begin();

    /**
     * Read the raw ADC value from the LDR. The result is clipped to
     * LIGHT_MIN_VALID/LIGHT_MAX_VALID.
     * @return A value between 0 and 4095 (12‑bit resolution).
     */
    int readRaw();

    /**
     * Read the normalised light level. Currently this simply returns
     * the raw value but could be extended to return a percentage or lux.
     * @return The processed light level.
     */
    int readNormalized();

private:
    uint8_t _pin; ///< ADC pin used to sample the LDR
};

#endif // LIGHT_SENSOR_H