/*********************************************************************************************
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

*********************************************************************************************/
#include "stm32f10x.h"    //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"


int main (void)      //主程序
{
	RCC_Configuration(); //时钟设置
	LED_Init();
	while(1)
		{
		
		//方法1：
		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED1接口输出高电平1
		delay_us(50000); //延时1秒
		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED1接口输出低电平0
		delay_us(50000); //延时1秒
		
		//方法2：
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1-GPIO_ReadOutputDataBit(LEDPORT,LED1))); //取反LED1
//		delay_ms(500); //延时1秒

		//方法3：
//		GPIO_SetBits(LEDPORT,LED1); //LED灯都为高电平（1）
//		delay_s(1); //延时1秒
//		GPIO_ResetBits(LEDPORT,LED1); //LED灯都为低电平（0）
//		delay_s(1); //延时1秒

		//方法4
//		GPIO_Write(LEDPORT,0x0001); //直接数值操作将变量值写入LED
//		delay_s(2); //延时1秒
//		GPIO_Write(LEDPORT,0x0000); //直接数值操作将变量值写入LED
//		delay_s(2); //延时1秒

	  }
}




/*

【变量定义说说明】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8      a; //定义8位无符号变量a
vu32    a; //定义易变的32位无符号变量a
vu16    a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32    a; //定义只读的32位无符号变量a
uc16    a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒

*/



