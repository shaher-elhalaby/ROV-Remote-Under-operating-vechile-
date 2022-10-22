/*
 * Authentication.c
 *
 * Created: 11/1/2020 5:10:56 PM
 *  Author: SHAHER
 */ 
#include "Authentication.h"
#include <string.h>

uint8 OneTimeAuth=0;

void InitAuthStruct(AuthInfo *Auth,LCD_CONFIG *lcd,KeypadInfo *Key)
{
	Auth->CountScreen=0;
	Auth->Key=Key;
	Auth->lcd=lcd;
}
uint8 Authenticate(AuthInfo *Auth)
{
	uint8 show;
	if (OneTimeAuth==0)
	{
		EEPROM_Read_Word(PassAddress,Auth->passStored);
		OneTimeAuth++;
	}
	if (Auth->Key->KeyAv== 1)
	{
		if (Auth->Key->KeyOut == '*')
		{
			Auth->CountScreen --;
			if (Auth->CountScreen <=0)
			{
				Auth->CountScreen =0;
			}
			show = ' ';
			LCD_RowCol(Auth->lcd,2,Auth->CountScreen);
			LCD_Send_Char(Auth->lcd,show);
		}
		else if (Auth->Key->KeyOut == '#')
		{
			Auth->passEntered[Auth->CountScreen]='\0';
			if (strcmp((char*)Auth->passEntered,(char*)Auth->passStored)==0)
			{
				Auth->CountScreen =0;
				return 1;
			}
			else
			{
				Auth->CountScreen =0;
				Wrong(Auth->lcd);
				return 0;
			}
		}
		else if (Auth->Key->KeyOut != '*' && Auth->Key->KeyOut !='#')
		{
			show = '*';
			Auth->passEntered[Auth->CountScreen]=Auth->Key->KeyOut;
			LCD_RowCol(Auth->lcd,2,Auth->CountScreen);
			LCD_Send_Char(Auth->lcd,show);
			Auth->CountScreen++;
		}
	}
	return 0;
}

void Wrong(LCD_CONFIG *lcd)
{
	static uint8 WrongCount = 0;

		LCD_Clear(lcd);
		LCD_RowCol(lcd,1,5);
		LCD_Send_String(lcd,(uint8*)"Wrong");
		WrongCount++;
		LCD_RowCol(lcd,1,12);
		LCD_DisplayInt(lcd,WrongCount);
}

void InitSetStruct(SetInfo *Set,LCD_CONFIG *lcd,KeypadInfo *Key)
{
	Set->PassCfmCount=0;
	Set->PassSetCount=0;
	Set->SetCount=0;
	Set->Key=Key;
	Set->lcd=lcd;
}
uint8 SetupMode(SetInfo *Set)
{
	switch(Set->SetCount)
	{
		case 0:
			LCD_Clear(Set->lcd);
			LCD_RowCol(Set->lcd,0,3);
			LCD_Send_String(Set->lcd,(uint8*)"Enter Pass");
			LCD_RowCol(Set->lcd,2,3);
			LCD_Send_String(Set->lcd,(uint8*)"Confirm Pass");
			Set->SetCount=1;
			break;
		case 1:
			if (SetPass(Set))
			{
				Set->SetCount =2;
			}
			break;
		case 2:
			if(cfmPass(Set))
			{
				Set->SetCount =3;
			}
			break;
		case 3:
			if (strcmp((char*)Set->passCfmed,(char*)Set->passSetted)==0)
			{
				EEPROM_Write_Word(PassAddress,Set->passCfmed);
				OneTimeAuth=0;
				Set->SetCount=0;
				return 1;
			}
			else
			{
				Set->SetCount=0;
				Wrong(Set->lcd);
				_delay_ms(500);
			}	
			break;	
	}
	return 0;
}

uint8 SetPass(SetInfo *Set)
{
		uint8 show;
		if (Set->Key->KeyAv == 1)
		{
			if (Set->Key->KeyOut == '*')
			{
				Set->PassSetCount --;
				if (Set->PassSetCount <=0)
				{
					Set->PassSetCount =0;
				}
				show = ' ';
				LCD_RowCol(Set->lcd,1,Set->PassSetCount);
				LCD_Send_Char(Set->lcd,show);
			}
			if (Set->Key->KeyOut == '#')
			{
				Set->PassSetCount ++;
				Set->passSetted[Set->PassSetCount]='\0';
				Set->PassSetCount=0;
					return 1;
			}
			if (Set->Key->KeyOut != '*' && Set->Key->KeyOut !='#')
			{
				show = '*';
				Set->passSetted[Set->PassSetCount]=Set->Key->KeyOut;
				LCD_RowCol(Set->lcd,1,Set->PassSetCount);
				LCD_Send_Char(Set->lcd,show);
				Set->PassSetCount++;
			}
		}
		return 0;
}
uint8 cfmPass(SetInfo *Set)
{
	uint8 show;
	if (Set->Key->KeyAv == 1)
	{
		if (Set->Key->KeyOut == '*')
		{
			Set->PassCfmCount --;
			if (Set->PassCfmCount <=0)
			{
				Set->PassCfmCount =0;
			}
			show = ' ';
			LCD_RowCol(Set->lcd,3,Set->PassCfmCount);
			LCD_Send_Char(Set->lcd,show);
		}
		if (Set->Key->KeyOut == '#')
		{
			Set->PassCfmCount ++;
			Set->passCfmed[Set->PassCfmCount]='\0';
			Set->PassCfmCount=0;
			return 1;
		}
		if (Set->Key->KeyOut != '*' && Set->Key->KeyOut !='#')
		{
			show = '*';
			Set->passCfmed[Set->PassCfmCount]=Set->Key->KeyOut;
			LCD_RowCol(Set->lcd,3,Set->PassCfmCount);
			LCD_Send_Char(Set->lcd,show);
			Set->PassCfmCount++;
		}
	}
	return 0;
}
