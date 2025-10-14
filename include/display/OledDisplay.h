/**
 * @file OledDisplay.h
 * @brief High level wrapper around the Adafruit SSD1306 OLED display.
 *
 * This class handles initialization of the display, rendering of sensor
 * readings and status messages. It relies on the global configuration
 * constants defined in config.h.
 */

#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

/**
 * @class OledDisplay
 * @brief Abstraction for a 0.96" I2C OLED display using the SSD1306 driver.
 */
class OledDisplay {
public:
    /**
     * Construct a new OledDisplay. The display is instantiated with
     * dimensions and I2C parameters defined in config.h.
     */
    OledDisplay();

    /**
     * Initialize the display hardware. Must be called in setup().
     *
     * @return true if initialization succeeded, false otherwise.
     */
    bool begin();

    /**
     * Render the latest sensor readings on the display. Values are
     * formatted nicely and updated whenever this method is called.
     *
     * @param temperature Filtered temperature reading in °C
     * @param humidity    Filtered humidity reading in %
     * @param light       Filtered light reading (0‑4095)
     */
    void showReadings(float temperature, float humidity, int light);

    /**
     * Show a status message on the display. This will clear the screen
     * before rendering the message.
     *
     * @param status A textual status to display
     */
    void showStatus(const String &status);

private:
    Adafruit_SSD1306 _display; ///< Display driver object
    void clear();              ///< Clear the display buffer and send to screen
};

#endif // OLED_DISPLAY_H