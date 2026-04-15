/* PROJECT: Interrupt-Based Preemption over Blocking Tasks
 * DATE: 2026-03-24
 * REVISION: 1.1 - Final Version for Arduino Uno R4
 * DESCRIPTION:
 * This program demonstrates why Interrupts are essential in real-time embedded systems.
 * 1. STATUS LED: Blinks slowly using a blocking delay(2000) to simulate a heavy CPU task.
 * 2. USER LED: Toggled via a Hardware Interrupt (ISR) to show immediate responsiveness.

 * LICENSE: CC BY-NC-SA 4.0
 * See README.md for full technical documentation and circuit schematics.
 */

#include <stdint.h>

// --- PIN CONFIGURATION ---
constexpr uint8_t USER_LED_PIN = 3;   // Toggled by Interrupt
constexpr uint8_t STATUS_LED_PIN = 4; // Blinks slowly in the Loop
constexpr uint8_t BTN_PIN = 8;         // Hardware Interrupt Pin

constexpr uint16_t DEBOUNCE_DELAY = 200;
constexpr uint16_t BLOCKING_TIME = 2000; 

// --- GLOBAL VARIABLES ---
volatile bool userLedState = false;
volatile uint32_t lastInterruptTime = 0;

// Forward declaration for the Interrupt Service Routine
void handleButtonToggle();

void setup() {
  pinMode(USER_LED_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  // Link the interrupt to the button (triggers on press)
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), handleButtonToggle, FALLING);
}

void loop() {
  // --- BLOCKING TASK ---
  digitalWrite(STATUS_LED_PIN, HIGH);
  delay(BLOCKING_TIME);
  digitalWrite(STATUS_LED_PIN, LOW);
  delay(BLOCKING_TIME); 
}

/**
 * INTERRUPT SERVICE ROUTINE (ISR)
 * This function bypasses the delay() in the loop. 
 */
void handleButtonToggle() {
  uint32_t currentTime = millis();

  // Standard software debounce filter
  if (currentTime - lastInterruptTime > DEBOUNCE_DELAY) {
    userLedState = !userLedState;
    digitalWrite(USER_LED_PIN, userLedState);
    
    lastInterruptTime = currentTime;
  }
}