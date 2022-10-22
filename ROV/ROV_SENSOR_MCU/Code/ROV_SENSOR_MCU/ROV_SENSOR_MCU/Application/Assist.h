/*
 * Assist.h
 *
 * Created: 11/15/2020 10:29:54 PM
 *  Author: SHAHER
 */ 


#ifndef ASSIST_H_
#define ASSIST_H_
	
	#include <string.h>
	#include <stdlib.h>
	
	void TransUART(uint8 *ptr);
	void MassgeUpdata(void);
	void DisplayRTC(RTC_Info *info,uint8 *Date,uint8 *clk);
	void DHTDis(DHT_Info *DHT,uint8 *temp ,uint8 *hum);
	void DisULR(UltraSonicInfo *ulrh,UltraSonicInfo *ulrv,uint8 *ulrhw,uint8 *ulrvw);

#endif /* ASSIST_H_ */