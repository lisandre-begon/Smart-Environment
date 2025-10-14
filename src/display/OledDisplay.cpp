/**
 * @file OledDisplay.cpp
 * @brief Implementation of the OledDisplay class.
 */

#include "config.h"
#include "secret.h"
#include "display/OledDisplay.h"

OledDisplay::OledDisplay() : _display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1) {}

bool OledDisplay::begin() {
    // Initialize I2C pins (Wire will use default SDA/SCL defined by pins).
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!_display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        // Failed to initialize display
        return false;
    }
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.display();
    return true;
}

void OledDisplay::clear() {
    _display.clearDisplay();
    _display.display();
}

void OledDisplay::showReadings(float temperature, float humidity, int light) {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.print(F("Temp: "));
    if (isnan(temperature)) {
        _display.println(F("--"));
    } else {
        _display.print(temperature, 1);
        _display.println(F(" C"));
    }
    _display.print(F("Hum: "));
    if (isnan(humidity)) {
        _display.println(F("--"));
    } else {
        _display.print(humidity, 1);
        _display.println(F(" %"));
    }
    _display.print(F("Light: "));
    _display.println(light);
    _display.display();
}

void OledDisplay::showStatus(const String &status) {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println(status);
    _display.display();
}