#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//#define LED1 PBout(0)// PB0
//#define LED2 PBout(1)// PB1	
#define LEDPORT	GPIOB	//定义IO接口
#define Setp1	GPIO_Pin_13	//定义IO接口
#define Dir1	GPIO_Pin_12	//定义IO接口
 
#define Setp2	GPIO_Pin_10	//定义IO接口
#define Dir2	GPIO_Pin_11	//定义IO接口



void LED_Init(void);//初始化
	 				    
#endif
