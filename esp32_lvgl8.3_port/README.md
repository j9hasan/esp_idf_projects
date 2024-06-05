# LVGL v8.6 Port for ESP32 using ESP-IDF

This project demonstrates how to port and use LVGL v9 on an ESP32 with an ILI9341 display and XPT2046 touch driver.

## Prerequisites

### Hardware
- ESP32 WROOM without PSRAM 
- ILI9341 display
- XPT2046 touch driver
- SD card (optional)
- Proper wiring for HSPI and VSPI ports

### Software
- ESP-IDF (version compatible with your ESP32)

## Installation

### 1. Open Project in ESP-IDF

Clone the repository and navigate to the project directory:

```sh
git clone https://github.com/j9hasan/lvgl_v9_port_esp32.git
cd lvgl_v9_port_esp32
```

### 2. Configure Project

Open `menuconfig` to configure the project settings:

```sh
idf.py menuconfig
```

In `menuconfig`, set up the following:
- **Component Config** -> **Display configuration**: Configure display Pins set HSPI port.
- **Component Config** -> **Touch Driver configuration**: Configure touch pin shared with Display and set HSPI port.

### 3. Configure SD card
- Configure the SD card pins by going to sd_fat components sd_fat.h file
   
### 4. Build and Flash

Build the project and flash it to your ESP32:

```sh
idf.py build
idf.py flash
idf.py monitor
```

## Usage

After flashing, the project should start automatically. You can monitor the output via the serial monitor.

For additional information or troubleshooting, feel free to reach out via email.

## Contact

For more information, email: [jubaid.eee07@gmail.com](mailto:jubaid.eee07@gmail.com)

---
