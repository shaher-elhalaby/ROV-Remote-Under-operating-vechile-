/*
 * UltraSonic.h
 *
 * Created: 11/9/2020 6:34:15 PM
 *  Author: SHAHER
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

	#include "MACROSH.h"
	#include "StandardTypes.h"
	#include "MC_Config.h"
	#include "GPIO.h"
	#include "EX_INTERRUPT.h"
	#include "Timer1.h"
	
typedef struct{
	GPIO *Uport;
	uint8 Trig;
	INT_Sel Echo;
	INT_Mode INTmODE;
	uint16 Read;
	}UltraSonicInfo;

	
void UltraSonicInit(UltraSonicInfo *info);
void UltrasonicReading(UltraSonicInfo *info);


#endif /* ULTRASONIC_H_ */