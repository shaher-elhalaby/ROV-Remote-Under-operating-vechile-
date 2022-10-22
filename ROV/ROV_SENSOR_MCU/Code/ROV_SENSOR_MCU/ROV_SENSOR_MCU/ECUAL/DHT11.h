/*
 * DHT11.h
 *
 * Created: 11/15/2020 5:54:31 PM
 *  Author: SHAHER
 */ 


#ifndef DHT11_H_
#define DHT11_H_

	#include "StandardTypes.h"
	#include "MACROSH.h"
	#include "GPIO.h"
	#include "MC_Config.h"
	
	typedef struct{
		GPIO  *DHT;
		uint8 DHT_Pin;
		uint8 IRH;
		uint8 DRH;
		uint8 IT;
		uint8 DT;
		uint8 Sum;
		}DHT_Info;

void DHT_Start(DHT_Info *info);
void DHT_Response(DHT_Info *info);
uint8 DHT_Data(DHT_Info *info);
void DHT_Operate(DHT_Info *info);

#endif /* DHT11_H_ */