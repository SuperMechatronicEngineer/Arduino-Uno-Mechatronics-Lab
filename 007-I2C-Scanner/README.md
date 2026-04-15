# Project 07: I2C Bus Scanner for Arduino UNO R4

## Project Info
- **Project Name:** I2C Bus Scanner for Arduino UNO R4
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-04-15
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a high-reliability diagnostic tool designed to scan and map the I2C bus on an Arduino UNO R4. While compatible with any I2C peripheral, this version is specifically tailored to troubleshoot and verify the connection of **OLED SSD1306 displays**.

Identifying the correct I2C address is a mandatory first step before initializing graphics libraries (like Adafruit_SSD1306 or U8g2), as these modules often vary between **0x3C** and **0x3D** depending on the manufacturer's jumper settings.

## Technical Details
* **Target Hardware:** Arduino UNO R4 (Minima or WiFi).
* **Reference Device:** **OLED SSD1306 Display** (128x64 / 128x32).
* **Communication Protocol:** I2C.
* **Standard Addresses:** Probes the entire 7-bit range, specifically looking for the SSD1306 default **0x3C/0x3D** signatures.
* **Bus Diagnostics:** 
    * **ACK Detection:** Confirms the OLED is powered and listening.
    * **Error Code 4:** Critical for SSD1306 setup to identify missing pull-up resistors or SCL/SDA swaps.
 
## Software Logic & Architecture
### 1. Serial Synchronization
Ensures the Arduino UNO R4 wait for the Serial Monitor to be ready before announcing the detected address of the **SSD1306**, avoiding lost "ACK" messages during boot.

### 2. Scanning Algorithm
The code pings each address. For the **SSD1306**, this confirms that the display's internal controller is responding to the master's "START" condition, providing the exact Hex value needed for the software constructor.

### 3. Error Analysis for Displays
The program is designed to help the user distinguish if an OLED is simply not responding (Address NACK) or if there is a fundamental bus failure (Error 4), which is common when using long jumper wires or incorrect voltage levels for the display.

## Wiring Diagram
| Arduino UNO R4 Pin | I2C Function | SSD1306 OLED Pin |
| :--- | :--- | :--- |
| **SCL** | **Clock Line (SCL)** | **SCL** |
| **SDA** | **Data Line (SDA)** | **SDA** |
| **5V** | **VCC** | **VCC** |
| **GND** | **Ground** | **GND** |

## License & Credits
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).