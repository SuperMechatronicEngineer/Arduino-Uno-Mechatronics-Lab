/*
 * Project: Dynamic Name Acquisition System
 * Date: 2026-03-06
 * Revision: 1.1 - Improved Version
 * DESCRIPTION:
 * This program solves the "static array limitation" by allowing the user 
 * to specify the number of entries AT RUNTIME. Unlike standard Arduino 
 * sketches where array sizes must be known before compiling, this system
 * adapts its memory usage to the user's specific needs during execution.
 * Author: SuperMechatronicEngineer
 * License: CC BY-NC-SA 4.0
 * See README.md for full technical documentation.
 */

#include <new> // Required for (std::nothrow)

void setup() {
  Serial.begin(115200);
  
  // Set a short timeout (100ms) to ensure responsiveness 
  // even with "No Line Ending" selected in the Serial Monitor.
  Serial.setTimeout(100); 

  while (!Serial); // Wait for Serial Monitor to open (USB Handshake)
  
  Serial.println(F("============================================="));
  Serial.println(F("       DYNAMIC NAME ACQUISITION SYSTEM       "));
  Serial.println(F("============================================="));
  Serial.println(F("Status: Ready. Any 'Line Ending' supported."));
}

void loop() {
  int numNames = 0;

  // 1. INPUT VALIDATION LOOP
  while (numNames <= 0) {
    Serial.println(F("\nHow many names do you want to enter?"));
    
    while (Serial.available() == 0); // Active wait for user input
    
    numNames = Serial.parseInt();
    clearBuffer(); // Clean the hardware buffer from '\n' or '\r'

    if (numNames <= 0) {
      Serial.println(F("Error: Please enter a positive integer."));
    }
  }

  Serial.print(F("Allocating heap memory for "));
  Serial.print(numNames);
  Serial.println(F(" strings..."));

  // 2. DYNAMIC HEAP ALLOCATION WITH SAFETY CHECK
  // (std::nothrow) prevents the board from crashing if RAM is full.
  // Instead, it returns 'nullptr'.
  String* nameList = new (std::nothrow) String[numNames];

  // Safety check: verify if the pointer is null (Allocation Failed)
  if (nameList == nullptr) {
    Serial.println(F("!!! FATAL ERROR: Out of Memory (SRAM Full) !!!"));
    Serial.println(F("Try a smaller number of names."));
    return; // Restart the loop from the beginning
  }

  // 3. DATA ACQUISITION
  for (int i = 0; i < numNames; i++) {
    Serial.print(F("Enter name #"));
    Serial.print(i + 1);
    Serial.print(F(": "));

    while (Serial.available() == 0); // Wait for user to type
    
    nameList[i] = Serial.readString(); 
    nameList[i].trim(); // Remove whitespace/newlines from the string
    
    Serial.println(nameList[i]); // User confirmation
  }

  // 4. RESULTS DISPLAY
  Serial.println(F("\n--- Final List of Stored Names ---"));
  for (int i = 0; i < numNames; i++) {
    Serial.print(i + 1);
    Serial.print(F(". "));
    Serial.println(nameList[i]);
  }

  // 5. MANUAL MEMORY CLEANUP
  // We MUST use delete[] because we allocated an array with new[] in the heap memory.
  delete[] nameList;
  
  // 6. SESSION RESTART
  Serial.println(F("Type ANY CHARACTER and press Enter to restart..."));
  
  while (Serial.available() == 0); // Wait for interaction
  clearBuffer();                   // Flush the restart keypress
  Serial.println(F("---------------------------------------------"));
}

/**
 * Utility: Flushes the Serial UART buffer to ensure the next 
 * input call starts with a clean slate.
 */
void clearBuffer() {
  delay(10); // Sync delay: wait for slow serial bits to arrive
  while (Serial.available() > 0) {
    Serial.read(); // Discard the byte
  }
}