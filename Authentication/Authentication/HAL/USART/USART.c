/*
 * USART.c
 *
 *  Created on: Nov 27, 2021
 *      Author: mahmoud
 */


#include "USART.h"

void UART_INIT(){
	UCSRB |= (1<<TXEN)|(1<<RXEN);//enable reciever and transmitter
	UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);//8 BITS
	UBRRL = MyUBRR;
	UBRRH |= MyUBRR>>8;
}
void UART_TransmitChar(s8 data){
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;
}
s8 UART_Recieve(){
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}
void UART_TransmitString(s8 * data){
	u8 i;
	while(data[i] != '\0'){
		UART_TransmitChar(data[i]);
		i++;
	}
}
