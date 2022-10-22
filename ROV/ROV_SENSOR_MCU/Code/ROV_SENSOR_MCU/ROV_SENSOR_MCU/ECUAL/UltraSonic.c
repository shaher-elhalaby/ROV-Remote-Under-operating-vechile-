/*
 * UltraSonic.c
 *
 * Created: 11/9/2020 6:34:00 PM
 *  Author: SHAHER
 */ 
#include "UltraSonic.h"
#include <avr/interrupt.h>

vuint8 sensor_working=0;
vuint8 rising_edge=0;
vuint32 timer_counter=0;
vuint16 distance;

void UltraSonicInit(UltraSonicInfo *info)
{
	PinDirection(info->Uport,OUTPUT,info->Trig);
	EX_INT_Enable(info->Echo,info->INTmODE);
	info->Read = 0;
}
void UltrasonicReading(UltraSonicInfo *info)
{	
	Timer1_Init(T1_Normal, T1_Noraml_NO_OC1A, T1_Noraml_NO_OC1B, T1_FCPU8);
	INT_Enable();
	PinWrite(info->Uport,info->Trig,HIGH);
	_delay_us(10);
	PinWrite(info->Uport,info->Trig,LOW);
	sensor_working=0;
	rising_edge=0;
	while(!sensor_working);
	INT_Disable();
	Timer1_Init(T1_Normal, T1_Noraml_NO_OC1A, T1_Noraml_NO_OC1B, T1_OFF);
	info->Read = (uint8)((float)distance/116);
}

ISR(INT0_vect)
{
	if (rising_edge==0)
	{
		TCNT1 = 0;
		rising_edge=1;
	}
	else if (rising_edge==1)
	{
		distance = TCNT1;
		sensor_working = 1;
	}
}

ISR(INT1_vect)
{
	if (rising_edge==0)
	{
		TCNT1 = 0;
		rising_edge=1;
	}
	else if (rising_edge==1)
	{
		distance = TCNT1;
		sensor_working = 1;
	}
}
