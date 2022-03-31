/*
 * DIO.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: mahmoud
 */

#include "DIO.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_HW.h"

void Write_Channel(DIO_CHANNEL_TYPES Channel_ID, STD_LEVEL_TYPES LEVEL) {
	DIO_GROUPE_TYPES Portx = Channel_ID / 8;
	DIO_CHANNEL_TYPES PIN_NO = Channel_ID % 8;
	switch (Portx) {
	case GROUPA:
		if (LEVEL == STD_HIGH) {
			SET_BIT(PORTA_REG, PIN_NO);
		} else {
			CLR_BIT(PORTA_REG, PIN_NO);
		}
		break;
	case GROUPB:
		if (LEVEL == STD_HIGH) {
			SET_BIT(PORTB_REG, PIN_NO);
		} else {
			CLR_BIT(PORTB_REG, PIN_NO);
		}
		break;
	case GROUPC:
		if (LEVEL == STD_HIGH) {
			SET_BIT(PORTC_REG, PIN_NO);
		} else {
			CLR_BIT(PORTC_REG, PIN_NO);
		}
		break;
	case GROUPD:
		if (LEVEL == STD_HIGH) {
			SET_BIT(PORTD_REG, PIN_NO);
		} else {
			CLR_BIT(PORTD_REG, PIN_NO);
		}
		break;
	default:
		break;
	}

}
STD_LEVEL_TYPES Read_Channel(DIO_CHANNEL_TYPES Channel_ID) {
	STD_LEVEL_TYPES PIN_TYPE = STD_LOW;
	DIO_GROUPE_TYPES Portx = Channel_ID / 8;
	DIO_CHANNEL_TYPES PIN_NO = Channel_ID % 8;
	switch (Portx) {
	case GROUPA:
		PIN_TYPE = GET_BIT(PINA_REG, PIN_NO);
		break;
	case GROUPB:
		PIN_TYPE = GET_BIT(PINB_REG, PIN_NO);
		break;
	case GROUPC:
		PIN_TYPE = GET_BIT(PINC_REG, PIN_NO);
		break;
	case GROUPD:
		PIN_TYPE = GET_BIT(PIND_REG, PIN_NO);
		break;
	default:
		break;
	}
	return PIN_TYPE;
}
void Write_PORT(DIO_GROUPE_TYPES PORT_ID, u8 Data) {
	switch (PORT_ID) {
	case GROUPA:
		PORTA_REG = Data;
		break;
	case GROUPB:
		PORTB_REG = Data;
		break;
	case GROUPC:
		PORTC_REG = Data;
		break;
	case GROUPD:
		PORTD_REG = Data;
		break;
	}
}
u8 Read_PORT(DIO_GROUPE_TYPES PORT_ID) {
	u8 Data = 0;
	switch (PORT_ID) {
	case GROUPA:
		Data = PINA_REG;
		break;
	case GROUPB:
		Data = PINB_REG;
		break;
	case GROUPC:
		Data = PINC_REG;
		break;
	case GROUPD:
		Data = PIND_REG;
		break;
	}
	return Data;
}
