/*
 * KeyPad.c
 *
 * Created: 5/29/2020 5:20:41 AM
 *  Author: shaher
 */ 

#include "KeyPad.h"

#define KEYPAD_NO_NEW_DATA  '*'

void KeyPad_Init( KeypadInfo *keypad )
{
	PinDirection(keypad->G_OUT,OUTPUT,keypad->PINs0);
	PinDirection(keypad->G_OUT,OUTPUT,keypad->PINs1);
	PinDirection(keypad->G_OUT,OUTPUT,keypad->PINs2);
#if key4x4		
	PinDirection(keypad->G_OUT,OUTPUT,keypad->PINs3);
#endif	
	PinDirection(keypad->G_IN,INPUTPULLUP,keypad->PINs4);
	PinDirection(keypad->G_IN,INPUTPULLUP,keypad->PINs5);
	PinDirection(keypad->G_IN,INPUTPULLUP,keypad->PINs6);
	PinDirection(keypad->G_IN,INPUTPULLUP,keypad->PINs7);
}

uint8 Keypad_Read( KeypadInfo *keypad )
{
	static uint8 oldKey;
	uint8 Key = KEYPAD_NO_NEW_DATA;
	static uint8 Last_valid_key_G;
	PinWrite(keypad->G_OUT,keypad->PINs0,LOW);
		if(PinRead(keypad->G_IN,keypad->PINs4)==0) Key=50;
		if(PinRead(keypad->G_IN,keypad->PINs5)==0) Key=52;
		if(PinRead(keypad->G_IN,keypad->PINs6)==0) Key=54;
		if(PinRead(keypad->G_IN,keypad->PINs7)==0) Key=56;
	PinWrite(keypad->G_OUT,keypad->PINs0,HIGH);
	
	PinWrite(keypad->G_OUT,keypad->PINs1,LOW);
		if(PinRead(keypad->G_IN,keypad->PINs4)==0) Key=58;
		if(PinRead(keypad->G_IN,keypad->PINs5)==0) Key=60;
		if(PinRead(keypad->G_IN,keypad->PINs6)==0) Key=62;
		if(PinRead(keypad->G_IN,keypad->PINs7)==0) Key=64;
	PinWrite(keypad->G_OUT,keypad->PINs1,HIGH);
	
	PinWrite(keypad->G_OUT,keypad->PINs2,LOW);
		if(PinRead(keypad->G_IN,keypad->PINs4)==0) Key=66;
		if(PinRead(keypad->G_IN,keypad->PINs5)==0) Key=68;
		if(PinRead(keypad->G_IN,keypad->PINs6)==0) Key=70;
		if(PinRead(keypad->G_IN,keypad->PINs7)==0) Key=72;
	PinWrite(keypad->G_OUT,keypad->PINs2,HIGH);
#if key4x4	
	PinWrite(keypad->G_OUT,keypad->PINs3,LOW);
		if(PinRead(keypad->G_IN,keypad->PINs4)==0) Key=74;
		if(PinRead(keypad->G_IN,keypad->PINs5)==0) Key=76;
		if(PinRead(keypad->G_IN,keypad->PINs6)==0) Key=78;
		if(PinRead(keypad->G_IN,keypad->PINs7)==0) Key=80;
	PinWrite(keypad->G_OUT,keypad->PINs3,HIGH);
#endif	
	if(Key == KEYPAD_NO_NEW_DATA)
	{
		oldKey = KEYPAD_NO_NEW_DATA;
		Last_valid_key_G = KEYPAD_NO_NEW_DATA;
		return 0;
	}
	if (Key == oldKey)
	{
		if (Key != Last_valid_key_G)
		{
			keypad->KeyOut=Key;
			Last_valid_key_G =Key;
			return 1;
		}
	}
		
	oldKey = Key;
	return 0;	
}


 uint8 KeypadPhone( KeypadInfo *keypad )
 {
	 keypad->KeyAv=Keypad_Read(keypad);
	 switch (keypad->KeyOut)
	 {
		 case 50:
			keypad->KeyOut = '1';
			break;
		case 52:
			keypad->KeyOut = '4';
			break;
		case 54:
			keypad->KeyOut = '7';
			break;
		case 56:
			keypad->KeyOut = '*';
			break;
		case 58:
			keypad->KeyOut = '2';
			break;
		case 60:
			keypad->KeyOut = '5';
			break;
		case 62:
			keypad->KeyOut = '8';
			break;
		case 64:
			keypad->KeyOut = '0';
			break;
		case 66:
			keypad->KeyOut = '3';
			break;
		case 68:
			keypad->KeyOut = '6';
			break;
		case 70:
			keypad->KeyOut = '9';
			break;
		case 72:
			keypad->KeyOut = '#';
			break;
	 }
	 return keypad->KeyAv;
 }