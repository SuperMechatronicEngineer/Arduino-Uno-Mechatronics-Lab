/*
 * Project: Dual-Rate Asynchronous LED Controller
 * Date: 2026-03-15
 * Revision: 1.1 - Non-Blocking Multitasking
 * * DESCRIPTION:
 * This program implements a multitasking architecture that allows multiple 
 * independent processes to run simultaneously on the Arduino UNO R4. 
 * By replacing the restrictive delay() function with a time-differential 
 * logic based on millis(), the system achieves a "Zero-Latency" execution.
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

// Pin definitions using industry-standard types
constexpr uint8_t FAST_LED_PIN = 2;
constexpr uint8_t SLOW_LED_PIN = 3;

// Timing variables (Must be unsigned long / uint32_t for millis)
uint32_t previousMillisFast = 0;
uint32_t previousMillisSlow = 0;

// Intervals in milliseconds
constexpr uint32_t FAST_INTERVAL = 500;  // 0.5 seconds
constexpr uint32_t SLOW_INTERVAL = 2000; // 2.0 seconds

// State variables to track LED status
bool fastLedState = LOW;
bool slowLedState = LOW;

void setup() {
  // Initialize digital pins as outputs
  pinMode(FAST_LED_PIN, OUTPUT);
  pinMode(SLOW_LED_PIN, OUTPUT);
}

void loop() {
  // Capture the current time (Snapshot)
  uint32_t currentMillis = millis();

  // --- FAST LED LOGIC (0.5s ON / 0.5s OFF) ---
  // Check if the time elapsed is greater than or equal to the interval
  if (currentMillis - previousMillisFast >= FAST_INTERVAL) {
    // Update the timestamp for the next toggle
    previousMillisFast = currentMillis;
    
    // Toggle the state (if HIGH becomes LOW, if LOW becomes HIGH)
    fastLedState = !fastLedState;
    digitalWrite(FAST_LED_PIN, fastLedState);
  }

  // --- SLOW LED LOGIC (2s ON / 2s OFF) ---
  if (currentMillis - previousMillisSlow >= SLOW_INTERVAL) {
    // Update the timestamp for the next toggle
    previousMillisSlow = currentMillis;
    
    // Toggle the state
    slowLedState = !slowLedState;
    digitalWrite(SLOW_LED_PIN, slowLedState);
  }
}