# SkyMetrics--Smart-Weather-monitoring-system-
This project is an ESP32-based IoT weather monitoring system that reads temperature, humidity, and atmospheric pressure, displays the data on a 16x2 I2C LCD, and connects to the Blynk mobile platform for remote monitoring and control. The system also drives an LED using a combination of automatic temperature-based control and manual Blynk control.

The system also implements hybrid automation, where an LED is controlled automatically based on temperature thresholds and manually via the Blynk mobile application.

---

## Features

* Real-time temperature and humidity monitoring using DHT22
* Atmospheric pressure measurement using BMP280
* LCD display with dynamic screen switching
* Remote LED control using Blynk (Virtual Pin V0)
* Automatic LED activation when temperature exceeds threshold
* Non-blocking execution using millis()

---

## Hardware Requirements

* ESP32 Development Board
* DHT22 Temperature and Humidity Sensor
* BMP280 Pressure Sensor
* 16x2 I2C LCD Display
* LED
* Resistor (220Ω recommended)
* Push Button / Switch (for GPIO 13 input)
* Breadboard and Jumper Wires

---

## Software Requirements

* Arduino IDE
* ESP32 Board Package
* Required Libraries:

  * WiFi.h
  * BlynkSimpleEsp32.h
  * Wire.h
  * LiquidCrystal_I2C.h
  * Adafruit_BMP280.h
  * DHT.h

---

## Circuit Connections

| Component   | ESP32 Pin        | Description   |
| ----------- | ---------------- | ------------- |
| DHT22 VCC   | 3.3V             | Power         |
| DHT22 GND   | GND              | Ground        |
| DHT22 DATA  | GPIO 4           | Data pin      |
| BMP280 SDA  | GPIO 21          | I2C Data      |
| BMP280 SCL  | GPIO 22          | I2C Clock     |
| LCD SDA     | GPIO 21          | I2C Data      |
| LCD SCL     | GPIO 22          | I2C Clock     |
| LED Anode   | GPIO 5           | Output        |
| LED Cathode | GND via resistor | Ground        |
| Switch      | GPIO 13          | Weather input |

---

## Installation and Setup

### 1. Install Arduino IDE

Download and install Arduino IDE from the official website.

### 2. Install ESP32 Board

* Go to File > Preferences
* Add the following URL to "Additional Board Manager URLs":
  https://dl.espressif.com/dl/package_esp32_index.json
* Go to Tools > Board > Boards Manager
* Search for ESP32 and install

### 3. Install Required Libraries

Install the following libraries using Library Manager:

* Blynk
* Adafruit BMP280
* DHT sensor library
* LiquidCrystal I2C

---

## Blynk Setup

1. Install the Blynk mobile app
2. Create a new template/project
3. Copy the following credentials into your code:

   * BLYNK_TEMPLATE_ID
   * BLYNK_TEMPLATE_NAME
   * BLYNK_AUTH_TOKEN
4. Add a button widget:

   * Set it to Virtual Pin V0
   * Mode: Switch

---

## How to Run the Project

1. Open the Arduino IDE
2. Copy and paste the project code into a new sketch
3. Update WiFi credentials:

   ```cpp
   const char* ssid = "YOUR_WIFI_NAME";
   const char* pwd  = "YOUR_WIFI_PASSWORD";
   ```
4. Update Blynk credentials:

   ```cpp
   #define BLYNK_AUTH_TOKEN "YOUR_TOKEN"
   ```
5. Select the correct board:

   * Tools > Board > ESP32 Dev Module
6. Select the correct port:

   * Tools > Port
7. Upload the code to ESP32
8. Open Serial Monitor (115200 baud)

---

## System Behavior

* Sensor data is read every 2 seconds
* LCD alternates between:

  * Temperature and humidity
  * Pressure
* LED behavior:

  * Turns ON automatically if temperature > 35°C
  * Otherwise controlled via Blynk
* GPIO 13 determines weather display:

  * LOW: Sunny
  * HIGH: Cloudy

---

## Future Improvements

* Add cloud data logging
* Implement alerts and notifications
* Integrate additional sensors (rain, air quality)
* Add data visualization dashboards

---

## License

This project is for educational purposes and can be modified and reused freely.
