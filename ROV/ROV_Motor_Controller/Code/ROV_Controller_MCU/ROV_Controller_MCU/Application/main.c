/*
 * ROV_Controller_MCU.c
 *
 * Created: 11/3/2020 4:13:27 PM
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

