# Project 04: Interrupt-Based Preemption over Blocking Tasks

## Project Info
- **Project Name:** Interrupt-Based Preemption over Blocking Tasks
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-03-24
- **Author:** SuperMechatronicEngineer

## Project Description
This project demonstrates the fundamental difference between **Sequential Execution** and **Hardware Preemption** on the Arduino UNO R4. 

The firmware manages two distinct visual outputs with conflicting timing logic:
1.  **Status LED (Yellow):** Executes a continuous blink cycle with a 2-second interval. It uses a blocking `delay()`, which typically freezes the CPU.
2.  **User LED (Red):** Toggles its state (ON/OFF) instantly upon a button press. 

**The Core Concept:** By leveraging a Hardware Interrupt (ISR), the Red LED "preempts" the 2000ms delay of the Yellow LED. This proves that critical user inputs can be processed with microsecond latency even when the main software loop is technically "frozen" in a blocking task.

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi (Renesas RA4M1)
* **Variable Integrity:** Uses the `volatile` qualifier for shared variables to prevent compiler optimization errors during asynchronous state changes.
* **Debounce Logic:** Implements a **200ms Software Filter** within the ISR to eliminate mechanical contact bounce without using prohibited blocking functions.
* **Components:** 
    * 1x Red LED (**Pin 3**) - Toggled via Interrupt.
    * 1x Yellow LED (**Pin 4**) - Controlled by blocking loop.
    * 2x 1kΩ Resistors (Current limiting for LED protection)
    * 1x Push-button (**Pin 8**): Triggering Hardware Interrupt via **Internal Pull-up** (Active-LOW).
## Software Logic & Architecture
### 1. The Blocking Main Loop (Status LED)
The `loop()` function deliberately uses a `delay(BLOCKING_TIME)` to simulate a system under heavy load or a long-running computation. In a standard sequential program, the system would be "blind" to any input during these 2 seconds.

### 2. Preemptive Hardware Interrupt (User LED)
The **User LED** is managed by an **Interrupt Service Routine (ISR)**. When the button on Pin 8 is pressed:
1. The hardware detects a `FALLING` edge (transition from 5V to 0V).
2. The CPU immediately suspends the `delay()` in the loop.
3. The `handleButtonToggle()` function is executed with microsecond latency.
4. The CPU resumes the `delay()` exactly where it left off.

### 3. Active-LOW Configuration
By enabling `INPUT_PULLUP` on Pin 8, the pin is held at a stable HIGH state (5V) by default. Pressing the button pulls the signal to GND (0V). This "Active-LOW" setup increases noise immunity and simplifies wiring by removing the need for external resistors.

## License & Credits
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).