/*
 * Assist.c
 *
 * Created: 11/3/2020 4:18:08 PM
 *  Author: SHAHER
 */ 
#include "MAIN.h"

void sysInit(void)
{
	SPI_Init(SPI_NO_INT, SPI_Slave, SET_R_SPL_F, SPI_FCPU16, SPI_1X);
	//USART_Init(9600,_8Bit_9Bit, USART_Async,USART_INT_Disable, PARITY_Disable, STOP1);
	
	PinDirection(GPIOD,OUTPUT,PIN4);
	PinDirection(GPIOD,OUTPUT,PIN5);
	T0_Init(T0_PhaseCorrect,T0_NonInverting_OC0, T0_NoInterrupt, T0_FCPU64);
	Timer1_Init( T1_Phase_Correct_PWM_8Bit, T1_Phase_Correct_PWM_Non_Inverting_OC1A, T1_Phase_Correct_PWM_Non_Inverting_OC1B, T1_FCPU64);
	T2_Init(T2_PhaseCorrect, T2_NonInverting_OC2, T2_NoInterrupt, T2_FCPU64);
	PortDirection(GPIOA,OUTPUT);
}
void sysUpdate(void)
{
	uint8 data;
	ROVinfo ROV;
	//data=USART_RecByte();
	SPI_Read(&data);
	//USART_SendByte(data);
	ROV_Remote(&ROV,data);
	Forward(ROV.FWD,ROV.FWDN);
	Left(ROV.LFT,ROV.LFTN);
	Right(ROV.RHT,ROV.RHTN);
	Back(ROV.BCK,ROV.BCKN);
}