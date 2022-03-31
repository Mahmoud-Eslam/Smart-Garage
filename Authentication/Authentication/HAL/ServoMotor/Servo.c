/*
 * Servo.c
 *
 *  Created on: Mar 15, 2022
 *      Author: Elbekoo
 */

#include "Servo.h"

void Servo_Init() {
	DDRD |= (1 << 7);
	TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS22);
	OCR2 = 255;
	Servo_Angle(90);
}
void Servo_Angle(long angle) {
	OCR2 =
			(((angle - MinAngle) * (MaxCount - MinCount))
					/ (MaxAngle - MinAngle)) + MinCount - 1;
}
