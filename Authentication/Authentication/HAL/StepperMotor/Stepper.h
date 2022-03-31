/*
 * Stepper.h
 *
 *  Created on: Mar 16, 2022
 *      Author: Elbekoo
 */

#ifndef HAL_STEPPERMOTOR_STEPPER_H_
#define HAL_STEPPERMOTOR_STEPPER_H_

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL
void Stepper(unsigned char Direction, int period);
void Stepper_Angle();

#endif /* HAL_STEPPERMOTOR_STEPPER_H_ */
