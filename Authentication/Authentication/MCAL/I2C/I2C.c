/*
 * I2C.c
 *
 *  Created on: Dec 4, 2021
 *      Author: mahmoud
 */
#include "I2C.h"

void TWI_Init (void)
{
       TWSR=0; //Clear the status register
       TWBR=0x03; //ADJUST THE BIT RATE
       TWCR|=(1<<TWEN); // set the enable
}
void TWI_Start (void)
{
       TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
       while (get_bit(TWCR,TWINT)==0)
       {
       }
}
void TWI_Stop (void)
{
       TWCR=(1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
}
void TWI_Write (char data)
{
       TWDR=data;
       TWCR= (1<<TWINT)|(1<<TWEN);
       while (get_bit(TWCR,TWINT)==0)
       {
       }
}
void TWI_Read_Nack (char* ptr) // The function argument is a pointer to a memory place in the MCU to store the received data in
{
       TWCR=(1<<TWINT)|(1<<TWEN);

       while (get_bit(TWCR,TWINT)==0)
       {

       }
       *ptr=TWDR;
}
