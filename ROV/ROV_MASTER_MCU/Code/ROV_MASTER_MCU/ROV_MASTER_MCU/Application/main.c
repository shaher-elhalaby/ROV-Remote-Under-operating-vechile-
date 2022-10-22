/*
 * ROV_MASTER_MCU.c
 *
 * Created: 11/1/2020 5:02:33 PM
 * Author : SHAHER
 */ 

#include "MAIN.h"

int main(void)
{
    sysInit();
	SchedulerIntit();
	createTask(sysUpdate,0,1,1);
	createTask(Remote_Access,0,50,1);
	createTask(KaypadEnable,0,1,0);
	Boot();
	SchedulerStart();
    while (1) 
    {
		Dispatcher();
    }
}

