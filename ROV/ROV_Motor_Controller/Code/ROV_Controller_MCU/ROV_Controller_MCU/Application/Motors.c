/*
 * Motors.c
 *
 * Created: 11/3/2020 4:46:36 PM
 *  Author: SHAHER
 */ 
#include "Motors.h"


void Forward(uint8 State,uint8 Power)
{
	switch(State)
	{
		case 0:
			PinWrite(GPIOA,F1,0);
			PinWrite(GPIOA,F2,0);
			T0_PWM(0);
			break;
		case 1:
			PinWrite(GPIOA,F1,1);
			PinWrite(GPIOA,F2,0);
			T0_PWM(Power*20);
			break;	
	}
}
void Left(uint8 State,uint8 Power)
{
	switch(State)
	{
		case 0:
			PinWrite(GPIOA,L1,0);
			PinWrite(GPIOA,L2,0);
			T1_PWM_OC1A(0,0, T1_Phase_Correct_PWM_8Bit, T1_Phase_Correct_PWM_Non_Inverting_OC1A);
			break;
		case 1:
			PinWrite(GPIOA,L1,1);
			PinWrite(GPIOA,L2,0);
			T1_PWM_OC1A(Power*20,0, T1_Phase_Correct_PWM_8Bit, T1_Phase_Correct_PWM_Non_Inverting_OC1A);
			break;
	}
}
void Right(uint8 State,uint8 Power)
{
	switch(State)
	{
		case 0:
			PinWrite(GPIOA,R1,0);
			PinWrite(GPIOA,R2,0);
			T1_PWM_OC1B(0,255, T1_Phase_Correct_PWM_8Bit, T1_Phase_Correct_PWM_Non_Inverting_OC1B);
			break;
		case 1:
			PinWrite(GPIOA,R1,1);
			PinWrite(GPIOA,R2,0);
			T1_PWM_OC1B(Power*20,255, T1_Phase_Correct_PWM_8Bit, T1_Phase_Correct_PWM_Non_Inverting_OC1B);
		break;
	}
}
void Back(uint8 State,uint8 Power)
{
	switch(State)
	{
		case 0:
			PinWrite(GPIOA,B1,0);
			PinWrite(GPIOA,B2,0);
			T2_PWM(0);
			break;
		case 1:
			PinWrite(GPIOA,B1,1);
			PinWrite(GPIOA,B2,0);
			T2_PWM(Power*20);
			break;
	}
}

void ROV_Remote(ROVinfo *info,uint8 data)
{
	if (data == 'w')
	{
		info->FWD=1;
		info->FWDN=2;
	}
	else if (data == 'a')
	{
		info->LFT=1;
		info->LFTN=2;
	}
	else if (data == 'd')
	{
		info->RHT=1;
		info->RHTN=2;
	}
	else if (data == 's')
	{
		info->BCK=1;
		info->BCKN=2;
	}
	else if (data == ' ')
	{
		info->FWD=0;
		info->FWDN=0;
		info->LFT=0;
		info->LFTN=0;
		info->RHT=0;
		info->RHTN=0;
		info->BCK=0;
		info->BCKN=0;
	}
	if (data>='A' &&data<'G')
	{
		info->FWDN=(uint8)(data-'A');
	}
	if (data>='G' &&data<'M')
	{
		info->LFTN=data-'G';
	}
	if (data>='M' &&data<'S')
	{
		info->RHTN=data-'M';
	}
	if (data>='S' &&data<'Z')
	{
		info->BCKN=data-'S';
	}
	if (data <=0x08)
	{
		if ((data&0x01)==0x01)
		{
			info->FWD=1;
		}
		else
		{
			info->FWD=0;
		}
		if ((data&0x02)==0x02)
		{
			info->LFT=1;
		}
		else
		{
			info->LFT=0;
		}
		if ((data&0x04)==0x04)
		{
			info->RHT=1;
		}
		else
		{
			info->RHT=0;
		}
		if ((data&0x08)==0x08)
		{
			info->BCK=1;
		}
		else
		{
			info->BCK=0;
		}
	}
}