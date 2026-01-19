#include "Ledc_mega2560.h"

void ledc::Setup_mega2560(int pin_PWM, int freq, int resolution_bits) {
  pinMode(pin_PWM, OUTPUT);
  if (resolution_bits == 8) {
    resolution_bits = 255;
  }
  if (resolution_bits == 10) {
    resolution_bits = 1023;
  }


  //Timer 1
  if ((pin_PWM == 11) || (pin_PWM == 12) || (pin_PWM == 13)) {
    //setup mode Fast PWM
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << COM1C1) | (1 << COM1B1);
    TCCR1B = (1 << WGM13) | (1 << WGM12);
    // TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);

    // Set freq
    if (resolution_bits == 1023) {
      if (freq == 15000) {
        TCCR1B |= (1 << CS10);  // Prescaler = 1
        ICR1 = 1066;
      }
      if (freq == 2000) {
        TCCR1B |= (1 << CS11);  // Prescaler = 8
        ICR1 = 999;
      }
      if (freq == 800) {
        TCCR1B |= (1 << CS11);  // Prescaler = 8
        ICR1 = 2300;
      }
    }
    if (resolution_bits == 255) {
      if (freq == 8000) {
        TCCR1B |= (1 << CS10);
        ICR1 = 368;
      }
      if (freq == 12000) {
        TCCR1B = (0 << CS12) | (0 << CS11) | (1 << CS10);
        ICR1 = 166;
      }
    }
  }

  //Timer 3
  if ((pin_PWM == 2) || (pin_PWM == 3) || (pin_PWM == 5)) {
    //setup mode Fast PWM
    TCCR3A = (1 << COM3B1) | (1 << WGM31);
    TCCR3B = (1 << WGM33) | (1 << WGM32);
    // Set freq
    if (resolution_bits == 1023) {
      if (freq == 15000) {
        TCCR3B |= (1 << CS30);
        ICR3 = 1040;
      }
      if (freq == 2000) {
        TCCR3B |= (1 << CS31);
      }
    }
    if (resolution_bits == 255) {
      if (freq == 8000) {
        TCCR3B |= (1 << CS31);
      }
    }
  }

  //Timer 4
  if ((pin_PWM == 6) || (pin_PWM == 7) || (pin_PWM == 8)) {
    //setup mode Fast PWM
    // TCCR4A |= (1 << COM4A1) | (1 << COM4B1) | (1 << COM4C1) | (1 << WGM41);
    TCCR4A = (1 << COM4A1) | (1 << WGM41) | (1 << COM4B1);
    TCCR4B = (1 << WGM43) | (1 << WGM42);
    // TCCR4B |= (1 << WGM43) | (1 << WGM42);

    // Set freq
    if (resolution_bits == 1023) {
      if (freq == 15000) {
        TCCR4B |= (1 << CS40);
        ICR4 = 1065;
      }
      if (freq == 2000) {
        TCCR4B |= (1 << CS41);
        ICR4 = 1000;
      }
    }
    if (resolution_bits == 255) {
      if (freq == 8000) {
        TCCR4B |= (1 << CS42) | (0 << CS41) | (0 << CS40);
        ICR4 = 12;
      }
    }
  }

  //Timer 2
  if ((pin_PWM == 9) || (pin_PWM == 10)) {
    //setup mode Fast PWM
    TCCR2A = (1 << WGM21) | (1 << WGM20);  //
    TCCR2B = (1 << CS21);                  // Prescaler = 8

    // Set non-inverting mode
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1);

    // Set freq
    if (resolution_bits == 255) {
      if (freq == 8000) {
        TCCR2B |= (1 << CS21);  //prescaler 8
      }
    }
  }
}


void ledc::attch_mega2560(uint8_t pin_PWM, int32_t duty) {
  uint16_t duty_16b = ((duty < 0) ? -duty : duty);


  switch (pin_PWM) {
    //Timer 1
    case 11:
      OCR1AH = (uint8_t)(duty_16b >> 8);
      OCR1AL = (uint8_t)duty_16b;
      break;

    case 12:
      OCR1BH = (uint8_t)(duty_16b >> 8);
      OCR1BL = (uint8_t)duty_16b;
      break;

    case 13:
      OCR1CH = (uint8_t)(duty_16b >> 8);
      OCR1CL = duty_16b;
      break;

    case 2:
      OCR3BH = (uint8_t)(duty_16b >> 8);
      OCR3BL = (uint8_t)duty_16b;
      break;

    case 3:
      OCR3CH = (uint8_t)(duty_16b >> 8);
      OCR3CL = (uint8_t)duty_16b;
      break;

    case 5:
      OCR3AH = (uint8_t)(duty_16b >> 8);
      OCR3AL = (uint8_t)duty_16b;
      break;

    //Timer 4
    case 6:
      OCR4AH = (uint8_t)(duty_16b >> 8);
      OCR4AL = (uint8_t)duty_16b;
      break;

    case 7:
      OCR4BH = (uint8_t)(duty_16b >> 8);
      OCR4BL = (uint8_t)duty_16b;
      break;

    case 8:
      OCR4CH = (uint8_t)(duty_16b >> 8);
      OCR4CL = (uint8_t)duty_16b;
      break;

    //Timer 2
    case 9:
      OCR2B = (uint8_t)duty_16b;
      break;

    case 10:
      OCR2A = (uint8_t)duty_16b;
      break;

    default:
      return;
  }
}