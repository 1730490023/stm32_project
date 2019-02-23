/*********************************************************************************************
程序名：	LED灯显示RTC走时程序
编写人：	杜洋	  
编写时间：	2018年1月17日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  
	
说明：
 # 本模板加载了STM32F103内部的RCC时钟设置，并加入了利用滴答定时器的延时函数。
 # 可根据自己的需要增加或删减。
*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "usart.h"

#include "rtc.h"

int main (void)
{
	RCC_Configuration(); //系统时钟初始化

	RTC_Config();        //实时时钟初始化

	LED_Init();   //LED初始化
	KEY_Init();   //按键初始化
	BUZZER_Init();//蜂鸣器初始化
	USART1_Init(115200);   //串口初始化，参数中写波特率
	USART1_RX_STA=0xC000;  //初始值设为有回车的状态，即显示一次欢迎词
	while(1)
	{
		if(RTC_Get()==0)     //读出时间值，同时判断返回值是不是0，非0时读取的值是错误的。	
		{   
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(rsec%2)); //LED1接口
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(rmin%2)); //LED2接口
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



