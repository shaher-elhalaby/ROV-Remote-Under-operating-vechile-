/*
 * Assist.c
 *
 * Created: 11/9/2020 6:25:21 PM
 *  Author: SHAHER
 */ 
#include "MAIN.h"
#include <avr/interrupt.h>
#include "Assist.h"

UltraSonicInfo UTR_H;
UltraSonicInfo UTR_V;
DHT_Info DHT;
RTC_Info RTC;

void sysInit(void)
{
	UTR_H.Uport =GPIOD;
	UTR_H.Echo =_INT1;
	UTR_H.INTmODE = LVL_INT1;
	UTR_H.Trig = PD4;
	UltraSonicInit(&UTR_H);
	UTR_V.Uport =GPIOD;
	UTR_V.Echo =_INT0;
	UTR_V.INTmODE = LVL_INT0;
	UTR_V.Trig = PD5;
	UltraSonicInit(&UTR_V);
	DHT.DHT = GPIOB;
	DHT.DHT_Pin = PB5;
	I2C_Init(0X08,100000,I2C_INT_Disable,I2C_pre1);
	RTC_Init(&RTC);
	USART_Init(9600, _8Bit_9Bit, USART_Async, USART_INT_Disable, PARITY_Disable, STOP1);
}
void sysUpdate(void)
{
	DHT_Operate(&DHT);
	RTC_Read(&RTC);
	UltrasonicReading(&UTR_H);
	UltrasonicReading(&UTR_V);
	MassgeUpdata();
	_delay_ms(1000);
}

void TransUART(uint8 *ptr)
{
	while (*ptr!='\0')
	{
		USART_SendByte(*ptr);
		ptr++;
	}
}

void MassgeUpdata(void)
{
	static uint8 Date[24],clk[24];
	static uint8 temp[30],HM[30];
	static uint8 HORIZ[30],VERT[30];
	DisplayRTC(&RTC,Date,clk);
	DHTDis(&DHT,temp,HM);
	DisULR(&UTR_H,&UTR_V,HORIZ,VERT);
	TransUART((uint8*)"**************************************");
	USART_SendByte(0x0D);
	TransUART(Date);
	USART_SendByte(0x0D);
	TransUART(clk);
	USART_SendByte(0x0D);
	TransUART(temp);
	USART_SendByte(0x0D);
	TransUART(HM);
	USART_SendByte(0x0D);
	TransUART(HORIZ);
	USART_SendByte(0x0D);
	TransUART(VERT);
	USART_SendByte(0x0D);
	TransUART((uint8*)"**************************************");
	USART_SendByte(0x0D);
}

void DisplayRTC(RTC_Info *info,uint8 *Date,uint8 *clk)
{
	static char shour[2],smin[2],ssec[2];
	static char shour1[2],smin1[2],ssec1[2];
	
	static uint8 syear[2],smon[2],sday[2];
	static uint8 ssyear[2],ssmon[2],ssday[2];
	
	itoa((info->Hour&0x0f),shour,10);
	itoa((info->Min&0x0f),smin,10);
	itoa((info->Second&0x0f),ssec,10);
	itoa((info->Hour>>4),shour1,10);
	itoa(info->Min>>4,smin1,10);
	itoa(info->Second>>4,ssec1,10);
	
	itoa((info->Date&0x0f),(char*)sday,10);
	itoa((info->Mon&0x0f),(char*)smon,10);
	itoa((info->Year&0x0f),(char*)syear,10);
	itoa((info->Date>>4),(char*)ssday,10);
	itoa(info->Mon>>4,(char*)ssmon,10);
	itoa(info->Year>>4,(char*)ssyear,10);
	
	strcpy((char*)clk,"ClocK:");
	strcat((char*)clk,(char*)shour1);
	strcat((char*)clk,(char*)shour);
	strcat((char*)clk,":");
	strcat((char*)clk,(char*)smin1);
	strcat((char*)clk,(char*)smin);
	strcat((char*)clk,":");
	strcat((char*)clk,(char*)ssec1);
	strcat((char*)clk,(char*)ssec);	
	
	strcpy((char*)Date,"Date:");
	strcat((char*)Date,(char*)ssday);
	strcat((char*)Date,(char*)sday);
	strcat((char*)Date,"/");
	strcat((char*)Date,(char*)ssmon);
	strcat((char*)Date,(char*)smon);
	strcat((char*)Date,"/");
	strcat((char*)Date,(char*)ssyear);
	strcat((char*)Date,(char*)syear);

}

void DHTDis(DHT_Info *DHT,uint8 *temp ,uint8 *hum)
{
	static uint8 tmp[4],rh[4];
	
	itoa(DHT->IRH,(char*)rh,10);
	itoa(DHT->IT,(char*)tmp,10);
	
	strcpy((char*)temp,"Temperature : ");
	strcat((char*)temp,(char*)tmp);
	strcat((char*)temp," C.");
	
	strcpy((char*)hum,"Humedity : ");
	strcat((char*)hum,(char*)rh);
	strcat((char*)hum," %");
}

void DisULR(UltraSonicInfo *ulrh,UltraSonicInfo *ulrv,uint8 *ulrhw,uint8 *ulrvw)
{
	static uint8 horiz[4],vert[4];
	
	itoa(ulrh->Read,(char*)horiz,10);
	itoa(ulrv->Read,(char*)vert,10);
	
	strcpy((char*)ulrhw,"Horizontal Distance : ");
	strcat((char*)ulrhw,(char*)horiz);
	strcat((char*)ulrhw," cm.");
	
	strcpy((char*)ulrvw,"Vertical Distance : ");
	strcat((char*)ulrvw,(char*)vert);
	strcat((char*)ulrvw," cm.");
}