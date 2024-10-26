/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** 
 * @file NTC.c
 * @brief Implementation file for NTC temperature calculations.
 * 
 * This file provides the implementation for calculating temperature using an NTC thermistor 
 * based on the ADC readings and the Steinhart-Hart equation.
 * 
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#include "NTC.h"


#if TEMPERATURE_CALCULATION_METHOD == USE_LOOKUP_TABLE
   // Lookup tables for temperature and resistance values
	static const float temperatureLookupTable[] = {
	    -50.0, -40.0, -30.0, -20.0, -10.0, -5.0, 0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0
	};
	static const  float resistanceLookupTable[] = {
	    1500.0, 820.0, 470.0, 270.0, 150.0, 100.0, 75.0, 50.0, 35.0, 25.0, 18.0, 10.0, 8.0, 6.0, 4.7, 3.6, 3.0, 2.2, 1.8
	};
	#define TABLE_SIZE 19// Size of the lookup tables
	  /**
     * @brief Get temperature from resistance using a lookup table.
     * 
     * This function interpolates between known resistance values to find the 
     * corresponding temperature.
     * 
     * @param resistance The resistance of the NTC thermistor.
     * @return The interpolated temperature in Celsius or -999.0 if out of range.
     */	
	float GetTemperatureFromLookup(unsigned long resistance) {
	    int i;
		// Check for resistance out of bounds
	    if (resistance < 1.8 || resistance > 1500.0) return -999.0;
	    for (i = 0; i < TABLE_SIZE - 1; i++) {
	        if (resistance >= resistanceLookupTable[i + 1] && resistance <= resistanceLookupTable[i]) {
	            float temp1 = temperatureLookupTable[i] , 
	                  temp2 = temperatureLookupTable[i + 1],
	                  resistance1 =resistanceLookupTable[i],
	                  resistance2 =resistanceLookupTable[i + 1];
	            return (temp1 + (resistance - resistance1) * (temp2 - temp1) / (resistance2 - resistance1));
	        }
	    }
	    return -999.0;// Return -999.0 if no match found
	}

#elif TEMPERATURE_CALCULATION_METHOD == USE_STENINHART

	#if CALCULATE_STENINHART_LOGARITM_LIBRARY == USE_MATH_H
	    // If _USE_MATH_H is defined, no additional code is needed since math.h is used.
	#elif CALCULATE_STENINHART_LOGARITM_LIBRARY == USE_CUSTOM_LOG_FUNCTION
		/**
		 * @brief Custom natural logarithm function.
		 * 
		 * This function calculates the natural logarithm of a number using a series expansion.
		 * 
		 * @param x The input value for which the logarithm is to be calculated.
		 * @return The natural logarithm of the input value.
		 */
		float custom_log(float x) {
			int n=0;
		    if (x <= 0) {
		        return -1.0; // Logarithm is not defined for non-positive numbers
		    }
		
		    float epsilon = 1e-10; // A small value for accuracy
		    float result = 0.0;
		    float term = (x - 1) / (x + 1);
		    float term_squared = term * term;
		    float term_squared_power = term_squared;
		    float current_term = term;
		
		    for (n = 1; current_term > epsilon; n++) {
		        result += current_term;
		        current_term = term_squared_power * term;
		        term_squared_power *= term_squared;
		        current_term /= 2 * n + 1;
		    }
		
		    return 2 * result;
		}
	#endif
		/**
		 * @brief Get temperature from resistance using the Steinhart-Hart equation.
		 * 
		 * This function computes the temperature in Kelvin and converts it to Celsius 
		 * using the Steinhart-Hart coefficients.
		 * 
		 * @param resistance The resistance of the NTC thermistor.
		 * @return The calculated temperature in Celsius.
		 */
		float GetTemperatureFromSteinhart(float resistance) {
			
		    float logResistance = LOG_FUNCTION(resistance);
		    float temperatureK = 1.0 / (A + B * logResistance + C * logResistance * logResistance * logResistance);
		    return  (temperatureK - 273.15)/10.0;// Convert Kelvin to Celsius
		   
		}
#endif

/**
 * @brief Calculate the temperature in Celsius from an ADC value and supply voltage (VDD).
 * 
 * This function first calculates the voltage across the NTC thermistor, then
 * computes the resistance and finally calculates the temperature based on the chosen
 * calculation method (lookup table or Steinhart-Hart).
 * 
 * @param ADCValue The ADC value corresponding to the voltage across the NTC.
 * @param VDD The supply voltage.
 * @return The calculated temperature in Celsius.
 */
float temperature(unsigned int ADCValue, float VDD) {
	//if((ADCValue<=0)||(ADCValue>4098))ADCValue=0;
	// Calculate the voltage across the NTC using the provided macros/functions.
	float VNTC = CALCULATE_VNTC(ADCValue, ADCNumerOfBits, VDD);
	
	// Calculate the resistance of the NTC using the provided macros/functions.
	float RNTC = CALCULATE_RNTC(VNTC, VDD, RES_CONNECTED_TO_NTC);
	
	#if TEMPERATURE_CALCULATION_METHOD ==  USE_LOOKUP_TABLE
        return GetTemperatureFromLookup(RNTC);
    #elif TEMPERATURE_CALCULATION_METHOD == USE_STENINHART
    /*	#if CALCULATE_STENINHART_LOGARITM_LIBRARY == USE_MATH_H
     		RNTC=RNTC*1000;
     	#endif*/
/*        RNTC=RNTC*1000;*/
        return GetTemperatureFromSteinhart(RNTC);
    #endif 
   
}
