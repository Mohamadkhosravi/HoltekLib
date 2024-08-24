/*
 * Licensed under the Apache License, Version 2.0.
 * You may not use this file except in compliance with the License.
 * Obtain a copy at http://www.apache.org/licenses/LICENSE-2.0.
 * Distributed on an "AS IS" basis, without warranties or conditions.
 */

/** @file Interrupt.c
 * @brief Implementation of Interrupt Service Routines (ISRs) and interrupt management functions.
 * This file provides the definitions for initializing, enabling, and disabling interrupts,
 * as well as the ISR implementations for various interrupt sources.
 * Author: Mohamad Khosravi  https://github.com/Mohamadkhosravi
 * Date: 2024
 */

#include <Interrupt.h>

/** @brief Initializes the interrupts.
 * This function enables the global interrupt and configures individual interrupts
 * based on predefined settings. It sets up each interrupt based on whether it's enabled or disabled.
 */
void IntrruptInit(void)
{
    GLOBAL_INTERRUPT = Enable;

    #if EXTERNAL_PIN0_ISR
        _int0e = EXTERNAL_PIN0_ISR;
    #endif

    #if EXTERNAL_PIN1_ISR
        _int1e = EXTERNAL_PIN1_ISR;
    #endif

    #if USIM_ISR
        _usime = USIM_ISR;
    #endif

    #if LVD_ISR
        _lve = LVD_ISR;
    #endif

    #if ADC_ISR
        _ade = ADC_ISR;
    #endif

    #if EEPROM_ISR
        _dee = EEPROM_ISR;
    #endif

    #if PTM_COMPAIR_P_ISR
        _ptmpe = PTM_COMPAIR_P_ISR;
    #endif

    #if PTM_COMPAIR_A_ISR
        _ptmae = PTM_COMPAIR_A_ISR;
    #endif

    #if STM_COMPAIR_P_ISR
        _stmpe = STM_COMPAIR_P_ISR;
    #endif

    #if STM_COMPAIR_A_ISR
        _stmae = STM_COMPAIR_A_ISR;
    #endif

    #if BASE_TIMER0_ISR
        _tb0e = BASE_TIMER0_ISR;
    #endif

    #if BASE_TIMER1_ISR
        _tb1e = BASE_TIMER1_ISR;
    #endif

    #if PLT_COMPAIR0_ISR
        _pltc0e = PLT_COMPAIR0_ISR;
    #endif

    #if PLT_COMPAIR1_ISR
        _pltc1e = PLT_COMPAIR1_ISR;
    #endif
}

/** @brief Enables a specific interrupt dynamically.
 * @param interruptAddress The address of the interrupt to be enabled.
 */
void EnableInterrupt(char interruptAddress)
{
    switch (interruptAddress)
    {
        #if EXTERNAL_PIN0_ISR
            case EXTERNAL_PIN0_ISR_ADDRESS:
                _int0e = InterruptEnable;
                break;
        #endif

        #if EXTERNAL_PIN1_ISR
            case EXTERNAL_PIN1_ISR_ADDRESS:
                _int1e = InterruptEnable;
                break;
        #endif

        #if USIM_ISR
            case USIM_ISR_ADDRESS:
                _usime = InterruptEnable;
                break;
        #endif

        #if LVD_ISR
            case LVD_ISR_ADDRESS:
                _lve = InterruptEnable;
                break;
        #endif

        #if ADC_ISR
            case ADC_ISR_ADDRESS:
                _ade = InterruptEnable;
                break;
        #endif

        #if EEPROM_ISR
            case EEPROM_ISR_ADDRESS:
                _dee = InterruptEnable;
                break;
        #endif

        #if PTM_COMPAIR_P_ISR
            case PTM_COMPAIR_P_ISR_ADDRESS:
                _ptmpe = InterruptEnable;
                break;
        #endif

        #if PTM_COMPAIR_A_ISR
            case PTM_COMPAIR_A_ISR_ADDRESS:
                _ptmae = InterruptEnable;
                break;
        #endif

        #if STM_COMPAIR_P_ISR
            case STM_COMPAIR_P_ISR_ADDRESS:
                _stmpe = InterruptEnable;
                break;
        #endif

        #if STM_COMPAIR_A_ISR
            case STM_COMPAIR_A_ISR_ADDRESS:
                _stmae = InterruptEnable;
                break;
        #endif

        #if BASE_TIMER0_ISR
            case BASE_TIMER0_ISR_ADDRESS:
                _tb0e = InterruptEnable;
                break;
        #endif

        #if BASE_TIMER1_ISR
            case BASE_TIMER1_ISR_ADDRESS:
                _tb1e = InterruptEnable;
                break;
        #endif

        #if PLT_COMPAIR0_ISR
            case PLT_COMPAIR0_ISR_ADDRESS:
                _pltc0e = InterruptEnable;
                break;
        #endif

        #if PLT_COMPAIR1_ISR
            case PLT_COMPAIR1_ISR_ADDRESS:
                _pltc1e = InterruptEnable;
                break;
        #endif

        default:
            // Handle invalid interrupt type
            break;
    }
}

