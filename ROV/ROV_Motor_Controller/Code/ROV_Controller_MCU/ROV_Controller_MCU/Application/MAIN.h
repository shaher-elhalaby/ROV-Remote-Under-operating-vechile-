/*
 * MAIN.h
 *
 * Created: 11/3/2020 4:17:28 PM
 *  Author: SHAHER
 */ 


#ifndef MAIN_H_
#define MAIN_H_

	#include "Motors.h"
	#include "USART.h"
	#include "SPI.h"
	#include "EX_INTERRUPT.h"
	#include "StandardTypes.h"
	#include "MACROSH.h"
	#include <avr/io.h>
	
	
void sysInit(void);
void sysUpdate(void);


#endif /* MAIN_H_ */