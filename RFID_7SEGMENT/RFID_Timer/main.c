/*
 * main.c
 *
 *  Created on: Jan 21, 2022
 *      Author: Elbekoo
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lcd.h"
#include "utils.h"
#include "spi.h"
#include "mfrc522.h"
#include "Ultrasonic.h"

volatile unsigned long Tmer0_OVF_Count = 0;
volatile unsigned long Seven_Left = 0;
volatile unsigned long Seven_Right = 0;
volatile unsigned long COUNTER = 0;

#define Card1 	2
#define Card2 	3
#define Card3 	4

int main(void) {
	// Ultrasonic
	double distance = 0;
	char str_ultra[20];
	DDRD |= (1 << 3) | (1 << 4);
	DDRD &= ~(1 << 6);
	PORTD |= (1 << 6);
	//LEDs
	PORTD |= (1 << 3);
	PORTD &= ~(1 << 4);

	//RFID
	uint8_t byte;
	uint8_t str[MAX_LEN];
	//indicator
	DDRD |=(1<<7);

	uint8_t person_recognised = 0;
	int not_detected = 1;
	int parked = 0;

	//define cards
	uint8_t Card_1[5] = { 0x84, 0x65, 0xac, 0x8b, 0xc6 };
	uint8_t Card_2[5] = { 0xe1, 0x02, 0xad, 0x8b, 0xc5 };
	uint8_t Card_3[5] = { 0x3e, 0x55, 0xac, 0x8b, 0x4c };

	_delay_ms(50);
	LCDInit(LS_BLINK);
	LCDWriteStringXY(2, 0, "RFID Reader");
	LCDWriteStringXY(5, 1, VERSION_STR);

	//Spi_INIT();
	spi_init();

	//init reader
	mfrc522_init();
	_delay_ms(1500);
	LCDClear();

	//check version of the reader

	byte = mfrc522_read(VersionReg);
	_delay_ms(1000);
	if (byte == 0x92) {
		LCDWriteStringXY(2, 0, "MIFARE RC522v2");
		LCDWriteStringXY(4, 1, "Detected");
	} else if (byte == 0x91 || byte == 0x90) {
		LCDWriteStringXY(2, 0, "MIFARE RC522v1");
		LCDWriteStringXY(4, 1, "Detected");
	} else {
		LCDWriteStringXY(0, 0, "No reader found");
	}

	_delay_ms(1500);
	LCDClear();

	while (1) {
		// Ultrasonic
		if (!not_detected) {
			dtostrf(distance, 2, 2, str_ultra);
			distance = Ultrasonic_Read();
			LCDWriteStringXY(0, 0, "Distance = ");
			LCDWriteStringXY(10, 0, str_ultra);
			if (distance <= 5) {
				// disable Green led and enable Red led
				PORTD |= (1 << 4);
				PORTD &= ~(1 << 3);
				_delay_ms(5000);
				parked = 1;
			}
			if ((!not_detected) && parked) {
				if (distance >= 7) {
					// reset all system
					PORTB &= ~((1 << 1) |(1<<2));
					Tmer0_OVF_Count = 0;
					Seven_Left = 0;
					Seven_Right = 0;
					COUNTER = 0;
					LCDClear();
					not_detected = 1;
					person_recognised = 0;
					parked = 0;
					DDRB |= (1 << 1) | (1 << 2);
					PORTD |= (1 << 3);
					PORTD &= ~(1 << 4);
					TCCR0 = 0;
					TCCR0 = 0;
					TIMSK = 0;
					TCNT0 = 0;
					cli();
				}
			}
		}
		// RFID
		if (not_detected) {
			LCDClear();
			LCDWriteStringXY(1, 0, "Show Your Card");
			byte = mfrc522_request(PICC_REQALL, str);

			if (byte == CARD_FOUND) {
				byte = mfrc522_get_card_serial(str);
				if (byte == CARD_FOUND) {
					PORTD |= (1<<7);
					_delay_ms(500);
					PORTD &=~ (1<<7);
					LCDClear();
					for (byte = 0; byte < 5; byte++) {
						char buffer[20];
						sprintf(buffer, "%x", str[byte]);
						LCDWriteStringXY(2 * byte, 0, buffer);
					}
					_delay_ms(2000);
					person_recognised = 1;
					// check first card
					for (byte = 0; byte < 5; byte++) {
						if (Card_1[byte] != str[byte])
							break;
					}
					if (byte == 5) {
						person_recognised = Card1;
					} else {
						// do nothing
					}
					if (byte != 5) {
						// check second card
						for (byte = 0; byte < 5; byte++) {
							if (Card_2[byte] != str[byte])
								break;
						}
						if (byte == 5) {
							person_recognised = Card2;
						} else {
							// do nothing
						}
					}
					if (byte != 5) {
						// check second card
						for (byte = 0; byte < 5; byte++) {
							if (Card_3[byte] != str[byte])
								break;
						}
						if (byte == 5) {
							person_recognised = Card3;
						}
					}

					switch (person_recognised) {
					case Card1: {
						LCDClear();
						LCDWriteStringXY(3, 1, "Car_1");
						not_detected = 0;
						break;
					}
					case Card2: {
						LCDClear();
						LCDWriteStringXY(3, 1, "Car_2");
						not_detected = 0;
						break;
					}
					case Card3: {
						LCDClear();
						LCDWriteStringXY(3, 1, "Car_3");
						not_detected = 0;
						break;
					}
					default: {
						LCDClear();
						LCDWriteStringXY(0, 1, "Not Recognised !");
						break;
					}
					}
				} else {
					LCDClear();
					LCDWriteStringXY(5, 1, "Error");
				}
				if (not_detected == 0) {
					// 7 segment data pins
					DDRC |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
					DDRB |= (1 << 1) | (1 << 2); //Enable
					PORTB |= (1 << 1);
					// timer 0 configurations
					TCCR0 &= ~((1 << WGM00) | (WGM01));
					TCCR0 |= (1 << CS00) | (1 << CS02); // N = 1024
					TIMSK |= (1 << TOIE0);
					TCNT0 = 0;
					sei();
				}
				_delay_ms(2000);
			}
		}

	}
}
ISR(TIMER0_OVF_vect) {
	Tmer0_OVF_Count++;
	COUNTER++;
	if (COUNTER > 100) {
		COUNTER = 0;
		if (Seven_Left > 9) {
			PORTB ^= ((1 << 1) | (1 << 2));
			return;
		}
		if (Seven_Left == 0) {
			Seven_Right++;
			if (Seven_Right > 9) {
				PORTB &= ~(1 << 1);
				PORTB |= (1 << 2);
				Seven_Left++;
				PORTC = (PORTC & 0x0F) | (Seven_Left << 4);
				return;
			} else {
				PORTC = (PORTC & 0x0F) | (Seven_Right << 4);
			}
		}
		if (Seven_Left > 0) {
			Seven_Left++;
			if (Seven_Left > 9) {
				PORTB |= ((1 << 1) | (1 << 2));
				PORTC = (PORTC & 0x0F) | (9 << 4);
			} else {
				PORTC = (PORTC & 0x0F) | (Seven_Left << 4);
			}
		}
	}
}
