/*
 * Motors.h
 *
 * Created: 11/3/2020 4:46:22 PM
 *  Author: SHAHER
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_
	#include "GPIO.h"
	#include "Timer0.h"
	#include "Timer1.h"
	#include "Timer2.h"

#define F1 (0)
#define F2 (1)
#define L1 (2)
#define L2 (3)
#define R1 (4)
#define R2 (5)
#define B1 (6)
#define B2 (7)

	typedef struct {
		uint8 FWD;
		uint8 FWDN;
		uint8 LFT;
		uint8 LFTN;
		uint8 RHT;
		uint8 RHTN;
		uint8 BCK;
		uint8 BCKN;
		}ROVinfo;

void Forward(uint8 State,uint8 Power);
void Left(uint8 State,uint8 Power);
void Right(uint8 State,uint8 Power);
void Back(uint8 State,uint8 Power);

void ROV_Remote(ROVinfo *info,uint8 data);



#endif /* MOTORS_H_ */