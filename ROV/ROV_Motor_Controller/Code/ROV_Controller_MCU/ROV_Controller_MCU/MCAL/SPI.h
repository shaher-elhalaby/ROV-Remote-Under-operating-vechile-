/*
 * SPI.h
 *
 * Created: 7/13/2020 7:53:01 PM
 *  Author: shaher
 */ 


#ifndef SPI_H_
#define SPI_H_

     #include "StandardTypes.h"
	 #include "MACROSH.h"
	 #include "GPIO.h"
	 #include <avr/io.h>
	 
	 #define SPI_Enable   (0x40)
	 #define check_SPIF() (Bit_Is_Set(SPSR,7))
	 #define Clear_SPIF() (Set_Bit(SPSR,7))
	 
	 
  typedef enum{
	SPI_NO_INT =0x00,
	SPI_INT_EN =0x80,
  }SPI_INT;
  
  typedef enum{
	  SPI_Slave  =0x00,
	  SPI_Master =0x10,
  }SPI_CTL;
  
  typedef enum{
	  SPI_LSB=0X00,
	  SPI_MSB=0X20,
  }SPI_DORD;
  
  typedef enum{
	  SPL_R_SET_F =0x00,
	  SET_R_SPL_F =0x04,
	  SPL_F_SET_R =0x08,
	  SET_F_SPL_R =0x09,
  }SPI_MODE;
  
  typedef enum{
	  SPI_FCPU4  ,
	  SPI_FCPU16 ,
	  SPI_FCPU64 ,
	  SPI_FCPU128,
  }SPI_CLK;
  
  typedef enum{
	  SPI_1X,
	  SPI_2X,
  }SPISpeed;
	 
	 
void SPI_Init(SPI_INT INT,SPI_CTL CTL,SPI_MODE MODE,SPI_CLK CLK,SPISpeed X);
void SPI_Read(uint8 * Data);
void SPI_Write(uint8 Data);



#endif /* SPI_H_ */