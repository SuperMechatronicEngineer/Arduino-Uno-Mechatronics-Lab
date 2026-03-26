/* * PROJECT: Dual-Interrupt System (Counting & Reset)
 * DATE: 2026-03-26
 * AUTHOR: SuperMechatronicEngineer
 * REVISION: 2.0 - Optimized for Arduino Uno R4
 * * DESCRIPTION:
 * This program demonstrates high-priority event handling using multiple Hardware Interrupts.
 * It bypasses standard loop execution to ensure zero-latency response for UI elements.
 * * KEY FEATURES:
 * 1. MULTI-INTERRUPT ARCHITECTURE: 
 * - Pin 8: Increments a 16-bit counter and toggles a Status LED.
 * - Pin 3: Triggers an immediate System Reset (Counter to 0, LED to OFF).
 * 2. ARCHITECTURAL OPTIMIZATION: 
 * - Uses 'stdint.h' for fixed-width integers (uint8_t, uint16_t, uint32_t).
 * 3. HIGH-SPEED TELEMETRY: 
 * - Communicates at 115200 Baud with F() macro optimization to preserve 
 * SRAM and reduce serial latency.
 * 4. ROBUST DEBOUNCING: 
 * - Non-blocking software filter implemented within the ISR to eliminate 
 * mechanical contact noise without stalling the CPU.
 * * LICENSE: CC BY-NC-SA 4.0
 * See README.md for full technical documentation and circuit schematics.
 */

#include <stdint.h>

// --- PIN CONFIGURATION ---
constexpr uint8_t BTN_PIN_COUNT = 8;   // Counter/Toggle Button
constexpr uint8_t BTN_PIN_RESET = 3;   // Reset Button
constexpr uint8_t STATUS_LED_PIN = 4;  // Output LED

// --- SETTINGS ---
constexpr uint32_t DEBOUNCE_DELAY = 200; 

// --- GLOBAL VARIABLES ---
volatile uint16_t pressCounter = 0;      // 16-bit as requested
volatile uint32_t lastInterruptTime = 0; // 32-bit for millis() consistency
volatile bool ledState = false;

uint16_t lastReportedCount = 0;

// ISR Function Prototypes
void handleButtonToggle();
void handleReset();

void setup() {
  Serial.begin(115200);
  
  while (!Serial) {
  }

  pinMode(BTN_PIN_COUNT, INPUT_PULLUP);
  pinMode(BTN_PIN_RESET, INPUT_PULLUP);
  pinMode(STATUS_LED_PIN, OUTPUT);
  
  digitalWrite(STATUS_LED_PIN, ledState);

  // Attach Interrupt for Button 1 (Toggle & Count)
  attachInterrupt(digitalPinToInterrupt(BTN_PIN_COUNT), handleButtonToggle, FALLING);
  
  // Attach Interrupt for Button 2 (Reset)
  attachInterrupt(digitalPinToInterrupt(BTN_PIN_RESET), handleReset, FALLING);
  
  Serial.println(F("Uno R4 Dual-Interrupt System Ready."));
  Serial.println(F("Pin 8: Count/Toggle | Pin 3: Reset"));
}

void loop() {
  uint16_t currentCount = pressCounter;

  // Detect count change (including reset to 0)
  if (currentCount != lastReportedCount) {
    Serial.print(F("Counter Update: "));
    Serial.println(currentCount);
    
    lastReportedCount = currentCount;
  }
}

// ISR 1: Increments the 16-bit counter and toggles the LED.
void handleButtonToggle() {
  uint32_t currentTime = millis();
  if (currentTime - lastInterruptTime > DEBOUNCE_DELAY) {
    pressCounter++;
    ledState = !ledState;
    digitalWrite(STATUS_LED_PIN, ledState);
    lastInterruptTime = currentTime;
  }
}

// ISR 2: Resets the counter and ensures the LED is OFF.
void handleReset() {
  // Reset logic is extremely fast, so it's perfect for an ISR
  // no need for the debounce here.
  pressCounter = 0;
  ledState = false;
  digitalWrite(STATUS_LED_PIN, LOW);
}