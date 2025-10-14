/**
 * @file DataFilter.cpp
 * @brief Implementation of the DataFilter class.
 */

#include "utils/DataFilter.h"

#include <stdlib.h>

DataFilter::DataFilter(size_t windowSize)
    : _windowSize(windowSize), _index(0), _count(0) {
    // Allocate buffer and initialize to zero
    _buffer = new float[_windowSize];
    for (size_t i = 0; i < _windowSize; ++i) {
        _buffer[i] = 0.0f;
    }
}

DataFilter::~DataFilter() {
    delete[] _buffer;
}

void DataFilter::addValue(float value) {
    _buffer[_index] = value;
    _index = (_index + 1) % _windowSize;
    if (_count < _windowSize) {
        ++_count;
    }
}

float DataFilter::getAverage() const {
    if (_count == 0) {
        return 0.0f;
    }
    float sum = 0.0f;
    for (size_t i = 0; i < _count; ++i) {
        sum += _buffer[i];
    }
    return sum / static_cast<float>(_count);
}

void DataFilter::reset() {
    _index = 0;
    _count = 0;
    for (size_t i = 0; i < _windowSize; ++i) {
        _buffer[i] = 0.0f;
    }
}