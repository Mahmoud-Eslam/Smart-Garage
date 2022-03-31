/*
 * Stepper.c
 *
 *  Created on: Mar 16, 2022
 *      Author: Elbekoo
 */

#include "Stepper.h"

void Stepper_Angle() {
	/* Rotate Stepper Motor clockwise with Half step sequence */
	for (int i = 0; i < 150; i++) {
		Stepper(0, 3);
	}
	PORTA = 0x09; /* Last step to initial position */
	_delay_ms(3);
	_delay_ms(1000);

	/* Rotate Stepper Motor Anticlockwise with Full step sequence */
	for (int i = 0; i < 150; i++) {
		Stepper(1, 3);
	}
	PORTA = 0x09;
	_delay_ms(3);
	_delay_ms(1000);
}
void Stepper(unsigned char Direction, int period) {
	switch (Direction) {
	case 0:
		PORTA = 0x09;
		_delay_ms(period);
		PORTA = 0x08;
		_delay_ms(period);
		PORTA = 0x0C;
		_delay_ms(period);
		PORTA = 0x04;
		_delay_ms(period);
		PORTA = 0x06;
		_delay_ms(period);
		PORTA = 0x02;
		_delay_ms(period);
		PORTA = 0x03;
		_delay_ms(period);
		PORTA = 0x01;
		_delay_ms(period);
		break;
	case 1:
		PORTA = 0x01;
		_delay_ms(period);
		PORTA = 0x03;
		_delay_ms(period);
		PORTA = 0x02;
		_delay_ms(period);
		PORTA = 0x06;
		_delay_ms(period);
		PORTA = 0x04;
		_delay_ms(period);
		PORTA = 0x0C;
		_delay_ms(period);
		PORTA = 0x08;
		_delay_ms(period);
		PORTA = 0x09;
		_delay_ms(period);
		break;
	}
}
