/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** @file UART.c
 * @brief Implementation of UART (Universal Asynchronous Receiver-Transmitter) functions.
 * This file provides the definitions for initializing UART, transmitting and receiving data,
 * and enabling/disabling UART interrupts.
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#include "UART.h"
#include <BA45F5240.h>

/** @brief Initializes the UART with a specified baud rate.
 * @param baudrate The baud rate for UART communication.
 *
 * This function configures the UART pins, sets the UART mode, and calculates the
 * baud rate register values based on the provided baud rate.
 */
void UART_Init(unsigned int baudrate) {
    _umd = 1; // UMD: UART mode selection bit, 1: UART mode
    _ubrgh = SPEED_BAUDRATE; // Set baud rate speed
    unsigned int ubrr = (F_CPU / (CONSTANT_NUMBER * baudrate)) - 1.0; // Calculate baud rate register value
    _ubrg = ubrr & 0xFF; // Set baud rate register
    _uren = 1; // Enable UART (UREN)
    _ubno = DATA_TRANSFER; // Set data transfer bit selection
    _upren = PARITY; // Set parity enable/disable
    _uprt = TYPE_OF_PARITY; // Set type of parity (odd/even)
    _ustops = STOP_BIT; // Set number of stop bits
    _utxen = TRANSMITTER; // Enable transmitter
    _urxen = RECEIVER; // Enable receiver
    _utiie = TRANSMITTER_IDLE_INTERRUPT; // Enable/disable transmitter idle interrupt
    _uteie = TRANSMITTER_EMPTY_INTERRUPT; // Enable/disable transmitter empty interrupt
    _urie = RECEIVER_INTERRUPT; // Enable/disable receiver interrupt
}

/** @brief Transmits a single character via UART.
 * @param data The character to be transmitted.
 *
 * This function waits until the transmit buffer is empty and then sends the data
 * through the UART.
 */
void UART_Transmit(char data) {
    // Wait for empty transmit buffer
    while (!(_utxif)); // Wait until UTXIF is set
    _utxr_rxr = data; // Put data into buffer, sends the data
}

/** @brief Receives a single character via UART.
 * @return The received character, or an error code in case of an error.
 *
 * This function waits until data is received and checks for errors such as
 * parity, overrun, or framing errors before returning the received data.
 */
char UART_Receive(void) {
    _acc = 0; // Clear accumulator
    // Wait for data to be received
    while (!((_urxif) && (_utidle))); // Wait until URXIF and UTIDLE are set

    _acc = _utxr_rxr; // Get received data from buffer
    _urxif = 0; // Clear the receive flag (URXIF)

#if CHECK_RECEIVER_ERROR
    // Check for parity error
    if (_uperr) {
        _uperr = 0; // Clear parity error flag
        return UART_PARITY_ERROR; // Return parity error code
    }
    // Check for overrun error
    if (_uoerr) {
        _uoerr = 0; // Clear overrun error flag
        return UART_OVERRUN_ERROR; // Return overrun error code
    }
    // Check for framing error
    if (_uferr) {
        _uferr = 0; // Clear framing error flag
        return UART_FRAMING_ERROR; // Return framing error code
    }
#endif

    return _acc; // Return received data
}

/** @brief Receives a single character via UART in a non-blocking manner.
 * @return The received character if available; otherwise, an error code.
 *
 * This function checks if data is available and then receives a single character via UART.
 * It is non-blocking and suitable for use in interrupt service routines.
 */
char UART_ReceiveNonBlocking(void) {
    _acc = 0; // Clear accumulator
    if (_urxif) { // Check if data has been received
        _acc = _utxr_rxr; // Get received data from buffer
    }

#if CHECK_RECEIVER_ERROR
    // Check for parity error
    if (_uperr) {
        _uperr = 0; // Clear parity error flag
        return UART_PARITY_ERROR; // Return parity error code
    }
    // Check for overrun error
    if (_uoerr) {
        _uoerr = 0; // Clear overrun error flag
        return UART_OVERRUN_ERROR; // Return overrun error code
    }
    // Check for framing error
    if (_uferr) {
        _uferr = 0; // Clear framing error flag
        return UART_FRAMING_ERROR; // Return framing error code
    }
#endif

    return _acc; // Return received data or 0 if no data
}

/** @brief Enables UART interrupts for receiving and transmitting.
 *
 * This function enables the receiver interrupt and the transmitter interrupts.
 */
void UART_EnableInterrupts(void) {
    _uucr2 |= _urie; // Enable receiver interrupt
    // Note: Transmitter interrupts are not enabled in this function
}

/** @brief Disables all UART interrupts.
 *
 * This function disables all UART interrupts, including receiver and transmitter interrupts.
 */
void UART_DisableInterrupts(void) {
    _uucr2 &= ~(_urie | _utiie | _uteie); // Disable all UART interrupts
}
