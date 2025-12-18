/*
 * Licensed under the Apache License, Version 2.0.
 */

/**
 * @file    OneWire.h
 * @brief   One-Wire protocol driver (Delay-Based + Non-Blocking)
 *
 * @author  Mohamad Khosravi
 * @author  Hamidreza Kalhor
 *
 * @github  https://github.com/Mohamadkhosravi
 * @github  https://github.com/hamiikalhor
 * @date    2024
 */


#include "OneWire.h" 



void delay_four_micro(unsigned long int number_of_seconds)
{	
   unsigned long int j;
   unsigned long int x;
    while(number_of_seconds--){
        for(j=0;j < 1;j++){
          _clrwdt();
        }
        _clrwdt();
    }  
}

bool initiate(void)// sending reset command
{
	bool sensorExist;
	
	pin_out;
	pin_low;
	delay_four_micro(120);
	pin_high;
	
	delay_four_micro(10);
	pin_in;
	sensorExist=!pin_data;
	delay_four_micro(120);
	
	return sensorExist;
}

bool readbit(void)
{
	bool input_bit=0;
	
	pin_out;
	pin_low;
	delay_four_micro(1);
	pin_in;
	delay_four_micro(2);
	input_bit=pin_data;
	
	delay_four_micro(12);
	
	return input_bit;
}

void write_one(void)
{
	pin_out;	
	pin_low;
	delay_four_micro(2);
	pin_high;
	delay_four_micro(15);
}

void write_zero(void)
{
	pin_out;	
	pin_low;
	delay_four_micro(20);
	pin_high;
	delay_four_micro(1);	
	
}

void OneWire_write_byte(uint8_t Tdata)
{
	uint8_t transmitBit=0b00000001;
	
	do
	{	
		 if (Tdata & transmitBit)
          write_one();
         else
          write_zero();
		
		transmitBit <<= 1; 
		
	}while (transmitBit!=0);
}

uint8_t OneWire_read_byte(void)
{
	uint8_t recievedBit=0b00000001;
	uint8_t read_data=0;
	
	do
	{	
		if (1 == readbit())
        read_data |= recievedBit; 
		
		recievedBit <<= 1; 
		
	}while (recievedBit!=0);
  return read_data;
}
	
