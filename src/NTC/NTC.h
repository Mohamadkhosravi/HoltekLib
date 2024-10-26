
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

// ADC resolution definitions
#define ADC_12bit  4094.0  // Maximum ADC value for 12-bit resolution
#define ADC_10bit  1023.0   // Maximum ADC value for 10-bit resolution
#define ADC_8bit   255.0    // Maximum ADC value for 8-bit resolution
#define ADCNumerOfBits  ADC_12bit // Define the number of bits used for ADC

// NTC power control macros
#define NTC_POWER_ON   _pa7 = 1  /**< Turns NTC ON by setting PA7 to HIGH */
#define NTC_POWER_OFF  _pa7 = 0  /**< Turns NTC OFF by setting PA7 to LOW */

// Temperature calculation method selection
#define USE_STENINHART    0
#define USE_LOOKUP_TABLE  1
#define TEMPERATURE_CALCULATION_METHOD     USE_STENINHART 

// Logarithm function selection for Steinhart-Hart calculations
#define USE_MATH_H   0
#define USE_CUSTOM_LOG_FUNCTION  1
#define CALCULATE_STENINHART_LOGARITM_LIBRARY   USE_MATH_H

// NTC configuration definitions
#define NTC_IS_PULLDOWN  0 /**< NTC is in pull-down configuration (NTC to GND, resistor to VCC) */
#define NTC_IS_PULLUP    1 /**< NTC is in pull-up configuration (NTC to VCC, resistor to GND) */
#define NTC_TOPOLOGY  NTC_IS_PULLDOWN 

// Resistor value in kO used in the NTC circuit
#define NTC_FIXED_RESISTOR  10  /**< Fixed resistor value in kO **/


#if TEMPERATURE_CALCULATION_METHOD == USE_LOOKUP_TABLE
	float GetTemperatureFromLookup(unsigned long resistance);
#elif TEMPERATURE_CALCULATION_METHOD == USE_STENINHART

	#if CALCULATE_STENINHART_LOGARITM_LIBRARY == USE_MATH_H
		#include <math.h>
		#define LOG_FUNCTION log
/*	#elif CALCULATE_STENINHART_LOGARITM_LIBRARY == USE_CUSTOM_LOG_FUNCTION*/
	#else
		float custom_log(float x); /**< Function prototype for custom logarithm function **/
		#define LOG_FUNCTION custom_log
	#endif

    /*  @brief Steinhart-Hart coefficients for temperature calculation.
    /*  3 point from your ntc in different temperatures , you can use from
     https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
    /*  Coefficients used:
    * T1 = -30°C, R1 = 154882 kO
    * T2 = 25°C, R2 = 10000 kO
    * T3 = 80°C, R3 = 1228 kO
    */
    #define A 0.001277368779     /**< Steinhart-Hart coefficient A */
    #define B 0.0002082232310    /**< Steinhart-Hart coefficient B */
    #define C 0.0000002032989311 /**< Steinhart-Hart coefficient C */
    float GetTemperatureFromSteinhart(float resistance);
		
#endif

#if NTC_TOPOLOGY ==  NTC_IS_PULLDOWN 
    #define RES_PULLDOWN_WITH_NTC   NTC_FIXED_RESISTOR  /**< Resistor value (kOhm) when using pull-down configuration with NTC */
    #define RES_CONNECTED_TO_NTC    RES_PULLDOWN_WITH_NTC

    /**
     * @brief Calculate the resistance of the NTC in a pull-down configuration.
     * 
     * @param VNTC The voltage across the NTC.
     * @param VCC The supply voltage.
     * @param ResPullDown The pull-down resistor value.
     * @return The calculated resistance of the NTC.
     */
  
    #define CALCULATE_RNTC(VNTC, VCC, ResPullDown) (((VNTC) / (VCC - VNTC))*ResPullDown)
   
#elif  NTC_TOPOLOGY ==  NTC_IS_PULLUP
    #define RES_PULLUP_WITH_NTC     NTC_FIXED_RESISTOR  /**< Resistor value (kOhm) when using pull-up configuration with NTC */
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
#define CALCULATE_VNTC(ADC_NTC, ADCNumerOfbits, VCC)((ADC_NTC/ADCNumerOfbits)*VCC)
 


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
