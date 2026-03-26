# Project 05: Dual-Interrupt System (Counting & Reset)

## Project Info
- **Project Name:** Dual-Interrupt System (Counting & Reset)
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-03-26
- **Author:** SuperMechatronicEngineer

## Project Description
This project explores the relationship between **Sequential Execution** and **Hardware-Level Preemption** on the Arduino Uno R4. It demonstrates a method for decoupling low-priority background execution from high-priority asynchronous events via a Dual-ISR (Interrupt Service Routine) architecture.

The firmware manages a real-time system state where user interactions (counting and resetting) are processed with microsecond latency, bypassing the standard linear flow of the `loop()` to ensure zero-latency UI responsiveness.

**The Core Concept:** By utilizing multiple Hardware Interrupts, the system can "preempt" any ongoing CPU task to handle critical inputs. This ensures that a button press is never "missed," providing a professional-grade alternative to standard software polling.

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - Implementing a Dual-Interrupt System for Real-Time Counting & Reset](https://odysee.com/@SuperMechatronicEngineer:8/005-Interrupt-2:9)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi (Renesas RA4M1)
* **Variable Integrity:** Uses the `volatile` qualifier for shared variables to prevent compiler optimization errors during asynchronous state changes.
* **Debounce Logic:** Implements a **200ms Software Filter** within the ISR to eliminate mechanical contact bounce without using prohibited blocking functions.
* **Components:** 
    * 1x Red Push-button (**Pin 8**) - **Count & Toggle**: Increments a 16-bit counter and flips LED state.
    * 1x Green Push-button (**Pin 3**) - **System Reset**: Instantly zeroes the counter and forces the LED to OFF.
    * 1x Yellow LED (**Pin 4**) - Status output toggled via Interrupt.
    * 1x 1kΩ Resistors (Current limiting for LED protection)

## Software Logic & Architecture
### 1. Hardware-Level Preemption
The system utilizes the `attachInterrupt()` function to monitor Pins 8 and 3. When a `FALLING` edge is detected (button press), the CPU immediately suspends its current task in the `loop()` to execute the corresponding ISR. Once the ISR completes, the CPU resumes exactly where it left off.

### 2. Dual-ISR Functionality
* **`handleButtonToggle()` (Pin 8):** * Implements a **200ms Software Debounce** filter using a time-delta check ($currentTime - lastTime$).
    * Increments a `uint16_t` counter (safe up to 65,535 presses).
    * Toggles the `ledState` and updates the physical output on Pin 4.
* **`handleReset()` (Pin 3):** * An "Emergency" high-priority trigger.
    * Resets `pressCounter` to 0 and `ledState` to `false`.
    * Immediately forces **Pin 4 LOW**, ensuring the system returns to a safe state instantly.

### 3. Asynchronous Telemetry
The `loop()` function remains "non-blocking." It constantly compares the `pressCounter` (updated by ISRs) with `lastReportedCount`. Serial data is only transmitted when a change is detected, significantly reducing CPU overhead and keeping the Serial Monitor clean.

### 4. Active-LOW Configuration
Both buttons utilize the internal `INPUT_PULLUP` resistors. The pins are held at 5V (HIGH) and triggered by a transition to GND (0V). This setup simplifies the circuit and provides high immunity to electromagnetic noise.

## License & Credits
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).