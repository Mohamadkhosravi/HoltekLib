/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** @file PTM.c
 * @brief Implementation file for the PTM (Pulse Timer Module) for Holtek MCUs.
 * This file contains the definitions of functions for initializing and using
 * the PTM in embedded applications.
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#include <PTM.h>

/** @brief Initializes the Pulse Timer Module (PTM).
 *
 * This function configures the PTM's clock, mode, output settings, and
 * initializes the necessary registers.
 *
 * @return void
 */
void PTimerInit(void)
{
    _ifs06 = 1; // Clear interrupt flag for PTM
    _ifs07 = 0; // Initialize another interrupt flag
    
    // PTPAU: PTM Counter Pause Control
    // 0: Run, 1: Pause
    _ptpau = 0; // Set PTM counter to run mode

    // Select PTM Counter Clock
    _ptck0 = PTIMER_CLOCK & 1;
    _ptck1 = (PTIMER_CLOCK >> 1) & 1;
    _ptck2 = (PTIMER_CLOCK >> 2) & 1;

    // PTON: PTM Counter On/Off Control
    _pton = PTM_COUNTER; // Turn on PTM counter

    // Set PTM Operating Mode
    _ptm0 = PTM_MODE & 1;
    _ptm1 = (PTM_MODE >> 1) & 1;

    // Set PTM Pin Function
    _ptio0 = PTM_PIN_FUNCTION & 1;
    _ptio1 = (PTM_PIN_FUNCTION >> 1) & 1;

    // PTM Output Control
    _ptoc = PTM_OUTPUT_MODE;

    // Set PTM Output Polarity
    _ptpol = PTM_OUTPUT_POLARITY;

    // Set PTM Capture Trigger Source Selection
    _ptcapts = PTM_CAPTURE_TRIGGER;

    // Set PTM Compare Clear Condition
    _ptcclr = PTM_SELECT_CLEAR_COMPARE_MATCH;

    // Select PTM Counter clear condition in capture input mode only
    #if PTM_MODE == PTM_CAPTURE_INPUT_MODE
        _pttclr0 = PTM_SELECT_CLEAR_CONDITION_IN_CAPTURE_INPUT & 1;
        _pttclr1 = (PTM_SELECT_CLEAR_CONDITION_IN_CAPTURE_INPUT >> 1) & 1;
    #endif

    // Set PTM counter value latch edge flag
    _ptvlf = COUNTER_VALUE_LATCH_EDGE;

    // Set PTM Comparator CCRA Low Byte
    _ptmal = PTM_CCRA_LOW_BYTE_MASK;

    // Set PTM Comparator CCRA High Byte
    _ptmah = PTM_CCRA_HIGH_BYTE_MASK & 3;

    // Set PTM Comparator CCRB Low Byte
    _ptmbl = PTM_CCRB_LOW_BYTE_MASK;

    // Set PTM Comparator CCRB High Byte
    _ptmbh = PTM_CCRB_HIGH_BYTE_MASK & 3;

    // Set PTM Comparator CCRP Low Byte
    _ptmrpl = PTM_CCRP_LOW_BYTE_MASK;

    // Set PTM Comparator CCRP High Byte
    _ptmrph = PTM_CCRP_HIGH_BYTE_MASK & 3;
}

/** @brief Sets the PWM status.
 *
 * This function configures the PWM output state based on the provided status.
 *
 * @param status: The status to set for the PWM (1 for active, 0 for inactive).
 * @return void
 */
void PWMSeter(char status)
{
    if (status == 1)
    {
        // PTM CCRA Low Byte
        _ptmal = 37; // Set low byte value
        // PTM CCRA High Byte Register
        _ptmah = 0b00; // Set high byte value
        
        // PTM CCRP Low Byte Register
        _ptmrpl = 00; // Set low byte for CCRP
        // PTM CCRP High Byte Register
        _ptmrph = 0; // Set high byte for CCRP
        
        // PTPAU: PTM Counter Pause Control
        // 0: Run
        // 1: Pause
        _ptpau = 0; // Run the counter
        
        // PTON: PTM Counter On/Off Control
        // 0: Off
        // 1: On
        _pton = 1; // Turn on the counter
    }
    else if (status == 0)
    {
        _ptpau = 1; // Pause the counter
        _pton = 0; // Turn off the counter
        _ptmrpl = 0; // Clear low byte for CCRP
        _ptmal = 0; // Clear low byte for CCRA
    }
}

/** @brief Reads the current value of the Pulse Timer Module (PTM).
 *
 * This function retrieves the current timer value from the PTM.
 *
 * @return The current timer value as an unsigned integer.
 */
unsigned int readPTimer(void)
{
    // Read PTM Timer Value
    return ((_ptmdl) | (_ptmdh << 8));
}
