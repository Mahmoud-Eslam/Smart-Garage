/*
 * Ultrasonic.c
 *
 *  Created on: Nov 26, 2021
 *      Author: mahmoud
 */

#include "Ultrasonic.h"



volatile long OVF_COUNT = 0;

double Ultrasonic_Read(void) {
	sei(); // set global interrupt flag
	TIMSK |= (1<<TOIE1); //Overflow interrupt enable
	TCNT1 = 0; // clear timer
	TCCR1A = 0; // normal mode
	TCCR1B |= (1 << ICES1) | (1 << CS11); // rising edge & prescale 8
	TIFR |= (1 << TOV1); // clear flag
	TIFR |= (1 << ICF1); // CLEAR interrupt

	//Start the trigger
	PORTD |= (1<<2);
	_delay_us(10);
	PORTD &= ~(1<<2);

	while(!(TIFR & (1<<ICF1)));
	TCNT1 = 0; // clear timer
	OVF_COUNT = 0;
	TCCR1B &=~ (1 << ICES1);// rising edge & prescale 8
	TIFR |= (1 << TOV1); // clear flag
	TIFR |= (1 << ICF1); // CLEAR interrupt

	while(!(TIFR & (1<<ICF1)));
	long count = ICR1 + (OVF_COUNT*65535);
	double distance = (double) count * 0.008575;
	return distance;


}
ISR(TIMER1_OVF_vect){
	OVF_COUNT++;
}

