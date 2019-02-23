/*********************************************************************************************
程序名：	温度值OLED屏显示程序
编写人：	杜洋	
编写时间：	2018年2月27日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  
*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "lm75a.h"
#include "oled0561.h"

int main (void)
{
	u8 buffer[3];
	delay_ms(100); //上电时等待其他器件就绪
	RCC_Configuration(); //系统时钟初始化 

	I2C_Configuration();//I2C初始化
	LM75A_GetTemp(buffer); //读取LM75A的温度数据

	OLED0561_Init(); //OLED初始化

	OLED_DISPLAY_8x16_BUFFER(0,"   YoungTalk "); //显示字符串
	OLED_DISPLAY_8x16_BUFFER(6,"  Temp:"); //显示字符串

	while(1)
	{
		LM75A_GetTemp(buffer); //读取LM75A的温度数据
			
		if(buffer[0])OLED_DISPLAY_8x16(6,7*8,'-'); //如果第1组为1即是负温度
		OLED_DISPLAY_8x16(6,8*8,buffer[1]/10+0x30);//显示温度值
		OLED_DISPLAY_8x16(6,9*8,buffer[1]%10+0x30);//
		OLED_DISPLAY_8x16(6,10*8,'.');//
		OLED_DISPLAY_8x16(6,11*8,buffer[2]/10+0x30);//
		OLED_DISPLAY_8x16(6,12*8,buffer[2]%10+0x30);//
		OLED_DISPLAY_8x16(6,13*8,'C');//

		delay_ms(200); //延时
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



