/*
 * Ultrasonic.h
 *
 *  Created on: Nov 26, 2021
 *      Author: mahmoud
 */

#ifndef HAL_ULTRASONIC_ULTRASONIC_H_
#define HAL_ULTRASONIC_ULTRASONIC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>


/*
 Fos = 16Mhz
 Ftimer = 16/8 = 2 MHZ prescaling
 Ttimer = 1/2m = 0.5 * 10^-6

 distance = 17150 * timevalue * Ttimer(0.5 * 10^-6) =


 */

double Ultrasonic_Read(void);


#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
