/*
 * I2C.h
 *
 *  Created on: Dec 4, 2021
 *      Author: mahmoud
 */

#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "../../LIB/STD_TYPES.h"

#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum) // get bit macro used to get the value of a certain bit.

void TWI_Init (void);

void TWI_Start (void);

void TWI_Stop (void);

void TWI_Write (char data);

void TWI_Read_Nack (char* ptr);


#endif /* I2C_H_ */
