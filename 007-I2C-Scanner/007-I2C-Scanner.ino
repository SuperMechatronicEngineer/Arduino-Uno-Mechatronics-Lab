/*
 * Project: I2C Bus Scanner for Arduino UNO R4
 * Date: 2026-04-15
 * Revision: 1.0 - Stable Version
 * * DESCRIPTION:
 * This program is engineered to execute a perpetual, automated scan of the 
 * I2C (Inter-Integrated Circuit) bus. The system systematically probes all 
 * valid 7-bit addresses (from 0x01 to 0x7E) to detect connected peripherals. 
 * It distinguishes between successful acknowledgments (ACK), missing devices 
 * (NACK), and critical hardware-level bus errors. This tool is ideal for 
 * debugging hardware wiring, verifying device addresses, and ensuring 
 * electrical integrity of the SDA/SCL lines.
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <Wire.h>

void setup() {
    Serial.begin(115200);
    while (!Serial) {
    }

    Serial.println("I2C Scanner for Arduino UNO R4");
    Serial.println("Initializing I2C bus...");
    Wire.begin();   // Start I2C hardware in master mode
}

void loop() {
    byte error;
    byte address;
    int nDevices = 0;

    Serial.println();
    Serial.println("Scanning all I2C addresses...");

    // Valid 7-bit I2C addresses range from 0x01 to 0x7E.
    // Address 0x00 and 0x7F are reserved.
    for (address = 1; address < 127; address++) {

        // Begin a transmission to the current address.
        // This sends the address + write bit on the bus.
        Wire.beginTransmission(address);

        // endTransmission() sends the address and waits for ACK/NACK.
        // Return codes:
        //   0 → ACK received (device exists)
        //   2 → NACK on address (normal: no device here)
        //   3 → NACK on data (cannot occur here, we send no data)
        //   4 → bus error (wiring, power, or pull-up issue)
        error = Wire.endTransmission();

        if (error == 0) {
            // A device acknowledged this address.
            Serial.print("I2C device found at address 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address, HEX);
            nDevices++;
        }
        else if (error == 4) {
            // Error 4 indicates a real electrical problem on the bus.
            Serial.print("Bus error at address 0x");
            if (address < 16) Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  (ERROR 4: check wiring, power, pull-ups)");
        }

        // Note:
        // error 2 (NACK) is normal and simply means:
        // "no device responds at this address".
        // We do not print anything for it to keep output clean.
    }

    // ------------------------------------------------------------
    // Explicit handling of the "no devices found" case
    // ------------------------------------------------------------
    if (nDevices == 0) {
        Serial.println("No I2C devices detected on the bus.");
        Serial.println("If you expected a device (e.g., SSD1306),");
        Serial.println("check wiring, power, SDA/SCL connections, and pull-ups.");
    } else {
        Serial.print("Scan complete. Devices found: ");
        Serial.println(nDevices);
    }

    delay(2000);  // Avoid flooding the serial monitor
}