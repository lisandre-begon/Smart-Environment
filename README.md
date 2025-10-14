# Smart Environment Node

This project implements a connected environmental monitoring node using an
ESP32 development board. The node reads temperature and humidity from a
DHT11 sensor, light intensity from an LDR, displays the values on an
SSD1306 OLED screen, triggers an alert LED when thresholds are exceeded
and uploads the measurements to a cloud service via WiFi (HTTP or MQTT).

## Features

- Modular architecture with distinct classes for sensors, display,
  connectivity, filtering and alerting.
- Configurable pin assignments and thresholds via `include/config.h`.
- Moving average filtering to smooth out sensor readings.
- Automatic WiFi reconnection and cloud upload retries.
- Support for ThingSpeak (HTTP) or generic MQTT brokers.

## Directory Layout

```
include/            Public header files
├── config.h        Global definitions and settings
├── sensors/        Sensor interfaces
│   ├── DHTSensor.h
│   └── LightSensor.h
├── display/        OLED display wrapper
│   └── OledDisplay.h
├── connectivity/   Network and cloud interfaces
│   ├── WiFiManager.h
│   └── CloudUploader.h
└── utils/          Utility classes
    ├── DataFilter.h
    └── AlertManager.h

src/                Implementation files
├── main.cpp        Application entry point
├── sensors/
│   ├── DHTSensor.cpp
│   └── LightSensor.cpp
├── display/
│   └── OledDisplay.cpp
├── connectivity/
│   ├── WiFiManager.cpp
│   └── CloudUploader.cpp
└── utils/
    ├── DataFilter.cpp
    └── AlertManager.cpp

platformio.ini      PlatformIO build configuration
README.md           This file
```

## Getting Started

1. **Install PlatformIO** in VS Code.
2. Clone this repository to your machine.
3. Create a `secrets.h` inside `include/` (and add it to `.gitignore`) or
   override credentials in `platformio.ini` via `build_flags`.
4. Connect the hardware according to the wiring diagram described in
   `docs/wiring-diagram.md` (not included here but referenced in the
   `iot_project_structure.txt` file).
5. Build and upload the firmware to your ESP32 using PlatformIO.

## Customisation

Adjust threshold values, timing intervals and pin assignments in
`include/config.h` to suit your specific hardware setup. Use the
`FILTER_WINDOW_SIZE` constant to modify how aggressively the moving
average smooths the readings. To switch between ThingSpeak and MQTT
uploads simply leave the `THINGSPEAK_API_KEY` as the default placeholder
or set it to your actual ThingSpeak key.
