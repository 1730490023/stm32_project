#ifndef __DHT11_H
#define __DHT11_H	 
#include "sys.h"
#include "delay.h"

#define DHT11PORT	GPIOA	//定义IO接口
#define DHT11_IO	GPIO_Pin_15	//定义IO接口


void DHT11_IO_OUT (void);
void DHT11_IO_IN (void);
void DHT11_RST (void);
u8 Dht11_Check(void); 	   
u8 Dht11_ReadBit(void); 
u8 Dht11_ReadByte(void); 
u8 DHT11_Init (void);
u8 DHT11_ReadData(u8 *h);
		 				    
#endif
