/**
 * @file AlertManager.cpp
 * @brief Implementation of the AlertManager class.
 */

#include "config.h"
#include "secret.h"
#include "utils/AlertManager.h"

AlertManager::AlertManager(uint8_t ledPin)
    : _ledPin(ledPin), _state(ALERT_OK) {}

void AlertManager::begin() {
    pinMode(_ledPin, OUTPUT);
    digitalWrite(_ledPin, LOW);
}

AlertState AlertManager::update(float temperature, float humidity, int light) {
    // Determine the state based on threshold comparisons. Order of
    // evaluation matters; more severe conditions take precedence.
    if (!isnan(temperature) && temperature >= TEMP_HIGH_THRESHOLD) {
        _state = ALERT_TEMP_HIGH;
    } else if (!isnan(temperature) && temperature <= TEMP_LOW_THRESHOLD) {
        _state = ALERT_TEMP_LOW;
    } else if (!isnan(humidity) && humidity >= HUMID_HIGH_THRESHOLD) {
        _state = ALERT_HUMID_HIGH;
    } else if (!isnan(humidity) && humidity <= HUMID_LOW_THRESHOLD) {
        _state = ALERT_HUMID_LOW;
    } else if (light <= LIGHT_LOW_THRESHOLD) {
        _state = ALERT_LIGHT_LOW;
    } else {
        _state = ALERT_OK;
    }
    // Drive LED: on when an alert is present, off otherwise
    setLED(_state != ALERT_OK);
    return _state;
}

AlertState AlertManager::getState() const {
    return _state;
}

void AlertManager::setLED(bool on) {
    digitalWrite(_ledPin, on ? HIGH : LOW);
}