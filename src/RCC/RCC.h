/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** @file RCC.h
 * @brief Header file for system clock and power mode management.
 * This file contains the definitions for configuring the system clock (HIRC, LIRC),
 * managing power modes (SLEEP, IDLE), and configuring the Watchdog Timer (WDT).
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#ifndef RCC_H__
#define RCC_H__

#include "BA45F5240.h"

// Oscillator settings (HIRC - High-speed Internal RC oscillator)
#define INTERNAL_8_MHZ    0b00000010  // High-speed 8 MHz RC oscillator
#define INTERNAL_4_MHZ    0b00000001  // High-speed 4 MHz RC oscillator
#define INTERNAL_2_MHZ    0b00000000  // High-speed 2 MHz RC oscillator

// Oscillator settings (LIRC - Low-speed Internal RC oscillator)
#define LIRC_32KHZ        0b00000011  // Low-speed 32kHz RC oscillator

// SCC Register Clock Division Settings
#define SCC_CLOCK_DIV_1   0b00000000  // No division (Full speed)
#define SCC_CLOCK_DIV_2   0b00000001  // Divide by 2
#define SCC_CLOCK_DIV_4   0b00000010  // Divide by 4
#define SCC_CLOCK_DIV_8   0b00000011  // Divide by 8

// Power Modes and Idle Modes (SCC Register)
#define SCC_FAST_MODE     0b00000000  // Full speed operation
#define SCC_SLOW_MODE     0b00000001  // Low speed operation using LIRC
#define SCC_IDLE0_MODE    0b00000010  // IDLE0: CPU stopped, LIRC active
#define SCC_IDLE1_MODE    0b00000011  // IDLE1: CPU stopped, both HIRC and LIRC active
#define SCC_SLEEP_MODE    0b00000100  // SLEEP: CPU and peripherals stopped

// Watchdog Timer (WDT) Timeout Values
#define WDT_TIMEOUT_16_MS   0b00000000  // 16 ms
#define WDT_TIMEOUT_32_MS   0b00000001  // 32 ms
#define WDT_TIMEOUT_64_MS   0b00000010  // 64 ms
#define WDT_TIMEOUT_128_MS  0b00000011  // 128 ms
#define WDT_TIMEOUT_256_MS  0b00000100  // 256 ms
#define WDT_TIMEOUT_512_MS  0b00000101  // 512 ms
#define WDT_TIMEOUT_1_SEC   0b00000110  // 1 second
#define WDT_TIMEOUT_2_SEC   0b00000111  // 2 seconds
#define WDT_TIMEOUT_4_SEC   0b00001000  // 4 seconds

// Wake-up Pin Configurations
#define WAKE_UP_KEY_PIN    _pawu4 = 1  // Enable PA4 wake-up
#define PULL_HIGH_KEY      _papu4 = 1  // Enable pull-up for PA4

// Configuration macros
#define CONFIG_CLOCK_OVER    INTERNAL_8_MHZ  // Default clock setting
#define CONFIG_WDT           WDT_TIMEOUT_4_SEC  // Default WDT setting

// Function prototypes
void RCC_Init(void);
void Enter_Sleep_Mode(void);
void Enter_Idle0_Mode(void);
void Enter_Idle1_Mode(void);
void Enter_Fast_Mode(void);  
void Enable_Watchdog(void);
void Disable_Watchdog(void);

#endif  // RCC_H__
