/**
 * @file DataFilter.h
 * @brief Implements a simple moving average filter for float values.
 */

#ifndef DATA_FILTER_H
#define DATA_FILTER_H

#include <Arduino.h>
#include "config.h"

/**
 * @class DataFilter
 * @brief Maintains a circular buffer and computes a moving average.
 */
class DataFilter {
public:
    /**
     * Construct a new DataFilter object.
     *
     * @param windowSize Number of samples to average over.
     */
    explicit DataFilter(size_t windowSize = FILTER_WINDOW_SIZE);

    /**
     * Destructor to free allocated buffer.
     */
    ~DataFilter();

    /**
     * Add a new value to the filter. The oldest value will be dropped
     * once the buffer is full.
     *
     * @param value The new value to insert.
     */
    void addValue(float value);

    /**
     * Compute the current average of the values stored in the buffer.
     *
     * @return The average or 0 if no samples have been added.
     */
    float getAverage() const;

    /**
     * Reset the filter, discarding all stored samples.
     */
    void reset();

private:
    size_t _windowSize; ///< Maximum number of samples to average
    float *_buffer;     ///< Pointer to dynamic array storing samples
    size_t _index;      ///< Current insertion index
    size_t _count;      ///< Number of samples currently stored
};

#endif // DATA_FILTER_H