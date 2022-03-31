/*
 * KEYPAD.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: mahmoud
 */

#include "KEYPAD.h"

u8 KeyPadRow[RowSize] = { r0, r1, r2, r3 };
u8 KeyPadCol[ColSize] = { c0, c1, c2, c3 };

u8 KeyPad[RowSize][ColSize] = { { '1', '2', '3', 'A' }, { '4', '5', '6', 'B' },
		{ '7', '8', '9', 'C' }, { '*', '0', '#', 'D' } };

u8 GetKey(void) {
	//Put one to all Portx 0xffff
	for (u8 w = 0; w < RowSize; w++) {
		Write_Channel(KeyPadRow[w], STD_HIGH);
		Write_Channel(KeyPadCol[w], STD_HIGH);
	}
	for (u8 i = 0; i < RowSize; i++) {
		Write_Channel(KeyPadRow[i], STD_LOW);
		for (u8 j = 0; j < ColSize; j++) {
			if (Read_Channel(KeyPadCol[j]) == STD_LOW) {
				while (Read_Channel(KeyPadCol[j]) == STD_LOW);
				return KeyPad[i][j];
			}
		}
		Write_Channel(KeyPadRow[i], STD_HIGH);
	}
	return 9;
}
