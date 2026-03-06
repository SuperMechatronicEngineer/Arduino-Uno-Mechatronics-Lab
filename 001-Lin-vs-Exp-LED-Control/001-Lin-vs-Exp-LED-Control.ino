/*
 * Project:     Linear vs. Exponential LED PWM Control
 * Date:        2026-02-11
 * Revision:    1.1 - Improved Version
 * Description: A comparative study between Linear Scaling and 
 *              Base-2 Exponential Mapping. 
 *              10-bit Input Resolution mapped to 8-bit PWM Output.
 * Hardware:    Pin 10: Linear Output | Pin 11: Exponential Output
 * Formulas:    Exponential Y = (2^(x / 127.875)) - 1
 *              Linear Y = (255 / 1023) * x  
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

const int LED_EXPONENTIAL = 11; 
const int LED_LINEAR = 10;      
const int FADE_DELAY = 5;       // 5ms delay * 1024 steps = ~5.2s per fade cycle phase
const int BOOT_DELAY = 3000;    // Safety delay to initialize Serial Monitor

int x = 0;              // 10-bit virtual counter (Range: 0 - 1023)
int fadeAmount = 1;     // Unitary increment for maximum resolution

void setup() {
  Serial.begin(115200);
  pinMode(LED_LINEAR, OUTPUT);
  pinMode(LED_EXPONENTIAL, OUTPUT);
  
  // Wait for Serial connection
  while (!Serial); 
  
  delay(BOOT_DELAY);
  Serial.println();
  Serial.println("--- Mechatronics Lab: Linear vs. Exponential Comparison ---");
  Serial.println("Input Range: 0-1023 (10-bit) | Output Range: 0-255 (8-bit)");
}

void loop() {
  // 1. LINEAR MANAGEMENT (Pin 10)
  // Standard proportional scaling: y = (255/1023) * x
  // At 50% of the cycle (x=511), the LED is already at 50% power (y=127).
  float yLinear = (255.0 / 1023.0) * x;

  // 2. EXPONENTIAL MANAGEMENT (Pin 11)
  // Based on the formula: y = (2^(x / 127.875)) - 1
  // This divides the 1024 steps into 8 "octaves" (1024 / 127.875 = 8).
  // At 50% of the cycle (x=511), the LED is only at ~6% power (y=15).
  float yExp = pow(2, (x / 127.875)) - 1;

  // 3. MONITORING
  // Printing every 10 steps to maintain performance and readability
  if (x % 10 == 0) {
    Serial.print("Step X: ");      Serial.print(x);
    Serial.print(" | Linear Y: "); Serial.print((int)yLinear);
    Serial.print(" | Exp Y: ");    Serial.println((int)yExp);
  }

  // 4. SIGNAL OUTPUT
  // We cast the float values to int for the analogWrite function
  analogWrite(LED_LINEAR, (int)yLinear);
  analogWrite(LED_EXPONENTIAL, (int)yExp);

  // 5. BOUNCE LOGIC
  x += fadeAmount;

  // Reverse direction when boundaries (0 or 1023) are reached
  if (x <= 0 || x >= 1023) {
    fadeAmount = -fadeAmount; 
  }

  delay(FADE_DELAY);
}