/** @brief Disables a specific interrupt dynamically.
 * @param interruptAddress The address of the interrupt to be disabled.
 */
void DisableInterrupt(char interruptAddress)
{
    switch (interruptAddress)
    {
        #if EXTERNAL_PIN0_ISR
            case EXTERNAL_PIN0_ISR_ADDRESS:
                _int0e = InterruptDisable;
                break;
        #endif

        #if EXTERNAL_PIN1_ISR
            case EXTERNAL_PIN1_ISR_ADDRESS:
                _int1e = InterruptDisable;
                break;
        #endif

        #if USIM_ISR
            case USIM_ISR_ADDRESS:
                _usime = InterruptDisable;
                break;
        #endif

        #if LVD_ISR
            case LVD_ISR_ADDRESS:
                _lve = InterruptDisable;
                break;
        #endif

        #if ADC_ISR
            case ADC_ISR_ADDRESS:
                _ade = InterruptDisable;
                break;
        #endif

        #if EEPROM_ISR
            case EEPROM_ISR_ADDRESS:
                _dee = InterruptDisable;
                break;
        #endif

        #if PTM_COMPAIR_P_ISR
            case PTM_COMPAIR_P_ISR_ADDRESS:
                _ptmpe = InterruptDisable;
                break;
        #endif

        #if PTM_COMPAIR_A_ISR
            case PTM_COMPAIR_A_ISR_ADDRESS:
                _ptmae = InterruptDisable;
                break;
        #endif

        #if STM_COMPAIR_P_ISR
            case STM_COMPAIR_P_ISR_ADDRESS:
                _stmpe = InterruptDisable;
                break;
        #endif

        #if STM_COMPAIR_A_ISR
            case STM_COMPAIR_A_ISR_ADDRESS:
                _stmae = InterruptDisable;
                break;
        #endif

        #if BASE_TIMER0_ISR
            case BASE_TIMER0_ISR_ADDRESS:
                _tb0e = InterruptDisable;
                break;
        #endif

        #if BASE_TIMER1_ISR
            case BASE_TIMER1_ISR_ADDRESS:
                _tb1e = InterruptDisable;
                break;
        #endif

        #if PLT_COMPAIR0_ISR
            case PLT_COMPAIR0_ISR_ADDRESS:
                _pltc0e = InterruptDisable;
                break;
        #endif

        #if PLT_COMPAIR1_ISR
            case PLT_COMPAIR1_ISR_ADDRESS:
                _pltc1e = InterruptDisable;
                break;
        #endif

        default:
            // Handle invalid interrupt type
            break;
    }
}

/** @brief External Pin 0 Interrupt Service Routine.
 * This function handles the interrupt from external pin 0.
 * It is executed when an interrupt is triggered by external pin 0.
 */
#if EXTERNAL_PIN0_ISR
void __attribute__((interrupt(EXTERNAL_PIN0_ISR_ADDRESS))) ExternalPin0ISR(void)
{
    // Here goes the code for External Pin 0 ISR
}
#endif

/** @brief External Pin 1 Interrupt Service Routine.
 * This function handles the interrupt from external pin 1.
 * It is executed when an interrupt is triggered by external pin 1.
 */
#if EXTERNAL_PIN1_ISR
void __attribute__((interrupt(EXTERNAL_PIN1_ISR_ADDRESS))) ExternalPin1ISR(void)
{
    // Here goes the code for External Pin 1 ISR
}
#endif

/** @brief Universal Serial Interface Interrupt Service Routine.
 * This function handles the interrupt from Universal Serial Interface (USIM).
 * It is executed when an interrupt is triggered by the USIM.
 */
