/*
 * DIO_CFG.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: mahmoud
 */

#include "DIO_CFG.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_HW.h"

void DIO_INIT() {
	DIO_CHANNEL_TYPES count;
	DIO_GROUPE_TYPES Portx;
	DIO_CHANNEL_TYPES Channelx;
	for (count = DIO_CHANNEL_A0; count < PIN_COUNT; count++) {
		Portx = count / 8;
		Channelx = count % 8;
		switch (Portx) {
		case GROUPA:
			if (PIN_CFG[count].PIN_DIR == OUTPUT) {
				SET_BIT(DDRA_REG, Channelx);
			} else {
				CLR_BIT(DDRA_REG, Channelx);
			}
			break;
		case GROUPB:
			if (PIN_CFG[count].PIN_DIR == OUTPUT) {
				SET_BIT(DDRB_REG, Channelx);
			} else {
				CLR_BIT(DDRB_REG, Channelx);
			}
			break;
		case GROUPC:
			if (PIN_CFG[count].PIN_DIR == OUTPUT) {
				SET_BIT(DDRC_REG, Channelx);
			} else {
				CLR_BIT(DDRC_REG, Channelx);
			}
			break;
		case GROUPD:
			if (PIN_CFG[count].PIN_DIR == OUTPUT) {
				SET_BIT(DDRD_REG, Channelx);
			} else {
				CLR_BIT(DDRD_REG, Channelx);
			}
			break;
		default:
			break;
		}
	}

}
