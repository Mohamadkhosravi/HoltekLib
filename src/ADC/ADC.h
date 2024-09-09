/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** 
 * @file ADC.h
 * @brief Header file for ADC configuration and operations.
 * 
 * This file contains macros and function prototypes for initializing 
 * and reading from the ADC channels on the BA45F5240 microcontroller.
 * 
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#ifndef ADC_H_
#define ADC_H_

#include "BA45F5240.h"



// Common ADC configuration macros
#define Disable 0
#define Enable  1
// ADC Resolution Settings
#define RESOLUTION_12BIT 0
#define RESOLUTION_8BIT  1

#define ADC_RESOLUTION  RESOLUTION_12BIT

// Macros to enable and disable the ADC
#define ADC_ON   _adcen = 1; 
#define ADC_OFF  _adcen = 0; 

// Enable or Disable specific ADC channels
#define USE_ADC_AN0      Enable
#define USE_ADC_AN1      Enable
#define USE_ADC_AN2      Enable
#define USE_ADC_AN3      Enable
#define USE_ADC_VBGREF   Enable
#define USE_ADC_OPA0O    Enable
#define USE_ADC_OPA1O    Enable
#define USE_ADC_LINEV    Enable


// Define ADC channels based on usage
#if USE_ADC_AN0
#define AN0 0x00
#define READ_ADC_SET_AN0 { _sadc1 = 0b00000011; _sadc0 = 0b00000000; }
#endif

#if USE_ADC_AN1
#define AN1 0x01
#define READ_ADC_SET_AN1 { _sadc1 = 0b00001000; _sadc0 = 0b00000001; }
#endif

#if USE_ADC_AN2
#define AN2 0x02
#define READ_ADC_SET_AN2 { _sadc1 = 0b00000011; _sadc0 = 0b00000010; }
#endif

#if USE_ADC_AN3
#define AN3 0x03
#define READ_ADC_SET_AN3 { _sadc1 = 0b00000011; _sadc0 = 0b00000011; }
#endif

#if USE_ADC_VBGREF
#define VBGREF 0x04
#define READ_ADC_SET_VBGREF { _sadc1 = 0b00101011; _sadc0 = 0b00010111; }
#endif

#if USE_ADC_OPA0O
#define OPA0O 0x05
#define READ_ADC_SET_OPA0O { _sadc1 = 0b01000011; _sadc0 = 0b00000111; }
#endif

#if USE_ADC_OPA1O
#define OPA1O 0x06
#define READ_ADC_SET_OPA1O { _sadc1 = 0b01101011; _sadc0 = 0b00000111; }
#endif

#if USE_ADC_LINEV
#define LINEV 0x07
#define READ_ADC_SET_LINEV { _sadc1 = 0b10000011; _sadc0 = 0b00000111; }
#endif


// Function prototypes
void ADCInit();
unsigned int ReadADC(unsigned char channel);

#endif // ADC_H_
