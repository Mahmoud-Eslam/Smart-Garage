/*
 * KEYPAD.h
 *
 *  Created on: ??�/??�/????
 *      Author: mahmoud
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

#include "../../MCAL/DIO/DIO.h"

#define RowSize 4
#define ColSize 4

#define r0 DIO_CHANNEL_D0
#define r1 DIO_CHANNEL_D1
#define r2 DIO_CHANNEL_D2
#define r3 DIO_CHANNEL_D3

#define c0 DIO_CHANNEL_C2
#define c1 DIO_CHANNEL_C3
#define c2 DIO_CHANNEL_C4
#define c3 DIO_CHANNEL_C5

u8 GetKey(void);




#endif /* HAL_KEYPAD_H_ */
