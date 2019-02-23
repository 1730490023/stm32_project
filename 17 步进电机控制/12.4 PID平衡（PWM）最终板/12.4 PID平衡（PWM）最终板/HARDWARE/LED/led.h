#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0  PCout(6)	// PC6
#define LED1  PCout(7)	// PC7	
#define LED3  PCout(13)	// PC13	
#define LDIR  PAout(7)	// PA7
#define LSTEP PAout(6)	// PA6
#define RDIR  PBout(1)	// PB1
#define RSTEP PBout(0)	// PB0
#define EN PBout(12)	  // PB12


void LED_Init(void);//初始化

		 				    
#endif
