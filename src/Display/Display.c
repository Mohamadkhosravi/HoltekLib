/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/**
 * @file Display.c
 * @brief Optimized source file for 7-segment display control with loading animation.
 *
 * This file implements functions to control a 7-segment display with minimum memory
 * usage and high speed. It includes a loading animation using the dot segment.
 *
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#include "Display.h"

/**
 * @brief Displays a digit on the 7-segment display without using an array.
 * @param number The digit (0-9) to display.
 */
void segmentNumbers(unsigned char number) {
    switch (number) {
        case 0: SEGA = SEGB = SEGC = SEGD = SEGE = SEGF = 0; SEGG = 1; break;
        case 1: SEGB = SEGC = 0; SEGA = SEGD = SEGE = SEGF = SEGG = 1; break;
        case 2: SEGA = SEGB = SEGD = SEGE = SEGG = 0; SEGC = SEGF = 1; break;
        case 3: SEGA = SEGB = SEGC = SEGD = SEGG = 0; SEGE = SEGF = 1; break;
        case 4: SEGB = SEGC = SEGF = SEGG = 0; SEGA = SEGD = SEGE = 1; break;
        case 5: SEGA = SEGC = SEGD = SEGF = SEGG = 0; SEGB = SEGE = 1; break;
        case 6: SEGA = SEGC = SEGD = SEGE = SEGF = SEGG = 0; SEGB = 1; break;
        case 7: SEGA = SEGB = SEGC = 0; SEGD = SEGE = SEGF = SEGG = 1; break;
        case 8: SEGA = SEGB = SEGC = SEGD = SEGE = SEGF = SEGG = 0; break;
        case 9: SEGA = SEGB = SEGC = SEGD = SEGF = SEGG = 0; SEGE = 1; break;
    }
}

/**
 * @brief Displays a character on the 7-segment display without using an array.
 * @param character The character to display.
 */
void segmentCharacters(unsigned char character) {
    switch (character) {
        case 'A': SEGA = SEGB = SEGC = SEGE = SEGF = SEGG = 0; SEGD = 1; break;
        case 'b': SEGA = SEGB = 1; SEGC = SEGD = SEGE = SEGF = SEGG = 0; break;
        case 'L': SEGA = SEGB = SEGC = SEGG = SEGF = 0; SEGD = 1; break;
        case 'N': SEGA = SEGB = SEGE = SEGF = 0; SEGD = SEGC = SEGG = 1; break;
        case 'o': SEGA = SEGB = SEGF = 0; SEGC = SEGD = SEGG = 1; break;
        case 'O': SEGA = SEGB = SEGC = SEGD = SEGG = 0; SEGE = SEGF = 1; break;
        case 'E': SEGA = SEGB = SEGC = SEGG = SEGF = 0; SEGD = 1; break;
        case 'r': SEGA = SEGF = SEGG = 1; SEGB = SEGC = SEGD = SEGE = 0; break;
        case 'S': SEGA = SEGB = SEGC = SEGD = SEGG = 0; SEGE = SEGF = 1; break;
        case 'P': SEGA = SEGB = SEGC = SEGF = 0; SEGD = SEGG = 1; break;
    }
}

/**
 * @brief Displays a number and character across 4 digits of the 7-segment display.
 * @param number The number to display (e.g., 1234).
 * @param character A character to display on the first digit.
 * @param clock Determines the active digit.
 */
void Display(int number, unsigned char character, char clock) {
    switch (clock) {
        case 0:
            if (character != '0') {
                segmentCharacters(character);
            } else {
                segmentNumbers((number / 1000) % 10);
            }
            SELECT_SEGMENT_1;
            break;
        case 1:
            segmentNumbers((number / 100) % 10);
            SELECT_SEGMENT_2;
            break;
        case 2:
            segmentNumbers((number / 10) % 10);
            SELECT_SEGMENT_3;
            break;
        case 3:
            segmentNumbers(number % 10);
            SELECT_SEGMENT_4;
            break;
    }
}

/**
 * @brief Displays a sequence of characters across the 4 digits of the 7-segment display.
 * @param stringOfCharacter The string to display (up to 4 characters).
 * @param clock Determines the active digit.
 */
void DisplayCharacters(unsigned char *stringOfCharacter, char clock) {
    switch (clock) {
        case 0:
            segmentCharacters(stringOfCharacter[0]);
            SELECT_SEGMENT_1;
            break;    
        case 1:
            segmentCharacters(stringOfCharacter[1]);
            SELECT_SEGMENT_2;
            break;
        case 2:
            segmentCharacters(stringOfCharacter[2]);
            SELECT_SEGMENT_3;
            break;    
        case 3:
            segmentCharacters(stringOfCharacter[3]);
            SELECT_SEGMENT_4;
            break;    
    }    
}

/**
 * @brief Displays a loading animation using the dot (.) on the 7-segment display.
 * 
 * This function creates a rotating effect using the dot segment on each of the
 * four digits of the 7-segment display.
 *
 * @param step The current step of the loading animation (0-3).
 */
void displayLoading(unsigned char step) {
    switch (step) {
        case 0:
        case 4:
            SELECT_SEGMENT_1;
            break;      
        case 1:
        case 5:
            SELECT_SEGMENT_2;
            break;
        case 2:
        case 6:
            SELECT_SEGMENT_3;
            break;  
        case 3:
        case 7:
            SELECT_SEGMENT_4;
            break;
    }
}

#if START_LOADING
/**
 * @brief Start-up loading animation sequence on the 7-segment display.
 * 
 * This function handles a loading animation shown on the 7-segment display.
 * The animation rotates across the segments of the display during a delay period.
 */
void startLoading(void)
{
    static unsigned int DelayCounter = START_DELAY; // Set delay for the loading animation
    static unsigned int Counter = 0;
    unsigned i =8;
    // Start-up loading sequence
    do {
        --DelayCounter;  // Decrement delay counter
        Counter++;       // Increment animation counter
	
        // Display loading sequence on the 7-segment display
        for (i = 8; i > 0; i--) {
            displayLoading(Counter % 8);  // Cycle through the 8 possible steps
        }

        if (Counter > 7) {
            Counter = 0;  // Reset counter after completing the loading cycle
        }

    } while (DelayCounter); // Continue until the delay counter reaches zero

    // Reset counter after loading animation
    DelayCounter = 0;
    Counter = 0; // Reset the animation counter
}
#endif
