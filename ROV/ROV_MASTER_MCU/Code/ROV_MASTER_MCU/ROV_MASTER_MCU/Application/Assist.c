/*
 * Assist.c
 *
 * Created: 11/1/2020 5:13:07 PM
 *  Author: SHAHER
 */ 

#include "MAIN.h"


LCD_CONFIG lcd;
KeypadInfo keypad;
AuthInfo Auth;
SetInfo Set;
static uint8 remoteCount=0;
uint8 Screen,RemoteAccess=0;

void sysInit(void)
{
	lcd.E=PA2;
	lcd.RS=PA3;
	lcd.LCD_Control=GPIOA;
	lcd.LCD_Data=GPIOA;
	LCD_INIT(&lcd);
	keypad.G_IN=GPIOC;
	keypad.G_OUT=GPIOB;
	keypad.PINs4=PC2;
	keypad.PINs5=PC3;
	keypad.PINs6=PC4;
	keypad.PINs7=PC5;
	
	keypad.PINs0=PB0;
	keypad.PINs1=PB1;
	keypad.PINs2=PB2;
	
	KeyPad_Init(&keypad);
	USART_Init(9600,_8Bit_9Bit, USART_Async,USART_INT_Disable, PARITY_Disable, STOP1);
	SPI_Init(SPI_NO_INT, SPI_Master, SET_R_SPL_F, SPI_FCPU16, SPI_1X);
	PinDirection(GPIOD,OUTPUT,7);
	PinDirection(GPIOB,OUTPUT,4);
	InitAuthStruct(&Auth,&lcd,&keypad);
	InitSetStruct(&Set,&lcd,&keypad);
}
void sysUpdate(void)
{
	switch(Screen)
	{
		case SetUp:
			if(SetupMode(&Set))
			{
				Screen =First;
				EEPROM_Write(firsttimeAddress,55);
			}
			break;
		case First:
			FirstScreen();
			break;
		case Second:
			SecondScreen();
			break;
		case Remote:
			RemoteAccess=1;
			if (keypad.KeyOut=='*')
			{
				Screen =Second;
				RemoteAccess=0;
				remoteCount=0;
			}
			break;	
	}
}

void KaypadEnable(void)
{
	keypad.KeyAv = KeypadPhone(&keypad);
}

void Remote_Access(void)
{
	if (RemoteAccess == 1)
	{
		uint8 data;
		switch(remoteCount)
		{
			case 0:
				LCD_Clear(&lcd);
				LCD_RowCol(&lcd,1,2);
				LCD_Send_String(&lcd,(uint8*)"Remote Access");
				remoteCount++;
				break;
			case 1:
				data=USART_RecByte();
				PinWrite(GPIOB,4,LOW);
				SPI_Write(data);
				PinWrite(GPIOB,4,HIGH);
				break;
		}
	}
}

void Boot(void)
{
	LCD_RowCol(&lcd,1,1);
	LCD_Send_String(&lcd,(uint8*)"Welcome To ROV");
	_delay_ms(500);
	LCD_Clear(&lcd);
	if(EEPROM_Read(firsttimeAddress)==55)
	{
		Screen =First;
	}
	else
	{
		Screen =SetUp;
	}
}
void FirstScreen(void)
{
	static uint8 FirstCount=0;
	switch(FirstCount)
	{
		case 0 :
			LCD_Clear(&lcd);
			LCD_RowCol(&lcd,0,6);
			LCD_Send_String(&lcd,(uint8*)" ROV ");
			LCD_RowCol(&lcd,1,0);
			LCD_Send_String(&lcd,(uint8*)"   Enter Pass  ");
			FirstCount++;
			break;
		case 1:
			if (Authenticate(&Auth))
			{
				Screen = Second;
				FirstCount =0;
			}
			break;
	}
}
void SecondScreen(void)
{
	static uint8 SecondCount=0;
	switch(SecondCount)
	{
		case 0:
			LCD_Clear(&lcd);
			LCD_RowCol(&lcd,0,0);
			LCD_Send_String(&lcd,(uint8*)"1.Remote Access");
			LCD_RowCol(&lcd,1,0);
			LCD_Send_String(&lcd,(uint8*)"2.change Pass");
			LCD_RowCol(&lcd,2,0);
			LCD_Send_String(&lcd,(uint8*)"3.log out");
			SecondCount++;
			break;
		case 1:
		if (keypad.KeyAv)
		{
			switch(keypad.KeyOut)
			{
				case '1':
					Screen =Remote;
					SecondCount=0;
					break;
				case '2':
					Screen=SetUp;
					SecondCount=0;
					break;
				case '3':
					Screen =First;
					SecondCount=0;
					break;
			}
		}
		break;
	}
}
uint8 dataFilter(uint8 data)
{
	uint8 tmp;
	switch (data)
	{
		case 'w':
			tmp = 'w';
			break;
		case 'a':
			tmp = 'a';
			break;
		case 'd':
			tmp = 'd';
			break;
		case 's':
			tmp = 's';
			break;
		default:
			tmp = ' ';
			break;				
	}
	return tmp;
}