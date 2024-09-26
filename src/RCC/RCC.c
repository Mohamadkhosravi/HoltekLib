/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** @file RCC.c
 * @brief Implementation of system clock and power mode management functions.
 * This file provides the definitions for configuring the system clock (HIRC, LIRC),
 * managing power modes (SLEEP, IDLE, FAST), and configuring the Watchdog Timer (WDT).
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#include "RCC.h"

/** @brief Initializes the system clock and power settings.
 * This function configures the system clock using the high-speed internal RC oscillator (HIRC)
 * and the low-speed internal RC oscillator (LIRC) as needed. It also configures the Watchdog Timer (WDT)
 * and wake-up configurations.
 */
void RCC_Init()
{
    // Configure the system clock (SCC Register)
    _scc = SCC_FAST_MODE | SCC_CLOCK_DIV_1;  // Set fast mode with no clock division

    // Enable HIRC and select the desired frequency (HIRC Register)
    #if CONFIG_CLOCK_OVER == INTERNAL_8_MHZ
        _hircc = INTERNAL_8_MHZ | 0b00001000;  // Enable HIRC, 8 MHz
    #elif CONFIG_CLOCK_OVER == INTERNAL_4_MHZ
        _hircc = INTERNAL_4_MHZ | 0b00001000;  // Enable HIRC, 4 MHz
    #else
        _hircc = INTERNAL_2_MHZ | 0b00001000;  // Enable HIRC, 2 MHz
    #endif

    // Wait for HIRC stabilization (HIRCF Flag)
    while (!(_hircf & 0x01));  // Wait for HIRC to stabilize

    // Additional delay to ensure complete stabilization
    GCC_DELAY(HIRC_STABILIZE_DELAY);  // Delay based on required stabilization time

    // Enable LIRC for low-speed operations (LIRC Register)
    _lircen = LIRC_32KHZ;  // Enable LIRC 32kHz for low-speed operations

    // Configure Watchdog Timer (WDTC Register)
    _wdtc = 0b10101000 | CONFIG_WDT;  // Enable WDT with selected timeout

    // Wake-up configuration (PAWU and PAPU Registers)
    WAKE_UP_KEY_PIN;  // Enable wake-up on PA4 pin
    PULL_HIGH_KEY;    // Enable pull-up on PA4 pin

    // Final SCC configuration (Power Modes)
    _scc = SCC_FAST_MODE | SCC_CLOCK_DIV_1;  
}

/** @brief Enters the sleep mode.
 * This function configures the system to enter the SLEEP mode, where the CPU and peripherals
 * are stopped, but the low-speed oscillator (LIRC) remains active for WDT.
 */
void Enter_Sleep_Mode(void)
{
    // Enter SLEEP mode
    _scc = SCC_SLEEP_MODE;
    _halt();  // Execute HALT instruction to enter sleep mode
}

/** @brief Enters the idle0 mode.
 * This function configures the system to enter the IDLE0 mode, where the CPU is stopped
 * and the low-speed internal RC oscillator (LIRC) remains active.
 */
void Enter_Idle0_Mode(void)
{
    // Enter IDLE0 mode (Low-speed LIRC operation, CPU stopped)
    _scc = SCC_IDLE0_MODE;
    _halt();  // Execute HALT instruction to enter idle0 mode
}

/** @brief Enters the idle1 mode.
 * This function configures the system to enter the IDLE1 mode, where the CPU is stopped
 * and both high-speed and low-speed oscillators remain active.
 */
void Enter_Idle1_Mode(void)
{
    // Enter IDLE1 mode (High-speed HIRC and Low-speed LIRC both active, CPU stopped)
    _scc = SCC_IDLE1_MODE;
    _halt();  // Execute HALT instruction to enter idle1 mode
}

/** @brief Enters the fast mode.
 * This function configures the system to enter the FAST mode, where the CPU runs at full speed 
 * using the high-speed oscillator (HIRC).
 */
void Enter_Fast_Mode(void)
{
    // Enter FAST mode (HIRC active, full speed operation)
    _scc = SCC_FAST_MODE;
}

/** @brief Enables the Watchdog Timer.
 * This function enables the Watchdog Timer (WDT) with the predefined timeout value.
 */
void Enable_Watchdog(void)
{
    // Enable watchdog timer with configured timeout
    _wdtc |= 0b10101000 | CONFIG_WDT;  // Enable watchdog
}

/** @brief Disables the Watchdog Timer.
 * This function disables the Watchdog Timer (WDT).
 */
void Disable_Watchdog(void)
{
    // Disable watchdog timer
    _wdtc &= ~0b10101000;  // Disable watchdog
}
