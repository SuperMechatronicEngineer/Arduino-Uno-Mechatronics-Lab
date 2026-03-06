# Project 01: LED Control: Linear Scaling vs Base-2 Exponential LED Control

## Project Info
- **Project Name:** LED Control: Linear Scaling vs Base-2 Exponential
- **Revision:** 1.1 (Improved Version)
- **Date:** 2026-02-11
- **Author:** SuperMechatronicEngineer

## Project Description
This project explores the relationship between mathematical modeling and human visual perception. It features a comparative study of the visual effect produced by **two red LEDs** driven by different PWM (Pulse Width Modulation) control strategies. The goal is to demonstrate how software-level mathematical compensation can align digital outputs with the non-linear nature of human ocular sensitivity (**Weber-Fechner Law**).

## 📺 Video Documentation
The complete build and demonstration are available on Odysee:
- **Watch here:** [Arduino UNO R4 WiFi - LED Control: Linear Scaling vs Base-2 Exponential](https://odysee.com/@SuperMechatronicEngineer:8/Arduino-UNO-R4-PWM-LED-Lin-vs-Exp:9)

## Technical Details
* **Target Hardware:** Arduino UNO R4 WiFi
* **Active Components:** 
    * **2x Red LED**.
    * **2x 1kΩ Resistor**: Selected to ensure low current draw and long-term stability for the microcontroller.
* **Baud Rate:** 115200 bps.
* **Connections:** Digital Pin 10 (Linear LED), Digital Pin 11 (Exponential LED), and GND.

## Software Logic & Architecture
The code implements two distinct mathematical models to drive the LEDs:
* **Linear Scaling (Pin 10):** Implements $y = (255/1023) \cdot x$. This results in a constant increase in the duty cycle, which typically appears to reach maximum brightness prematurely due to human eye physiology.
* **Exponential Mapping (Pin 11):** Implements the base-2 formula $y = 2^{(x/127.875)} - 1$. This curve spreads the lower intensity values across a wider range, resulting in a perceptually "linear" and smooth fade.
* **Ultra-Smooth Resolution:** By using 1024 discrete input steps and a unitary increment (`fadeAmount = 1`), the transition is exceptionally fluid, effectively eliminating visible "stepping."
* **Real-Time Telemetry:** The project provides real-time data on how the models diverge. Telemetry is sampled and displayed every 10 steps to ensure the serial overhead does not impact the PWM timing.

## License & Credits
- **License:** This project is licensed under [CC BY-NC-SA 4.0](../../LICENSE) (Attribution-NonCommercial-ShareAlike).