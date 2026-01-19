# Ledc_mega2560

A high-performance PWM control library for **Arduino Mega 2560**, designed for motor control applications requiring high frequency and high resolution.

This library bypasses the standard Arduino `analogWrite` functions to utilize **Direct Register Access** on the ATmega2560's timers (Timer 1, 2, 3, and 4). It allows for 10-bit resolution and custom frequencies (up to 15kHz), eliminating motor whine and providing smoother control.

## Features

- **High Resolution:** Supports **10-bit (0-1023)** resolution for finer control steps (vs standard 8-bit).
- **High Frequency:** Pre-configured presets for **15kHz**, **2kHz**, and **800Hz** to suit various motor drivers.
- **Multiple Timers:** Simultaneous control across Timer 1, 2, 3, and 4.
- **Direct Hardware Control:** Optimized C++ implementation manipulating `TCCR`, `ICR`, and `OCR` registers directly.

## Hardware Support

- **Microcontroller:** Arduino Mega 2560 (ATmega2560)
- **Supported Pins:** 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13

## Pin & Timer Mapping

| Timer | Pins | Max Resolution | Supported Frequencies |
| :---: | :--- | :---: | :--- |
| **Timer 1** | 11, 12, 13 | 10-bit | 15kHz, 2kHz, 800Hz, 8kHz(8-bit), 12kHz(8-bit) |
| **Timer 3** | 2, 3, 5 | 10-bit | 15kHz, 2kHz, 8kHz(8-bit) |
| **Timer 4** | 6, 7, 8 | 10-bit | 15kHz, 2kHz, 8kHz(8-bit) |
| **Timer 2** | 9, 10 | 8-bit | 8kHz (Fixed) |

> **Note:** Timer 2 is an 8-bit timer on the ATmega2560 hardware, so it is limited to 255 resolution steps.

## Technical Architecture & Register Configuration

This library operates by directly manipulating the ATmega2560's Timer/Counter registers. Below are the specific configurations used to achieve the target frequencies.

### 1. 16-bit Timers (Timer 1, 3, 4)
These timers are configured in **Fast PWM Mode 14** (`WGMn3:0 = 1110`). In this mode, the TOP value is defined by the `ICRn` (Input Capture Register), allowing for precise frequency control.

**Frequency Formula:**
$$F_{PWM} = \frac{F_{CPU}}{Prescaler \times (1 + ICRn)}$$

| Target Frequency | Prescaler (N) | ICRn Value | Actual Frequency |
| :--- | :---: | :---: | :--- |
| **15 kHz** | 1 | 1066 | $16MHz / (1 \times 1067) \approx 14,995 \text{ Hz}$ |
| **2 kHz** | 8 | 999 | $16MHz / (8 \times 1000) = 2,000 \text{ Hz}$ |
| **800 Hz** | 8 | 2300 | $16MHz / (8 \times 2301) \approx 869 \text{ Hz}$ |

*Note: For 15kHz @ 10-bit resolution, the ICR is set to 1066. Since the input range (0-1023) is slightly lower than the TOP value (1066), the maximum duty cycle is approximately 96%.*

### 2. 8-bit Timer (Timer 2)
Timer 2 is an 8-bit timer configured in **Fast PWM Mode 3** (`WGM21:0 = 11`). The TOP value is fixed at `0xFF` (255).

**Frequency Formula:**
$$F_{PWM} = \frac{F_{CPU}}{Prescaler \times 256}$$

| Target Frequency | Prescaler (N) | Register Setting | Actual Frequency |
| :--- | :---: | :---: | :--- |
| **8 kHz** | 8 | `CS21` | $16MHz / (8 \times 256) \approx 7,812.5 \text{ Hz}$ |

### 3. Register Bit Map
The library sets the following control bits to enable PWM output on specific pins:

- **TCCRnA:** Controls Output Compare mode (COMnx1) to enable non-inverting PWM on pins.
- **TCCRnB:** Controls the Waveform Generation Mode (WGM) and Clock Select (CS/Prescaler).
