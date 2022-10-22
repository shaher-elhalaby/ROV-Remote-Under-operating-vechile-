/*
 * SPI.c
 *
 * Created: 7/13/2020 7:52:51 PM
 *  Author: shaher
 */ 

#include "SPI.h"

void SPI_Init(SPI_INT INT,SPI_CTL CTL,SPI_MODE MODE,SPI_CLK CLK,SPISpeed X)
{
	if (CTL == SPI_Master)
	{
		PinDirection(GPIOB,OUTPUT,PIN5);
		PinDirection(GPIOB,OUTPUT,PIN7);
	}
	else
	{
		PinDirection(GPIOB,OUTPUT,PIN6);
	}
	
	SPCR = INT|(SPI_Enable)|(CTL)|MODE|CLK;
	SPSR = X;
}
void SPI_Read(uint8 * Data)
{
	while ((SPSR&(1<<SPIF))==0x00);
	*Data = SPDR;
}
void SPI_Write(uint8 Data)
{
	SPDR = Data;
	while ((SPSR&(1<<SPIF))==0x00);
}
