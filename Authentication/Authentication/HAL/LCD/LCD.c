/*
 * LCD.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: mahmoud
 */

#include "LCD.h"

void LCD_INIT(void) {
	Write_Channel(LCD_RW, STD_LOW);
	Write_Channel(LCD_E, STD_HIGH);
	_delay_ms(20);
	LCD_CMD(0x33);
	_delay_us(100);
	LCD_CMD(0x32);
	LCD_CMD(0x28); // Set Function 4-bits, 2Lines, 5x8 display
	LCD_CMD(0x06); // Entry Mode I/D , SHIFT
	LCD_CMD(0x0C); // Display ON & Cursor off
	LCD_CMD(0x01); // clear LCD
}
void LCD_CMD(u8 CMD) {
	Write_Channel(LCD_RS, STD_LOW);

	u8 PORT_VAL = Read_PORT(LCD_DataPort);
	PORT_VAL = (PORT_VAL & 0x0F) | (CMD & 0xF0);
	Write_PORT(LCD_DataPort, PORT_VAL);
	Write_Channel(LCD_E, STD_LOW);
	_delay_us(100);
	Write_Channel(LCD_E, STD_HIGH);

	_delay_ms(5);

	PORT_VAL = Read_PORT(LCD_DataPort);
	PORT_VAL = (PORT_VAL & 0x0F) | (CMD << 4);
	Write_PORT(LCD_DataPort, PORT_VAL);
	Write_Channel(LCD_E, STD_LOW);
	_delay_us(100);
	Write_Channel(LCD_E, STD_HIGH);

	_delay_ms(2);
}
void LCD_CHAR(s8 DATA) {
	Write_Channel(LCD_RS, STD_HIGH);

	u8 PORT_VAL = Read_PORT(LCD_DataPort);
	PORT_VAL = (PORT_VAL & 0x0F) | (DATA & 0xF0);
	Write_PORT(LCD_DataPort, PORT_VAL);
	Write_Channel(LCD_E, STD_LOW);
	_delay_us(100);
	Write_Channel(LCD_E, STD_HIGH);

	_delay_ms(5);

	PORT_VAL = Read_PORT(LCD_DataPort);
	PORT_VAL = (PORT_VAL & 0x0F) | (DATA << 4);
	Write_PORT(LCD_DataPort, PORT_VAL);
	Write_Channel(LCD_E, STD_LOW);
	_delay_us(100);
	Write_Channel(LCD_E, STD_HIGH);
	_delay_ms(2);
}
void LCD_STRING(s8 * DATA) {
	u8 i = 0;
	while (DATA[i] != '\0') {
		LCD_CHAR(DATA[i]);
		i++;
	}
}
void LCD_SETPOS(u8 LINE, u8 POS) {
	switch (LINE) {
	case 1:
		LCD_CMD(0x80 | (POS & 0x0F));
		break;
	case 2:
		LCD_CMD(0xC0 | (POS & 0x0F));
		break;
	}
}
void LCD_Custome_Char(u8 loc, s8 * msg){
	u8 i = 0;
	if(loc < 8){
		LCD_CMD(0x40 + (loc * 8));
		for(i = 0;i<8;i++){
			LCD_CHAR(msg[i]);
		}
	}
}
