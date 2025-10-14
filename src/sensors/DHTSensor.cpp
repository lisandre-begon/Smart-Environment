/**
 * @file DHTSensor.cpp
 * @brief Implementation of the DHTSensor class.
 */

#include "config.h"
#include "secret.h"
#include "sensors/DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {
    // Constructor body is empty; member initialiser list sets up the DHT object
}

void DHTSensor::begin() {
    dht.begin();
}

float DHTSensor::readTemperature() {
    float t = dht.readTemperature();
    // Adafruit DHT returns NAN on error
    return t;
}

float DHTSensor::readHumidity() {
    float h = dht.readHumidity();
    return h;
}

bool DHTSensor::isValid(float value, float minValid, float maxValid) {
    return (!isnan(value) && value >= minValid && value <= maxValid);
}