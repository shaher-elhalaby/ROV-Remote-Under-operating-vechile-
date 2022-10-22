/*
 * Assist.c
 *
 * Created: 11/6/2020 7:34:39 PM
 *  Author: SHAHER
 */ 
#include "MAIN.h"
#include <stdlib.h>

void sysInit(void)
{
	ADC_Init( Free_Running, AVCC, ADC_No_Int, ADC_Pre2);
	USART_Init(9600, _8Bit_9Bit, USART_Async, USART_INT_Disable, PARITY_Disable, STOP1);
	PinDirection(GPIOB,INPUTPULLUP,FWD);
	PinDirection(GPIOB,INPUTPULLUP,LFT);
	PinDirection(GPIOB,INPUTPULLUP,RHT);
	PinDirection(GPIOB,INPUTPULLUP,BCK);
	PortDirection(GPIOC,OUTPUT);
}
void sysUpdate(void)
{
	uint8 data;
	data = ((~(GPIOB->pin))&0X0F)/*+'a'*/;
	USART_SendByte((char)data);

	data = (uint8)(analog_Read(_PA0_)/204.0)+(uint8)'A';
	USART_SendByte(data);

	data = (uint8)(analog_Read(_PA1_)/204.0)+(uint8)'G';
	USART_SendByte(data);

	data = (uint8)(analog_Read(_PA2_)/204.0)+(uint8)'M';
	USART_SendByte(data);

	data = (uint8)(analog_Read(_PA3_)/204.0)+(uint8)'S';
	USART_SendByte(data);
	
	_delay_ms(20);
}