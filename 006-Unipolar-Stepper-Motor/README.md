# Project 06: Drive a 28BYJ-48 Stepper Motor with ULN2003a breakout board

## Project Info
- **Project Name:** Drive a 28BYJ-48 Stepper Motor with ULN2003a breakout board
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-03-31
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a basic driver for the 28BYJ-48 unipolar stepper motor using an Arduino Uno R4 WiFi. The goal is to move the motor in both directions (CW and CCW) with a fixed pause between transitions, avoiding the use of `delay()`.

The firmware uses a simple **C++ Class** to handle the stepping logic and a **State Machine** in the main loop to manage the rotation cycles. This structure ensures that the microcontroller remains responsive during the timed pauses and the stepping process.

## 📺 Video Documentation
Comprehensive project documentation is available in two parts on Odysee:

* **Hardware Teardown:** [Inside the 28BYJ-48 Stepper Motor: The 4,096 Step Secret Revealed](https://odysee.com/@SuperMechatronicEngineer:8/006-unipolar-stepper-motor:7)  
  *Detailed look at the 32-pole rotor and the gear train (9:32, 11:22, 9:27, 8:24) to explain the 64:1 reduction.*
* **Project Build & Demo:** [Arduino UNO R4 WiFi - Drive a 28BYJ-48 Stepper Motor with ULN2003a breakout board](https://odysee.com/@SuperMechatronicEngineer:8/006b-unipolar-stepper:6)  
  *Wiring and real-time functional test.*

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi (Renesas RA4M1).
* **Motor Driver:** ULN2003a Darlington transistor array breakout board.
* **Main Actuator:** 28BYJ-48 Unipolar Stepper Motor (5V).
* **Power Architecture:** 
    * **External 5V DC Supply:** Dedicated source for the motor to handle the ~250mA draw and prevent noise.
    * **Common GND:** The external power supply ground is tied to the Arduino GND.
* **Motor & Gearbox Specs:** 
    * **Internal Rotor:** 32-pole magnetic rotor construction.
    * **Integrated Gearbox:** 64:1 reduction ratio (verified internal stages: 9:32, 11:22, 9:27, 8:24).
* **System Resolution:** 4,096 steps per full 360° output shaft rotation when driven in **Half-Step mode**.

## Software Logic & Architecture
### 1. `StepperDriver` Class
A C++ class that encapsulates the motor pins and the 8-step lookup table. It manages timing via `millis()` with a default 2ms interval between steps to ensure non-blocking execution.

### 2. State Machine Logic
The `loop()` function transitions through four basic states: `ROTATING_CW`, `PAUSE_CW`, `ROTATING_CCW`, and `PAUSE_CCW`. This allows the code to track the step count and timing without halting the CPU.

### 3. Coil Management
The `release()` method sets all driver pins to **LOW** during pauses. This stops current flow through the motor coils when stationary, reducing heat buildup in both the ULN2003a driver and the 28BYJ-48 motor.

## Wiring Diagram
| Arduino UNO R4 Pin | Cable Color | ULN2003a Pin |
| :--- | :--- | :--- |
| **D8** | **Yellow** | IN1 |
| **D9** | **Red** | IN2 |
| **D10** | **Green** | IN3 |
| **D11** | **Black** | IN4 |
| **GND** | **Black** | GND (Common) |
| **External 5V** | — | VCC (ULN2003) |

## License & Credits
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).