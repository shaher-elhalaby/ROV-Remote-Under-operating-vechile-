/*
 * MAIN.h
 *
 * Created: 11/6/2020 7:34:16 PM
 *  Author: SHAHER
 */ 


#ifndef MAIN_H_
#define MAIN_H_
	
	#include <avr/io.h>
	#include "GPIO.h"
	#include "ADC.h"
	#include "StandardTypes.h"
	#include "MACROSH.h"
	#include "USART.h"

#define FWD  (PB0)	
#define LFT  (PB1)	
#define RHT  (PB2)	
#define BCK  (PB2)	
	
void sysInit(void);
void sysUpdate(void);



#endif /* MAIN_H_ */