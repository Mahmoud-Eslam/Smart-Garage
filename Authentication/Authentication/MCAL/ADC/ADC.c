/*
 * ADC.c
 *
 *  Created on: ??�/??�/????
 *      Author: mahmoud
 */


#include "ADC.h"

void ADC_INIT(){
	ADMUX = (1<<REFS0) | (1<<REFS1);// INTERNAL VREF
	ADCSRA = (1<<ADEN) | (1<<ADPS1) |(1<<ADPS2);// ENABLE THE 64 PRE SCALER
}
u16 ADC_READ(u8 MODEID){
	u16 TEMP = 0;
	ADMUX = (ADMUX & 0xE0) | (MODEID & 0x1F); // SET ADC MODE
	ADCSRA |= (1<<ADSC); //START CONVERSION
	while(!(ADCSRA & (1<<ADIF)));// POLLING ON THE FLAG
	ADCSRA |= (1<<ADIF); //CLEAR FLAG
	TEMP = ADCL;
	TEMP |= ADCH << 8;
	return TEMP;
}

