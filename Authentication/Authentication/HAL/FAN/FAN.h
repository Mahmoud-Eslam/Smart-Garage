/*
 * FAN.h
 *
 *  Created on: Mar 16, 2022
 *      Author: Elbekoo
 */

#ifndef HAL_FAN_FAN_H_
#define HAL_FAN_FAN_H_

#include <avr/io.h>

void FAN_Init();
void FAN_Speed(int speed);

#endif /* HAL_FAN_FAN_H_ */
