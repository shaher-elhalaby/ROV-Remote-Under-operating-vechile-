/*
 * MAIN.h
 *
 * Created: 11/1/2020 5:09:36 PM
 *  Author: SHAHER
 */ 


#ifndef MAIN_H_
#define MAIN_H_

	#include <avr/io.h>
	#include "MACROSH.h"
	#include "StandardTypes.h"
	#include "MC_Config.h"
	#include "KeyPad.h"
	#include "LCD.h"
	#include "EEPROM.h"
	#include "USART.h"
	#include "Authentication.h"
	#include "SPI.h"
	#include "EX_INTERRUPT.h"
	#include <avr/io.h>
	#include "HypirdScheduler.h"
	
	#define First  1
	#define Second 2
	#define Third  3
	#define SetUp  0
	#define Remote 4
	
	#define firsttimeAddress 0x08 
	
void Boot(void);	
void FirstScreen(void);
void SecondScreen(void);
void Remote_Access(void);

void sysInit(void);
void sysUpdate(void);

void KaypadEnable(void);

uint8 dataFilter(uint8 data);

#endif /* MAIN_H_ */