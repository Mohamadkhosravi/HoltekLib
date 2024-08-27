/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** @file UART.h
 * @brief Header file for UART (Universal Asynchronous Receiver-Transmitter) functions.
 * This file contains the definitions for configuring UART settings,
 * data transfer parameters, and function prototypes.
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#ifndef UART_H
#define UART_H

/** @brief Enable or disable macros. */
#define ENABLE           	  1
#define DISABLE               0

/** @brief UART modes for transmitter and receiver. */
#define TRANSMITTER      ENABLE
#define RECEIVER         ENABLE

//============================================
// Assuming a clock frequency 
//============================================
#define F_CPU            4000000 /**< Clock frequency in Hz. */

//============================================
// Calculate and set the baud rate
// UBRGH: Baud Rate speed selection
//============================================
#define LOW_SPEED             0
#define HIGH_SPEED            1
#define SPEED_BAUDRATE   LOW_SPEED /**< Current baud rate setting. */

#if SPEED_BAUDRATE
	#define CONSTANT_NUMBER 16.00 /**< Constant for low speed calculation. */
#else
	#define CONSTANT_NUMBER 64.00 /**< Constant for high speed calculation. */
#endif

//============================================
// UBNO: Number of data transfer bits selection
//============================================
#define _8_BIT_DATA_TRANSFER  0
#define _9_BIT_DATA_TRANSFER  1
#define DATA_TRANSFER    _8_BIT_DATA_TRANSFER /**< Data transfer bit configuration. */

//============================================
// UPREN: Parity function enable control
// UPRT: Parity type selection bit
//============================================
#define PARITY           DISABLE /**< Enable or disable parity checking. */

#define EVEN_PARITY           0 /**< Even parity type. */
#define ODD_PARITY            1 /**< Odd parity type. */
#define TYPE_OF_PARITY   ODD_PARITY /**< Selected parity type. */

//============================================
// USTOPS: Number of Stop bits selection
//============================================
#define ONE_STOP_BIT          0 /**< One stop bit. */
#define TWO_STOP_BIT          1 /**< Two stop bits. */
#define STOP_BIT         ONE_STOP_BIT /**< Selected stop bit configuration. */

//============================================
// UTXBRK: Transmit break character
/*
0: No break character is transmitted
1: Break characters transmit
*/
//============================================

#define CHECK_RECEIVER_ERROR DISABLE /**< Enable or disable receiver error checking. */

//============================================
// UART error codes
//============================================
#define UART_ERROR          -1 /**< UART generic error code. */
#define UART_FRAMING_ERROR  -2 /**< Framing error code. */
#define UART_PARITY_ERROR   -3 /**< Parity error code. */
#define UART_OVERRUN_ERROR  -4 /**< Overrun error code. */

//============================================          
#define TRANSMITTER_IDLE_INTERRUPT DISABLE /**< Enable or disable transmitter idle interrupt. */
#define TRANSMITTER_EMPTY_INTERRUPT DISABLE /**< Enable or disable transmitter empty interrupt. */
#define RECEIVER_INTERRUPT ENABLE /**< Enable or disable receiver interrupt. */

/** @brief Receives a single character via UART.
 * @return The received character.
 *
 * This function checks if data is available and then receives a single character via UART.
 * It is a non-blocking function, which means it does not wait if no data is available.
 */
char UART_Receive(void);

/** @brief Initializes the UART with a specified baud rate.
 * @param baudrate The baud rate for UART communication.
 *
 * This function configures the UART pins, sets the UART mode, and calculates the
 * baud rate register values based on the provided baud rate.
 */
void UART_Init(unsigned int baudrate);

/** @brief Transmits a single character via UART.
 * @param data The character to be transmitted.
 *
 * This function waits until the transmit buffer is empty and then sends the data
 * through the UART.
 */
void UART_Transmit(char data);

/** @brief Receives a single character via UART in a non-blocking manner.
 * @return The received character if available; otherwise, an error code.
 *
 * This function checks if data is available and then receives a single character via UART.
 * It is non-blocking and suitable for use in interrupt service routines.
 */
char UART_ReceiveNonBlocking(void);

/** @brief Enables UART interrupts for receiving and transmitting.
 *
 * This function enables the receiver interrupt and the transmitter interrupts.
 */
void UART_EnableInterrupts(void);

/** @brief Disables all UART interrupts.
 *
 * This function disables all UART interrupts, including receiver and transmitter interrupts.
 */
void UART_DisableInterrupts(void);

#endif // UART_H
