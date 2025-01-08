/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */
/**
 * @file Display.h
 * @brief Header file for 7-segment display control, including loading animation.
 * 
 * This header defines the function prototypes and pin mappings used
 * for controlling a 7-segment display, including a loading animation.
 * 
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "GPIO.h"
// Macros for enabling and disabling features 
#define Enable  1
#define Disable 0

#define DISPLAY_2_DIGIT 2
#define DISPLAY_3_DIGIT 3
#define DISPLAY_4_DIGIT 4

#define NUMBER_OF_DIGIT DISPLAY_3_DIGIT

#define COMMON_ANODE   0
#define COMMON_CATHODE 1

//COM_HIGH  1
//COM_LOW   0
//SEG_HIGH COM_LOW
//SEG_LOW  COM_HIGH


// Define pins for the 7-segment display segments
#define COM0 COM_1
#define COM1 COM_2
#define COM2 COM_3
#define COM3 
#define SEGA SEG_A
#define SEGB SEG_B
#define SEGC SEG_C
#define SEGD SEG_D
#define SEGE SEG_E
#define SEGF SEG_F
#define SEGG SEG_G
#define DOT  


 
// Macros for selecting segments (COM lines)
#if NUMBER_OF_DIGIT == DISPLAY_2_DIGIT
#define SEGMENTS_TURN_OFF  COM0 = COM1= 0;
#define SELECT_SEGMENT_1  COM0 = 1; COM1= 0;
#define SELECT_SEGMENT_2  COM1 = 1; COM0 = 0;

#elif NUMBER_OF_DIGIT == DISPLAY_3_DIGIT

#define SEGMENTS_TURN_OFF  COM0 = COM1 =  COM2 = 0;
#define SELECT_SEGMENT_1  COM0 = 1; COM1 = COM2 =  0;
#define SELECT_SEGMENT_2  COM1 = 1; COM0 = COM2 =  0;
#define SELECT_SEGMENT_3  COM2 = 1; COM0 = COM1 =  0;


#else
#define SEGMENTS_TURN_OFF  COM0 = COM1 =  COM2 = COM3= 0;
#define SELECT_SEGMENT_1  COM0 = 1; COM1 = COM2 = COM3 = 0;
#define SELECT_SEGMENT_2  COM1 = 1; COM0 = COM2 = COM3 = 0;
#define SELECT_SEGMENT_3  COM2 = 1; COM0 = COM1 = COM3 = 0;
#define SELECT_SEGMENT_4  COM3 = 1; COM0 = COM1 = COM2 = 0;

#endif



// Macro to enable loading functionality
#define START_LOADING   Disable
#define START_DELAY     500
#define START_BLINK_ON  50
#define START_BLINK_OFF 100

/* @brief Function to display a digit (0-9) on the 7-segment display.
 * @param number The digit to display (0-9).
 */
void segmentNumbers(unsigned char number);

/**
 * @brief Function to display a character (A, b, L, etc.) on the 7-segment display.
 * @param character The character to display.
 */
void segmentCharacters(unsigned char character);

/**
 * @brief Function to display a number and a character across 4 digits of the 7-segment display.
 * @param number The number to display.
 * @param character The character to display.
 * @param clock Determines the active digit.
 */
void Display(int number, unsigned char character, char clock);

/**
 * @brief Function to display a sequence of characters on the 7-segment display.
 * @param stringOfCharacter The string to display (up to 4 characters).
 * @param clock Determines the active digit.
 */
void DisplayCharacters(unsigned char *stringOfCharacter, char clock);

 #if START_LOADING
/**
 * @brief Function to display a loading animation using the dot (.) on the 7-segment display.
 * This function makes use of the dot segment to create a rotating loading effect.
 * 
 * @param step The current step of the loading animation.
 */
void displayLoading(unsigned char step);

/**
 * @brief Function to initiate the start-up loading animation sequence.
 */
void startLoading(void);

#endif

#endif
