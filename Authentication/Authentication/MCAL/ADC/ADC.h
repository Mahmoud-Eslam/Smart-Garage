/*
 * ADC.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mahmoud
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include<avr/io.h>
#include "../../LIB/STD_TYPES.h"


void ADC_INIT();
u16 ADC_READ(u8 MODEID);

#endif /* MCAL_ADC_ADC_H_ */
