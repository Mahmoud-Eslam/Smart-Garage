/*
 * E2PROM.c
 *
 *  Created on: Dec 10, 2021
 *      Author: mahmoud
 */

#include "E2PROM.h"

void EEPROM_Write(char data, char address) {
	TWI_Start();
	TWI_Write(0xA8); //slave address is 1010.100 and a 0 in the 8th bit to indicate Writting.
	TWI_Write(address);
	TWI_Write(data);
	TWI_Stop();
}
void EEPROM_Read(char address, char* ptr) // the function arguments are an address in the EEPROM to read from and a pointer to a memory place in the MCU to store the read data in
{
	TWI_Start();
	TWI_Write(0xA8); // 0b1010 1000 as address write
	TWI_Write(address);
	TWI_Start();
	TWI_Write(0xA9); // 0b1010 1001 as address read
	TWI_Read_Nack(ptr);
	TWI_Stop();
}
