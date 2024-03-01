void setupPWM() {
  // Timer 1
  TCCR1A |= (1 << 1);                        // 00000010, set WGM1 to 1
  TCCR1B |= (1 << 3) | (1 << 4) | (1 << 0);  // 00011001, set WGM2 and WGM3 to 1, set CS0 to 1 for Fclk/1 prescaler.
  // 1023 -> 0000_0011_1111_1111
  // Set counter TOP value to 1023
  ICR1H = (uint8_t)(1023 >> 8);  // 0000_0011
  ICR1L = (uint8_t)1023;         // 1111_1111

  // Timer 3
  TCCR3A |= (1 << 1);                        // 00000010, set WGM1 to 1
  TCCR3B |= (1 << 3) | (1 << 4) | (1 << 0);  // 00011001, set WGM2 and WGM3 to 1, set CS0 to 1 for Fclk/1 prescaler.
  // 1023 -> 0000_0011_1111_1111
  // Set counter TOP value to 1023
  ICR3H = (uint8_t)(1023 >> 8);  // 0000_0011
  ICR3L = (uint8_t)1023;         // 1111_1111

  // Timer 4
  TCCR4A |= (1 << 1);                        // 00000010, set WGM1 to 1
  TCCR4B |= (1 << 3) | (1 << 4) | (1 << 0);  // 00011001, set WGM2 and WGM3 to 1, set CS0 to 1 for Fclk/1 prescaler.
  // 1023 -> 0000_0011_1111_1111
  // Set counter TOP value to 1023
  ICR4H = (uint8_t)(1023 >> 8);  // 0000_0011
  ICR4L = (uint8_t)1023;         // 1111_1111
}

void setPWm(uint8_t pin, uint16_t val) {
  if (val > 1023)
    return;

  switch (pin) {
    case 2:
      OCR3BH = (uint8_t)(val >> 8);
      OCR3BL = (uint8_t)val;
      break;

    case 3:
      OCR3CH = (uint8_t)(val >> 8);
      OCR3CL = (uint8_t)val;
      break;

    case 5:
      OCR3AH = (uint8_t)(val >> 8);
      OCR3AL = (uint8_t)val;
      break;

    case 6:
      OCR4AH = (uint8_t)(val >> 8);
      OCR4AL = (uint8_t)val;
      break;

    case 11:
      OCR1AH = (uint8_t)(val >> 8);
      OCR1AL = (uint8_t)val;
      break;

    case 12:
      OCR1BH = (uint8_t)(val >> 8);
      OCR1BL = (uint8_t)val;
      break;

    default:
      return;
  }
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}
void loop() {

}
