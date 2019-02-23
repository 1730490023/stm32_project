/*********************************************************************************************
程序名：	LED呼吸灯程序
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"

int main (void)     //主程序
	{
	//定义需要的变量
	u8 MENU;
	u16 t,i;
	//初始化程序
	RCC_Configuration(); //时钟设置
	LED_Init();
	//设置变量的初始值
	MENU = 0;
	t = 1;
	//主循环
	while(1){
		//菜单0
		if(MENU == 0)       //变亮循环
			{ 
			for(i = 0; i < 10; i++)
				{
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED1接口输出高电平1
				delay_us(t); //延时
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED1接口输出低电平0
				delay_us(501-t); //延时
			  }
			  t++;
			  if(t==500)
				{
				MENU = 1;
			  }
		}
		//菜单1
		if(MENU == 1)     //变暗循环
			{
			for(i = 0; i < 10; i++)
				{
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED1接口输出高电平1
				delay_us(t); //延时
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED1接口输出低电平0
				delay_us(501-t); //延时
		   	}
			 t--;
			 if(t==1)
				 {
			  	MENU = 0;
			   }
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

*/



