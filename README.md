# ESP32 Weather Display

This project reads **temperature and humidity** from a DHT11 sensor and displays it on a **128x64 OLED** screen.  
The ESP32 shows the data for **5 seconds**, then enters **deep sleep for 20 seconds** to save power.  

---

## Features

- Reads **temperature (°C)** and **humidity (%)** from DHT11  
- Displays data on **SSD1306 OLED**  
- **Timer-based active display**  
- **Deep sleep** to save power  
- Fully **ESP32 compatible**

---

## Hardware

- ESP32 Dev Module  
- DHT11 sensor  
- 128x64 OLED (I2C)  
- Jumper wires / breadboard

---

## Software / Libraries

- Arduino IDE  
- Adafruit SSD1306  
- Adafruit GFX  
- DHT sensor library

---

## Code Highlights

- Active display time: **5 seconds**  
- Sleep time: **20 seconds**  
- Uses **ESP32 hardware timer** and **deep sleep APIs**

---

## Usage

1. Open `ESP32_Weather_Display.ino` in Arduino IDE  
2. Select **ESP32 Dev Module** board  
3. Install required libraries  
4. Upload to ESP32  
5. Observe OLED display and power-efficient sleep cycles

---

## License

MIT License (optional)
