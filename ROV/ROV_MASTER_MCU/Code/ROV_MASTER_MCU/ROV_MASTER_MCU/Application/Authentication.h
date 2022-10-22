/*
 * Authentication.h
 *
 * Created: 11/1/2020 5:10:40 PM
 *  Author: SHAHER
 */ 


#ifndef AUTHENTICATION_H_
#define AUTHENTICATION_H_

	#include "MAIN.h"
	#include "EEPROM.h"
	
	#define  PassAddress  (0x00)
	
	typedef struct{
		uint8 passEntered[16];
		uint8 passStored[16];
		sint8 CountScreen;
		KeypadInfo *Key;
		LCD_CONFIG *lcd;
		}AuthInfo;
	
	typedef struct{
		uint8 passSetted[16];
		uint8 passCfmed[16];
		uint8 SetCount;
		sint8 PassSetCount;
		sint8 PassCfmCount;
		KeypadInfo *Key;
		LCD_CONFIG *lcd;
		}SetInfo;	
		
	void InitAuthStruct(AuthInfo *Auth,LCD_CONFIG *lcd,KeypadInfo *Key);
	uint8 Authenticate(AuthInfo *Auth);
	
	void InitSetStruct(SetInfo *Set,LCD_CONFIG *lcd,KeypadInfo *Key);
	uint8 SetupMode(SetInfo *Set);
	
	uint8 SetPass(SetInfo *Set);
	uint8 cfmPass(SetInfo *Set);
	
void Wrong(LCD_CONFIG *lcd);



#endif /* AUTHENTICATION_H_ */