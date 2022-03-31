/*
 * E2PROM.h
 *
 *  Created on: Dec 10, 2021
 *      Author: mahmoud
 */

#ifndef E2PROM_H_
#define E2PROM_H_

#include "../../MCAL/I2C/I2C.h"

void EEPROM_Write (char data, char address);

void EEPROM_Read (char address, char* ptr);

#endif /* E2PROM_H_ */
