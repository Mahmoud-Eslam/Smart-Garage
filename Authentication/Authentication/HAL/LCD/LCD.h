/*
 * LCD.h
 *
 *  Created on: ??�/??�/????
 *      Author: mahmoud
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "../../MCAL/DIO/DIO.h"
#include <util/delay.h>
#define F_CPU 8000000UL


#define LCD_RS DIO_CHANNEL_B1
#define LCD_RW DIO_CHANNEL_B2
#define LCD_E DIO_CHANNEL_B3


#define LCD_DataPort GROUPB

void LCD_INIT(void);
void LCD_CMD(u8 CMD);
void LCD_CHAR(s8 DATA);
void LCD_STRING(s8 * DATA);
void LCD_SETPOS(u8 LINE, u8 POS);
void LCD_Custome_Char(u8 loc, s8 * msg);





#endif /* HAL_LCD_LCD_H_ */
