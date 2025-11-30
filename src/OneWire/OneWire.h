#ifndef _ONE_WIRE_H_ 
#define _ONE_WIRE_H_


/* Includes-------------------------------------------------------------------------------------------------*/

#include <stdint.h>


/* Exported functions---------------------------------------------------------------------------------------*/

#define pin_data        _pa3
#define pin_mode        _pac3

#define pin_out    pin_mode=0
#define pin_in     pin_mode=1 

#define pin_high   pin_data=1;
#define pin_low    pin_data=0;

void delay_four_micro(unsigned long int number_of_seconds);
bool initiate(void);
bool readbit(void);
void write_one(void);
void write_zero(void);
void OneWire_write_byte(uint8_t Tdata);
uint8_t OneWire_read_byte(void);

#endif