# Project 02: Dynamic Name Acquisition System

## Project Info
- **Project Name:** Dynamic Name Acquisition System
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-03-06
- **Author:** SuperMechatronicEngineer

## Project Description
This program resolves the "static array limitation" by allowing the user to specify the number of entries **at runtime**. Unlike standard Arduino sketches where array sizes must be predefined before compilation (e.g., `String names[10];`), this system adapts its memory consumption based on the user's live requirements, making the firmware flexible and resource-efficient.

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi (Renesas RA4M1)
* **Memory Management:** Dynamic Heap Allocation (`new[]` / `delete[]`)
* **Library Dependencies:** `<new>` (for `std::nothrow` support)
* **Communication:** Serial UART @ 115200 baud

## Software Logic & Architecture
* **Runtime Elasticity (Heap Allocation):** The program does not pre-allocate space for data. Instead, it uses the `new` operator to "carve out" a contiguous block in the Heap of the exact size requested by the user during execution.
* **Safety & Robustness (`std::nothrow`):** To prevent hardware crashes during memory exhaustion (Out-of-Memory conditions), the firmware utilizes `new (std::nothrow)`. If the allocation fails, the system detects a `nullptr` and handles the error gracefully with a system message instead of resetting.
* **UART Sanitization (`clearBuffer`):** To prevent the common "input skipping" bug, the firmware flushes invisible control characters (such as `\n` or `\r`) from the hardware UART buffer after numeric input is received.
* **Memory Hygiene:** The system strictly follows the "Allocate-Use-Deallocate" pattern. The use of `delete[]` at the end of every cycle ensures that memory is returned to the system, preventing fragmentation and allowing the device to run indefinitely.

## License & Credits
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).