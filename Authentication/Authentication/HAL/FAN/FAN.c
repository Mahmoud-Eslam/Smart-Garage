/*
 * FAN.c
 *
 *  Created on: Mar 16, 2022
 *      Author: Elbekoo
 */

#include "FAN.h"

void FAN_Init() {
	DDRD |= (1 << 4);
	DDRC |= (1 << 6) | (1 << 7);
	TCCR1A = (1 << WGM11) | (1 << COM1B1); //mode 14 FPWM, Non Inverting
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11); //N = 64
	OCR1B = 1000;
	PORTC |= (1 << 6);
	PORTC &= ~(1 << 7);
	ICR1 = 500;
}
void FAN_Speed(int speed) {
	OCR1B = speed;
}
