/*
 * DHT11.c
 *
 * Created: 11/15/2020 5:54:41 PM
 *  Author: SHAHER
 */ 
#include "DHT11.h"

void DHT_Start(DHT_Info *info)
{
	PinDirection(info->DHT,OUTPUT,info->DHT_Pin);
	PinWrite	(info->DHT,info->DHT_Pin,LOW);       //sending start
	_delay_ms(18);
}
void DHT_Response(DHT_Info *info)
{
	vuint8 *pin = &(info->DHT->pin);
	uint8 pinNum = info->DHT_Pin; 
	PinDirection(info->DHT, INPUTPULLUP,info->DHT_Pin);
	while (((*(vuint8*)pin)&(1<<pinNum))!=0x00);		//waiting for response
	while (((*(vuint8*)pin)&(1<<pinNum))==0x00);		//preparing data
	while (((*(vuint8*)pin)&(1<<pinNum))!=0x00);		//DHT pull up the bus for 80us
}
uint8 DHT_Data(DHT_Info *info)
{
	uint8 Data=0,i=0;
	uint16 timeout;
	vuint8 *pin = &(info->DHT->pin);
	uint8 pinNum = info->DHT_Pin;
	for (i=0;i<8;i++)
	{
		timeout = 0xFFFF;
		while (((*(vuint8*)pin)&(1<<pinNum))==0);
		_delay_us(35);
		if (((*(vuint8*)pin)&(1<<pinNum)))
		{
			Data = (Data<<1)|(0x01);
		}
		else
		{
			Data = (Data<<1);
		}
		while ((((*(vuint8*)pin)&(1<<pinNum))!=0x00)&&(--timeout!=0));
	}
	return Data;
}
void DHT_Operate(DHT_Info *info)
{
	DHT_Start(info);
	DHT_Response(info);
	info->IRH = DHT_Data(info);
	info->DRH = DHT_Data(info);
	info->IT = DHT_Data(info);
	info->DT = DHT_Data(info);
	info->Sum = DHT_Data(info);
}