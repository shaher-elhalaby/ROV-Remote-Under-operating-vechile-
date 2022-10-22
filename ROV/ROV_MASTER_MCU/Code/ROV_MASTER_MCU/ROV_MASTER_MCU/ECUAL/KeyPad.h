/*
 * KeyPad.h
 *
 * Created: 5/29/2020 5:20:51 AM
 *  Author: shaher
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

   #include "GPIO.h"
   #include "StandardTypes.h"
   #include "MACROSH.h"
   
   #define key4x4  (0)
   
   typedef struct{
	   GPIO * G_OUT;
	   uint8 PINs0;
	   uint8 PINs1;
	   uint8 PINs2;
	   uint8 PINs3;
	   GPIO * G_IN;
	   uint8 PINs4;
	   uint8 PINs5;
	   uint8 PINs6;
	   uint8 PINs7;
	   uint8 KeyOut;
	   uint8 KeyAv;
	   }KeypadInfo;
   
      void KeyPad_Init( KeypadInfo *keypad );
							 
	 uint8 Keypad_Read( KeypadInfo *keypad );
	 
	 uint8 KeypadPhone( KeypadInfo *keypad );
	 
	 



#endif /* KEYPAD_H_ */