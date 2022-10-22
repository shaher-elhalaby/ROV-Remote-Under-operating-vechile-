/*
 * MAIN.h
 *
 * Created: 11/9/2020 6:25:07 PM
 *  Author: SHAHER
 */ 


#ifndef MAIN_H_
#define MAIN_H_

	#include "RTC.h"
	#include "USART.h"
	#include "MACROSH.h"
	#include "StandardTypes.h"
	#include "GPIO.h"
	#include "MC_Config.h"
	#include "UltraSonic.h"
	#include "EX_INTERRUPT.h"
	#include <avr/io.h>
	#include "DHT11.h"
	
	
void sysInit(void);
void sysUpdate(void);


#endif /* MAIN_H_ */