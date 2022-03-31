/*
 * DIO.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mahmoud
 */

#ifndef DIO_H_
#define DIO_H_

#include "DIO_TYPES.h"
#include "../../LIB/STD_TYPES.h"

void Write_Channel(DIO_CHANNEL_TYPES Channel_ID,STD_LEVEL_TYPES LEVEL);
void Write_PORT(DIO_GROUPE_TYPES PORT_ID,u8 Data);
u8 Read_PORT(DIO_GROUPE_TYPES PORT_ID);
STD_LEVEL_TYPES Read_Channel(DIO_CHANNEL_TYPES Channel_ID);


#endif /* DIO_H_ */
