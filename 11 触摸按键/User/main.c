/*********************************************************************************************
模板制作：  杜洋工作室/洋桃电子
程序名：	触摸按键驱动程序
编写人：	杜洋	
编写时间：	2018年1月27日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h"

int main (void)
{
	RCC_Configuration(); //系统时钟初始化 
	LED_Init();//LED初始化
	TOUCH_KEY_Init();//按键初始化
	while(1)
	{
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A))    //读触摸按键的电平
		{ 
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));   //LED控制	
		}
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_B))    //读触摸按键的电平
		{ 
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));   //LED控制	
		}
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_C))    //读触摸按键的电平
		{
			GPIO_WriteBit(LEDPORT,LED1|LED2,(BitAction)(0));//LED控制	
		}
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_D))    //读触摸按键的电平
		{ 
			GPIO_WriteBit(LEDPORT,LED1|LED2,(BitAction)(1));//LED控制	
		}
	}
}



/*

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒

GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED控制

*/



