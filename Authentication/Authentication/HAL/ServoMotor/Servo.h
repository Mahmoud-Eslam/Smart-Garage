/*
 * Servo.h
 *
 *  Created on: Mar 15, 2022
 *      Author: Elbekoo
 */

#ifndef HAL_SERVOMOTOR_SERVO_H_
#define HAL_SERVOMOTOR_SERVO_H_

#include <avr/io.h>

#define MinAngle 0
#define MaxAngle 180
#define MinCount 250
#define MaxCount 500

void Servo_Init();
void Servo_Angle(long angle);

#endif /* HAL_SERVOMOTOR_SERVO_H_ */
