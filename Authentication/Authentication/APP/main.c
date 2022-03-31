/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: mahmoud
 */

#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"
#include "../HAL/LCD/LCD.h"
//#include "../MCAL/SPI/SPI.h"
//#include "../HAL/Ultrasonic/Ultrasonic.h"
#include "../HAL/KEYPAD/KEYPAD.h"
//#include "../HAL/USART/USART.h"
#include "../MCAL/I2C/I2C.h"
#include "../HAL/EEPROM/E2PROM.h"
#include "../HAL/ServoMotor/Servo.h"
#include "../HAL/StepperMotor/Stepper.h"
#include "../HAL/FAN/FAN.h"

#include <string.h>
#include <stdlib.h>

void Open_Gate();
void Close_Gate();
void Alarm();
void Read_Temp();
void check_gate();

float celsius;
char string[50];

int main() {
	// Initializations
	DIO_INIT();
	LCD_INIT();
	TWI_Init();
	Servo_Init();
	ADC_INIT();

	// EEPROM + I2C Variables
	u8 password_addresses[4] = { 0x00, 0x01, 0x02, 0x03 };
	u8 pasword_Bytes[4] = { 0x01, 0x00, 0x00, 0x05 };
	// to be transmitted only once
//	EEPROM_Write(pasword_Bytes[0], password_addresses[0]);
//	_delay_ms(500); // delay until cycle completes
//	EEPROM_Write(pasword_Bytes[1], password_addresses[1]);
//	_delay_ms(500); // delay until cycle completes
//	EEPROM_Write(pasword_Bytes[2], password_addresses[2]);
//	_delay_ms(500); // delay until cycle completes
//	EEPROM_Write(pasword_Bytes[3], password_addresses[3]);
//	_delay_ms(500); // delay until cycle completes
//	LCD_STRING("Password Stored!");
//	_delay_ms(1000);
	char R;

	// keypad variables
	char password_entered[4];

	u8 pass = 0;
	u8 wrong_pass = 0;

	while (1) {
		while (!pass) {
			LCD_CMD(0x01);
			LCD_STRING("Enter Password!!");
			_delay_ms(1000);
			// Entering the password
			u8 entries_counter = 0;
			u8 typed = 0;
			while (entries_counter != 4) {
				char x = GetKey();
				if (x != 9) {
					if (!typed) {
						LCD_CMD(0x01);
						typed = 1;
					}
					password_entered[entries_counter] = x;
					LCD_CHAR('*');
					entries_counter++;
				}
			}
			// checking the password
			LCD_CMD(0x01);
			LCD_STRING("Waiting...");
			_delay_ms(1000);
			entries_counter = 0;
			while (entries_counter != 4) {
				EEPROM_Read(password_addresses[entries_counter], &R);
				char buffer[1];
				itoa(R, buffer, 10);
				_delay_ms(1000);
				// convert char to string
				char key_1[1] = "\0";
				char key_2[1] = "\0";
				key_1[0] = buffer[0];
				key_2[0] = password_entered[entries_counter];
				if (key_1[0] == key_2[0]) {
					//do nothing
				} else {
					LCD_CMD(0x01);
					LCD_STRING("Wrong Password");
					wrong_pass++;
					if (wrong_pass >= 3) {
						Alarm();
						wrong_pass = 0;
					}
					_delay_ms(1000);
					break;
				}
				entries_counter++;
			}
			if (entries_counter == 4) {
				pass = 1;
				LCD_CMD(0x01);
				LCD_STRING("Correct Password");
				Open_Gate();
				FAN_Init();
				_delay_ms(1000);
			}
		}
		if (pass == 1) {
			check_gate();
			Stepper_Angle();
			Read_Temp();
			if ((int) celsius >= 18) {
				FAN_Speed(500);
			} else {
				FAN_Speed(250);
			}
		}
	}
	return 0;
}
void Open_Gate() {
	Servo_Angle(180);
}
void Close_Gate() {
	Servo_Angle(90);
}
void Alarm() {
	for (u8 i = 0; i < 5; i++) {
		PORTD |= (1 << 6) | (1 << 5);
		_delay_ms(1000);
		PORTD &= ~((1 << 6) | (1 << 5));
		_delay_ms(1000);
	}
	PORTD &= ~((1 << 6) | (1 << 5));
}
void Read_Temp() {
	celsius = ADC_READ(4); //read from channel 4
	celsius = (celsius / 4);
	itoa((int) celsius, string, 10); //convert to char
	LCD_SETPOS(2, 0);
	LCD_STRING("Temp=");
	LCD_STRING(string);
}
void check_gate() {
	if (Read_Channel(DIO_CHANNEL_B0) == STD_LOW) {
		Open_Gate();
	} else {
		Close_Gate();
	}
}
