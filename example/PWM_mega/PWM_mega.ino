#include "Ledc_mega2560.h"

ledc myPWM;

void setup() {
  Serial.begin(9600);

  // 1. Configure Pin 11 (Timer 1): 15kHz frequency, 10-bit resolution
  myPWM.Setup_mega2560(11, 15000, 10);

  // 2. Configure Pin 6 (Timer 4): 2kHz frequency, 10-bit resolution
  myPWM.Setup_mega2560(6, 2000, 10);

  // 3. Configure Pin 9 (Timer 2): 8kHz frequency, 8-bit resolution (Timer 2 is 8-bit only)
  myPWM.Setup_mega2560(9, 8000, 8);
}

void loop() {
  // --- Test Pin 11 (10-bit range: 0-1023) ---
  
  // Drive motor in one direction at 50% speed
  myPWM.attch_mega2560(11, 512); 

  // --- Test Pin 6 (10-bit range) ---
  myPWM.attch_mega2560(6, 250); // Approx. 25% Duty cycle
  delay(1000);

  // --- Test Pin 9 (8-bit range: 0-255) ---
  // Drive motor in one direction at 50% speed
  myPWM.attch_mega2560(9, 125);
}