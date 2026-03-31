/*
 * Project: Non-blocking State Machine for Unipolar Stepper Motor (28BYJ-48) with ULN2003 Driver
 * Lesson: Arduino Uno R4 WiFi LESSON 49: Arduino Stepper Motor Control
 * Revision: 1.2 - Final Version
 * Note: We use the 28BYJ-48 stepper motor, and the ULN2003 Stepper Motor Driver.
 * Date: 2026-03-30
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <Arduino.h>

/**
 * @class StepperDriver
 * @brief Non-blocking driver for 28BYJ-48 stepper motors using the ULN2003 driver.
 */
class StepperDriver {
private:
    const uint8_t motorPins[4];
    
    // 8-Step Half-Step table for maximum smoothness and torque
    static constexpr uint8_t HALF_STEP_TABLE[8][4] = {
        {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0},
        {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}
    };

    int8_t currentStepIndex = 0;
    uint32_t lastStepTimestamp = 0;
    uint32_t stepInterval = 2; // Default speed in milliseconds

public:
    // Constructor: Maps physical pins to the internal array.
    StepperDriver(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4) 
        : motorPins{p1, p2, p3, p4} {}

    // Configures pins as outputs and ensures they start in a LOW state.
    void begin() {
        for (uint8_t i = 0; i < 4; i++) {
            pinMode(motorPins[i], OUTPUT);
            digitalWrite(motorPins[i], LOW);
        }
    }

    /**
     * Updates the speed of the motor.
     * @param intervalMs Time between steps (lower is faster).
     */
    void setSpeed(uint32_t intervalMs) {
        stepInterval = intervalMs;
    }

    /**
     * Core State Machine for stepping. 
     * @param clockwise Direction of rotation.
     * @return true if a physical step was performed, false if waiting for timer.
     */
    bool update(bool clockwise) {
        uint32_t now = millis();
        if (now - lastStepTimestamp >= stepInterval) {
            lastStepTimestamp = now;
            
            // Move the index within the circular buffer (0-7)
            if (clockwise) {
                currentStepIndex = (currentStepIndex + 1) % 8;
            } else {
                currentStepIndex = (currentStepIndex - 1 + 8) % 8;
            }

            // Apply the bit pattern from the table to the physical pins
            for (uint8_t i = 0; i < 4; i++) {
                digitalWrite(motorPins[i], HALF_STEP_TABLE[currentStepIndex][i]);
            }
            return true; 
        }
        return false;
    }

    // Disables all coils to prevent overheating and save power.
    void release() {
        for (uint8_t i = 0; i < 4; i++) {
            digitalWrite(motorPins[i], LOW);
        }
    }
};

// --- Hardware Pinout Configuration ---
constexpr uint8_t PIN_IN1 = 8;
constexpr uint8_t PIN_IN2 = 9;
constexpr uint8_t PIN_IN3 = 10;
constexpr uint8_t PIN_IN4 = 11;

// --- Motion Parameters ---
constexpr uint32_t SPEED_MS = 2;         // Pulse width in milliseconds
constexpr uint32_t PAUSE_DURATION = 1000; // Delay between direction changes (ms)
constexpr uint32_t STEPS_PER_REV = 4096;  // Full 360-degree rotation in Half-Step mode

// --- System States ---
enum SystemState { 
    ROTATING_CW, 
    PAUSE_CW, 
    ROTATING_CCW, 
    PAUSE_CCW 
};

SystemState currentState = ROTATING_CW;
uint32_t stateTimer = 0;
uint32_t stepsCounter = 0; // Tracks performed steps within the current state

// Global instance of the motor controller
StepperDriver motor(PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4);

void setup() {
    motor.begin();
    motor.setSpeed(SPEED_MS);
    stepsCounter = 0; 
}

void loop() {
    uint32_t currentTimestamp = millis();

    switch (currentState) {
        case ROTATING_CW:
            // Attempt a step; if successful (true), increment the counter
            if (motor.update(true)) {
                stepsCounter++;
            }
            
            // Transition to pause once a full revolution is reached
            if (stepsCounter >= STEPS_PER_REV) {
                motor.release();
                stepsCounter = 0; 
                stateTimer = currentTimestamp;
                currentState = PAUSE_CW;
            }
            break;

        case PAUSE_CW:
            if (currentTimestamp - stateTimer >= PAUSE_DURATION) {
                currentState = ROTATING_CCW;
            }
            break;

        case ROTATING_CCW:
            if (motor.update(false)) {
                stepsCounter++;
            }
            
            if (stepsCounter >= STEPS_PER_REV) {
                motor.release();
                stepsCounter = 0;
                stateTimer = currentTimestamp;
                currentState = PAUSE_CCW;
            }
            break;

        case PAUSE_CCW:
            if (currentTimestamp - stateTimer >= PAUSE_DURATION) {
                currentState = ROTATING_CW;
            }
            break;
    }
}