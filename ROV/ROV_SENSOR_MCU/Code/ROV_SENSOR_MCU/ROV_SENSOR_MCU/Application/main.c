/*
 * ROV_SENSOR_MCU.c
 *
 * Created: 11/9/2020 6:06:26 PM
 * Author : SHAHER
 */ 
#include "MAIN.h"




int main(void)
{
    sysInit();
    while (1) 
    {
		sysUpdate();
    }
}

