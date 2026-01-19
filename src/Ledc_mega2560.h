#ifndef Ledc_mega2560_H
#define Ledc_mega2560_H

#include "Arduino.h"

class ledc
{

private:
public:
  ledc() {}

  /**
   * @brief Configures the PWM settings for the specified pin.
   *
   * This function sets up the Pulse Width Modulation (PWM)
   * on the specified pin using the given frequency and resolution.
   *
   * @param pin_PWM        setup pin for output
   * @param freq           pwm hz
   * pin 11 12 13.
   * resoultion bits 10 bits / 1023 bits.
   * can use only 15khz 2khz 800hz.
   * resoultion bits 8 bits / 255 bits.
   * can use only 8khz 12khz.
   * for pin 9 10.
   * resultion bits 255 bits / 8 bits.
   * 8khz only.
   * for pin 8 7 6.
   * resultion bits 1023 bits / 10 bits.
   * 15khz 2khz.
   * resultion bits 255 bits / 8 bits.
   * 8khz only.
   * for pin 5 3 2.
   * resoultion bits 1023 bits / 10 bits.
   * 15khz 2khz.
   * resoultion bits 255 bits / 8 bits.
   * 8khz only.
   * @param resolution_bits The resolution of the PWM signal in bits.
   *                        For example, 8 bits allows values from 0-255.
   *                        and, 10 bits allows values from 0-1023.
   * @return void          This function does not return a value.
   */
  void Setup_mega2560(int pin_PWM, int freq, int resolution_bits);
  /**
   * @brief This function generates a PWM signal on the specified pin and
   * configures the direction of the motor based on the duty cycle.
   *
   * @param pin_PWM  The PWM output pin to control speed.
   * @param duty     The duty cycle for the PWM signal. Negative values reverse the motor.
   */
  void attch_mega2560(uint8_t pin_PWM, int32_t duty);
};

#endif