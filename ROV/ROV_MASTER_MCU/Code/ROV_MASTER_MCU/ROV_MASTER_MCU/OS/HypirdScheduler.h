/*
 * Scheduler.h
 *
 * Created: 7/5/2020 8:59:59 PM
 *  Author: shaher
 */ 


#ifndef HYPIRDSCHEDULER_H_
#define HYPIRDSCHEDULER_H_
	
	#include "StandardTypes.h"
	#include "Timer1.h"
	#include "MACROSH.h"
	#include "EX_INTERRUPT.h"
	#include <avr/interrupt.h>

	#define ERROR				 (1)
	#define status				 (0)
	#define Too_Many_Task_Error  (1)
	#define No_Task              (1)
	//#define ERROR_STATUS         (0)


	

	// Task Parameter
	typedef struct {
		void(*FP)(void);  //Task Function
		short Delay;      //Delay of task
		short Period;     //Task Interval
		char Run_me;      //Task in Execute
		uint8 Co_op;	  //co-op or pre.
	}Task_Parameter;

	#define Max_Tasks    (3)  // max number of tasks


	Task_Parameter Task_Array[Max_Tasks];



		//Scheduler Function
		void SchedulerIntit(void);
		void SchedulerUpdate(void);
		void Dispatcher(void);
		void SchedulerStart(void);
		uint16 createTask(void(*PFuntion)(void),uint32 Initail_Delay,uint32 Period,uint8 Co_op);
		void Dispatcher(void);
		uint8 Task_Delete(uint16 Index);
		void Task_Report(void);


#endif /* HYPIRDSCHEDULER_H_ */