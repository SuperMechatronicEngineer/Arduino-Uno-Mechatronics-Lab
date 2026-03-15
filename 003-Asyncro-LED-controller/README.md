# Project 03: Dual-Rate Asynchronous LED Controller

## Project Info
- **Project Name:** Dual-Rate Asynchronous LED Controller
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-03-15
- **Author:** SuperMechatronicEngineer

## Project Description
This project implements a **multitasking asynchronous architecture** on the Arduino UNO R4. Unlike standard scripts that use the restrictive `delay()` function, this firmware manages two independent LED duty cycles simultaneously. By leveraging the internal hardware timer via `millis()`, the system achieves a "Zero-Latency" execution, allowing the CPU to remain fully responsive to other tasks while managing precise timing for the outputs.

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi (Renesas RA4M1)
* **Variable Precision:** `uint32_t` (Unsigned 32-bit integers) to ensure overflow safety during long-term operation (up to 49.7 days).
* **Components:** 
    * 1x Red LED (**Pin 2**)
    * 1x Yellow LED (**Pin 3**)
    * 2x 1kΩ Resistors (Current limiting for LED protection)

## Software Logic & Architecture
* **Non-Blocking Multitasking:** The core loop never "sleeps." It continuously polls the system clock and executes "toggle" events only when the delta-time condition is met. This mimics a real-time operating system (RTOS) behavior on a single-thread micro.
* **Asynchronous Threads:** 
    * **Thread A (Fast):** 500ms Interval (1Hz frequency).
    * **Thread B (Slow):** 2000ms Interval (0.25Hz frequency).
* **State Persistence:** LED states are stored in `bool` variables (1 byte each), providing high readability and minimal RAM footprint compared to standard integer flags.
* **Deterministic Execution:** By capturing `currentMillis` at the start of the `loop()`, the program ensures that all conditional checks within a single cycle are synchronized to the exact same timestamp.

## License & Credits
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).