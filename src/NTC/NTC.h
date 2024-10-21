/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/**
 * @file NTC.h
 * @brief Header file for NTC temperature calculations using ADC readings.
 * 
 * This file contains macros, function prototypes, and configurations for calculating 
 * temperature using an NTC thermistor with an ADC. It supports both a lookup table 
 * and the Steinhart-Hart equation for temperature calculation.
 * 
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#ifndef NTC_H
#define NTC_H

#include "BA45F5240.h"

// ---------------------------------------------
// User-configurable settings
// ---------------------------------------------

/** 
 * @brief Select ADC resolution.
 * 
 * Choose the resolution of the ADC in your system.
 * Options:
 *  - 4094.0 for 12-bit resolution (default)
 *  - 1023.0 for 10-bit resolution
 *  - 255.0 for 8-bit resolution
 */
#define ADC_RESOLUTION  4094.0  /**< ADC resolution (12-bit by default) */

/** 
 * @brief Select NTC connection type.
 * 
 * Choose whether the NTC thermistor is connected in pull-down or pull-up configuration.
 * Options:
 *  - NTC_IS_PULLDOWN: NTC connected to GND, resistor to VCC (pull-down).
 *  - NTC_IS_PULLUP: NTC connected to VCC, resistor to GND (pull-up).
 */
#define NTC_CONNECTION  NTC_IS_PULLDOWN

/**
 * @brief Resistor value.
 * 
 * Define the value of the fixed resistor in kΩ used in the NTC circuit.
 */
#define NTC_FIXED_RESISTOR  10  /**< Resistor value in kΩ */

/**
 * @brief Use lookup table for temperature calculation.
 * 
 * Uncomment the line below if you want to use a lookup table for calculating temperature
 * instead of using the Steinhart-Hart equation.
 */
//#define USE_LOOKUP_TABLE

/**
 * @brief Use standard math library for logarithm.
 * 
 * Uncomment the line below if you want to use the standard math library for logarithmic calculations.
 */
#define USE_MATH_H

/**
 * @brief Control NTC power using PA7 pin.
 * 
 * Use these macros to turn the NTC circuit ON/OFF using pin PA7.
 */
#define NTC_POWER_ON   _pa7 = 1  /**< Turns NTC ON by setting PA7 to HIGH */
#define NTC_POWER_OFF  _pa7 = 0  /**< Turns NTC OFF by setting PA7 to LOW */

// ---------------------------------------------
// Main calculations and configurations
// ---------------------------------------------

// Use the ADC resolution set by the user
#define ADCNumerOfbits  ADC_RESOLUTION

// Use the NTC connection configuration
#ifdef NTC_CONNECTION
    #if (NTC_CONNECTION == NTC_IS_PULLDOWN)
        #define RES_CONNECTED_TO_NTC  NTC_FIXED_RESISTOR
        #define CALCULATE_RNTC(VNTC, VCC, ResPullDown) (((VNTC) / (VCC - VNTC)) * ResPullDown)
    #elif (NTC_CONNECTION == NTC_IS_PULLUP)
        #define RES_CONNECTED_TO_NTC  NTC_FIXED_RESISTOR
        #define CALCULATE_RNTC(VNTC, VCC, ResPullUp) (((VCC) - (VNTC)) * (ResPullUp) / (VNTC))
    #endif
#endif

/**
 * @brief Calculate the voltage across the NTC.
 * 
 * @param ADC_NTC The ADC value corresponding to the voltage across the NTC.
 * @param ADCNumerOfbits The resolution of the ADC.
 * @param VCC The supply voltage.
 * @return The calculated voltage across the NTC.
 */
#define CALCULATE_VNTC(ADC_NTC, ADCNumerOfbits, VCC)((ADC_NTC / ADCNumerOfbits) * VCC)

// If using lookup table for temperature calculation
#ifdef USE_LOOKUP_TABLE
    /**
     * @brief Get temperature from lookup table based on resistance.
     * 
     * This function calculates the temperature corresponding to a given resistance
     * using a predefined lookup table and linear interpolation.
     * 
     * @param resistance The resistance of the NTC (in kΩ).
     * @return The calculated temperature in Celsius.
     */
    float GetTemperatureFromLookup(unsigned long resistance);
#else
    // If using Steinhart-Hart equation for temperature calculation
    #ifdef USE_MATH_H
        #include <math.h>
        #define LOG_FUNCTION log
    #else
        /**
         * @brief Custom logarithm function.
         * 
         * This function calculates the natural logarithm of a number using a series expansion.
         * It is used if math.h is not available.
         * 
         * @param x The input value for which the logarithm is to be calculated.
         * @return The natural logarithm of the input value.
         */
        double custom_log(double x);
        #define LOG_FUNCTION custom_log
    #endif

    /**
     * @brief Steinhart-Hart coefficients for temperature calculation.
     * 
     * These coefficients are calculated based on 3 points from the NTC's datasheet.
     * Example: 
     * T1 = -30°C, R1 = 154882Ω
     * T2 = 25°C, R2 = 10000Ω
     * T3 = 80°C, R3 = 1228Ω
     */
    #define A 0.001277368779
    #define B 0.0002082232310
    #define C 0.0000002032989311

    /**
     * @brief Get temperature using the Steinhart-Hart equation.
     * 
     * This function calculates the temperature based on the resistance of the NTC
     * using the Steinhart-Hart equation.
     * 
     * @param resistance The resistance of the NTC (in Ω).
     * @return The calculated temperature in Celsius.
     */
    float GetTemperatureFromSteinhart(float resistance);
#endif

/**
 * @brief Calculate the temperature in Celsius from an ADC value and VDD voltage.
 * 
 * This function calculates the temperature based on the resistance of the NTC and
 * either the Steinhart-Hart equation or the lookup table, depending on the configuration.
 * 
 * @param ADCValue The ADC value corresponding to the voltage across the NTC.
 * @param VDD The supply voltage.
 * @return The calculated temperature in Celsius.
 */
float temperature(unsigned int ADCValue, float VDD);

#endif /* NTC_H */