#if USIM_ISR
void __attribute__((interrupt(USIM_ISR_ADDRESS))) UniversalSerialInterfaceISR(void)
{
    // Here goes the code for Universal Serial Interface ISR
}
#endif

/** @brief Low Voltage Detect Interrupt Service Routine.
 * This function handles the interrupt from Low Voltage Detector (LVD).
 * It is executed when an interrupt is triggered by the LVD.
 */
#if LVD_ISR
void __attribute__((interrupt(LVD_ISR_ADDRESS))) LowVoltageDetectISR(void)
{
    // Here goes the code for Low Voltage Detect ISR
}
#endif

/** @brief EEPROM Interrupt Service Routine.
 * This function handles the interrupt from EEPROM.
 * It is executed when an interrupt is triggered by the EEPROM.
 */
#if EEPROM_ISR
void __attribute__((interrupt(EEPROM_ISR_ADDRESS))) EEPROMISR(void)
{
    // Here goes the code for EEPROM ISR
}
#endif

/** @brief PTM Comparator P Interrupt Service Routine.
 * This function handles the interrupt from PTM Comparator P.
 * It is executed when an interrupt is triggered by PTM Comparator P.
 */
#if PTM_COMPAIR_P_ISR
void __attribute__((interrupt(PTM_COMPAIR_P_ISR_ADDRESS))) PTMCompairPISR(void)
{
    // Here goes the code for PTM Comparator P ISR
}
#endif

/** @brief PTM Comparator A Interrupt Service Routine.
 * This function handles the interrupt from PTM Comparator A.
 * It is executed when an interrupt is triggered by PTM Comparator A.
 */
#if PTM_COMPAIR_A_ISR
void __attribute__((interrupt(PTM_COMPAIR_A_ISR_ADDRESS))) PTMCompairAISR(void)
{
    // Here goes the code for PTM Comparator A ISR
}
#endif

/** @brief STM Comparator P Interrupt Service Routine.
 * This function handles the interrupt from STM Comparator P.
 * It is executed when an interrupt is triggered by STM Comparator P.
 */
#if STM_COMPAIR_P_ISR
void __attribute__((interrupt(STM_COMPAIR_P_ISR_ADDRESS))) STMCompairPISR(void)
{
    // Here goes the code for STM Comparator P ISR
}
#endif

/** @brief STM Comparator A Interrupt Service Routine.
 * This function handles the interrupt from STM Comparator A.
 * It is executed when an interrupt is triggered by STM Comparator A.
 */
#if STM_COMPAIR_A_ISR
void __attribute__((interrupt(STM_COMPAIR_A_ISR_ADDRESS))) STMCompairAISR(void)
{
    // Here goes the code for STM Comparator A ISR
}
#endif

/** @brief Base Timer 0 Interrupt Service Routine.
 * This function handles the interrupt from Base Timer 0.
 * It is executed when an interrupt is triggered by Base Timer 0.
 */
#if BASE_TIMER0_ISR
void __attribute__((interrupt(BASE_TIMER0_ISR_ADDRESS))) BaseTimer0ISR(void)
{
    // Here goes the code for Base Timer 0 ISR
}
#endif

/** @brief Base Timer 1 Interrupt Service Routine.
 * This function handles the interrupt from Base Timer 1.
 * It is executed when an interrupt is triggered by Base Timer 1.
 */
#if BASE_TIMER1_ISR
void __attribute__((interrupt(BASE_TIMER1_ISR_ADDRESS))) BaseTimer1ISR(void)
{
    // Here goes the code for Base Timer 1 ISR
}
#endif

/** @brief PLT Comparator 1 Interrupt Service Routine.
 * This function handles the interrupt from PLT Comparator 1.
 * It is executed when an interrupt is triggered by PLT Comparator 1.
 */
#if PLT_COMPAIR1_ISR
void __attribute__((interrupt(PLT_COMPAIR1_ISR_ADDRESS))) PLT1CompairISR(void)
{
    // Here goes the code for PLT Comparator 1 ISR
}
#endif

/** @brief PLT Comparator 0 Interrupt Service Routine.
 * This function handles the interrupt from PLT Comparator 0.
 * It is executed when an interrupt is triggered by PLT Comparator 0.
 */
#if PLT_COMPAIR0_ISR
void __attribute__((interrupt(PLT_COMPAIR0_ISR_ADDRESS))) PLT0CompairISR(void)
{
    // Here goes the code for PLT Comparator 0 ISR
}
#endif
