/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** 
 * @file NTC.h
 * @brief Header file for NTC temperature calculations.
 * 
 * This file contains macros, function prototypes, and configurations for 
 * calculating temperature using an NTC thermistor with an ADC.
 * 
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#ifndef NTC_H
#define NTC_H

#include "BA45F5240.h"

// Uncomment the following line if you want to use the standard math library for logarithm calculations
 #define _USE_MATH_H

#ifdef _USE_MATH_H
    #include <math.h>
    #define LOG_FUNCTION log
#else
    double custom_log(double x); /**< Function prototype for custom logarithm function */
    #define LOG_FUNCTION custom_log
#endif

#define ADC_12bit  4095
#define ADC_10bit  1023
#define ADC_8bit   255

// Select ADC resolution
#define ADCNumerOfbits  ADC_12bit
// Uncomment the appropriate line based on your NTC configuration
#define NTC_IS_PULLDOWN  /**< NTC is in pull-down configuration (NTC to GND, resistor to VCC) */
//#define NTC_IS_PULLUP   /**< NTC is in pull-up configuration (NTC to VCC, resistor to GND) */

#ifdef NTC_IS_PULLDOWN
    #define RES_PULLDOWN_WITH_NTC 10  /**< Resistor value (kOhm) when using pull-down configuration with NTC */
    #define RES_CONNECTED_TO_NTC    RES_PULLDOWN_WITH_NTC

    /**
     * @brief Calculate the resistance of the NTC in a pull-down configuration.
     * 
     * @param VNTC The voltage across the NTC.
     * @param VCC The supply voltage.
     * @param ResPullDown The pull-down resistor value.
     * @return The calculated resistance of the NTC.
     */
    #define CALCULATE_RNTC(VNTC, VCC, ResPullDown) (((VNTC) / ((VCC) - (VNTC))) * (ResPullDown))
    
#endif

#ifdef NTC_IS_PULLUP
    #define RES_PULLUP_WITH_NTC 10  /**< Resistor value (kOhm) when using pull-up configuration with NTC */
    #define RES_CONNECTED_TO_NTC    RES_PULLUP_WITH_NTC

    /**
     * @brief Calculate the resistance of the NTC in a pull-up configuration.
     * 
     * @param VNTC The voltage across the NTC.
     * @param VCC The supply voltage.
     * @param ResPullUp The pull-up resistor value.
     * @return The calculated resistance of the NTC.
     */
    #define CALCULATE_RNTC(VNTC, VCC, ResPullUp) (((VCC) - (VNTC)) * (ResPullUp) / (VNTC))

#endif

/**
 * @brief Calculate the voltage across the NTC in a pull-down or pull-up configuration.
 * 
 * @param ADC_NTC The ADC value corresponding to the voltage across the NTC.
 * @param ADCNumerOfbits The resolution of the ADC.
 * @param VCC The supply voltage.
 * @return The calculated voltage across the NTC.
 */
#define CALCULATE_VNTC(ADC_NTC, ADCNumerOfbits, VCC) ((VCC) * (ADC_NTC) / ((1 << (ADCNumerOfbits)) - 1))

/**
 * @brief Steinhart-Hart coefficients for temperature calculation.
 */	
/*
/*  3 point from your ntc in different temperatures , you can use from
  https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
  T1=-30^C   R1=154882kR
  T2=25^C    R2=10000KR
  T3=80^C    R3=1228KR 

*/



#define A  0.001277368    /**< Steinhart-Hart coefficient A */
#define B  0.000208223    /**< Steinhart-Hart coefficient B */
#define C  0.0000002032989 /**< Steinhart-Hart coefficient C */

/**
 * @brief Calculate the temperature in Celsius from an ADC value and VDD voltage.
 * 
 * This function calculates the temperature based on the resistance of the NTC and
 * the provided Steinhart-Hart coefficients.
 * 
 * @param ADCValue The ADC value corresponding to the voltage across the NTC.
 * @param VDD The supply voltage.
 * @return The calculated temperature in Celsius.
 */
float temperature(unsigned int ADCValue, float VDD);

#endif /* NTC_H */
