/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** 
 * @file ADC.c
 * @brief Implementation of ADC configuration and reading functions.
 * 
 * This file contains the implementation of functions to initialize the ADC
 * and read analog values from specified channels on the BA45F5240 microcontroller.
 * 
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#include "ADC.h"

/**
 * @brief Initialize the ADC module.
 * 
 * This function initializes the ADC module by setting up the control registers.
 * It prepares the ADC for reading from various channels.
 */
void ADCInit()
{
    // Configure ADC control registers
    _sadc0 = 0b00000111;
    _sadc1 = 0b01101011;
	_adrfs = ADC_RESOLUTION;
    _ade = 0; // Disable analog interrupt initially
}

/**
 * @brief Read analog value from a specified ADC channel.
 * 
 * This function reads the analog value from the specified ADC channel and returns 
 * the digital equivalent.
 * 
 * @param channel The ADC channel to read from (AN0, AN1, AN2, AN3, VBGREF, OPA0O, OPA1O, LINEV).
 * @return The digital value corresponding to the analog input.
 */
unsigned int ReadADC(unsigned char channel)
{
    unsigned int result;
    
 switch(channel)
 {
	#if USE_ADC_AN0
        case AN0:
            READ_ADC_SET_AN0;
            break;
	#endif
	#if USE_ADC_AN1
        case AN1:
            READ_ADC_SET_AN1;
            break;
	#endif
	#if USE_ADC_AN2
        case AN2:
            READ_ADC_SET_AN2;
            break;
	#endif
	#if USE_ADC_AN3
        case AN3:
            READ_ADC_SET_AN3;
            break;
	#endif
	#if USE_ADC_VBGREF
        case VBGREF:
            READ_ADC_SET_VBGREF;
            break;
	#endif
	#if USE_ADC_OPA0O
        case OPA0O:
            READ_ADC_SET_OPA0O;
            break;
	#endif
	#if USE_ADC_OPA1O
        case OPA1O:
            READ_ADC_SET_OPA1O;
            break;
	#endif
	#if USE_ADC_LINEV
        case LINEV:
            READ_ADC_SET_LINEV;
            break;
	#endif
        default:
           return 0; // Invalid channel
           break;
   }
    
    // Start ADC conversion
    ADC_ON;
    GCC_DELAY(12); // Small delay to stabilize the signal
    _start = 0;    // Clear start bit
    _start = 1;    // Set start bit to begin conversion
    _start = 0;    // Clear start bit again
    
    // Wait for conversion to complete
    while (_adbz);
    
    // Disable ADC after conversion
    ADC_OFF;
    
    // Read result based on resolution
    if (_adrfs == 0) {
        result = _sadoh;
        result = (result << 8) | _sadol;
    } else {
        result = (_sadoh & 0x0F); // Only lower 4 bits are valid
        result = (result << 8) | _sadol;
    }

    return result; // Return the digital value
}
