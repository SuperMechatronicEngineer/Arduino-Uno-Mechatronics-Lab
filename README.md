# 🤖 Arduino-Uno-Mechatronics-Lab
A personal collection of technical experiments and implementation studies using the **Arduino UNO R4 WiFi**.

## 🎯 Project Philosophy
This repository is my personal "Knowledge Base." It tracks my progress in mastering **Embedded C++** and **Electronic Systems** through the unique features of the Renesas RA4M1 MCU. I use these projects to:
- **Level up my C++**: Moving from simple logic to robust firmware.
- **Explore Hardware Limits**: Understanding how the Arduino R4 handles data, signals, and memory in real-world scenarios.
- **Build a Reference Library**: Every project here is a "verified brick" — a tested solution that I can revisit and reuse in more complex future designs.

---

## 🛠️ Hardware Stack
- **Board:** Arduino UNO R4 WiFi (Renesas RA4M1)
- **Primary Editor:** VS Code / Arduino IDE 2.x
- **Components:** A diverse range of hardware including discrete components (LEDs, resistors), actuators (motors, drivers), and sensors, integrated according to specific lesson requirements.

---

## 🚀 Project Registry
These experiments represent specific technical milestones in my learning path.

| ID | Project Name | Technical Focus | Status |
| :---: | :--- | :--- | :---: |
| 001 | [📁 Linear vs Exp LED](./001-Lin-vs-Exp-LED-Control/) | Mastering PWM duty cycles and Human Eye perception (Logarithmic mapping). | ✅ |
| 002 | [📁 Dynamic Name System](./002-String-Array/) | Handling unknown data quantities at runtime and protecting the Serial buffer. | ✅ |
| 003 | [📁 Asynchronous LED Controller](./003-Asyncro-LED-controller/) | Implementing a non-blocking multitasking architecture for independent LED control. | ✅ |
| 004 | [📁 Hardware Interrupt](./004-HW-Interrupt/) | Hardware-Level Event Management: overriding Blocking Delays with Arduino Uno R4 Interrupts. | ✅ |
| 005 | [📁 Dual Hardware Interrupt](./005-HW-Interrupt-2/) | Hardware-Level Event Management: decoupling high-priority asynchronous triggers from the main execution flow via Dual-ISR architecture. | ✅ |
| 006 | [📁 28BYJ-48 Stepper Motor](./006-Unipolar-Stepper-Motor/) | Asynchronous Motion Control: decoupling deterministic motor stepping from sequential program flow via Object-Oriented State Machine architecture. | ✅ |
| ... | ... | ... | ... |

### 🔑 Legend
* ✅ **Completed**: Project is finished and code is optimized.
* 🟡 **In Progress**: Code is being written or currently in testing.

---

## ⚖️ License
This repository is licensed under the **Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)**. 
See the [LICENSE](./LICENSE) file for the full text.