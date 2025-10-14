/**
 * @file LightSensor.cpp
 * @brief Implementation of the LightSensor class for reading from an LDR.
 */

#include "config.h"
#include "secret.h"
#include "sensors/LightSensor.h"

LightSensor::LightSensor(uint8_t pin) : _pin(pin) {}

void LightSensor::begin() {
    // Configure ADC resolution for the ESP32. 12‑bit yields values in 0..4095.
    analogReadResolution(LDR_RESOLUTION);
    pinMode(_pin, INPUT);
}

int LightSensor::readRaw() {
    int value = analogRead(_pin);
    // Constrain the reading to valid bounds
    if (value < LIGHT_MIN_VALID) value = LIGHT_MIN_VALID;
    if (value > LIGHT_MAX_VALID) value = LIGHT_MAX_VALID;
    return value;
}

int LightSensor::readNormalized() {
    // At present, normalisation simply returns the raw reading. In a future
    // revision this function could map the reading to a percentage or lux.
    return readRaw();
}