/*
 * SPI.h
 *
 *  Created on: Dec 3, 2021
 *      Author: mahmoud
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#define SS 4
#define MOSI 5
#define MISO 6
#define CLK 7

#define SPI_DDR  DDRB
#define SPI_PORT PORTB

#define Slave_Enable()  (SPI_PORT &=~ (1<<SS))
#define Slave_Disable() (SPI_PORT |=  (1<<SS))

void SPI_INIT(char state);
unsigned char SPI_TxRx(unsigned char data);

#endif /* SPI_H_ */
