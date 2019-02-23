/*********************************************************************************************
程序名：	USART串口发送程序
编写时间：	2018年1月9日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

接收串口数据分为串口查询方式和串口中断方式
    查询方式没有较高的时实性；
		中断方式会直接用中断方式处理接收的数据；
		  切换方式需要更改.c文件的开启中断
*********************************************************************************************/

#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "usart.h"


int main (void)
{
	//u8 a;

	RCC_Configuration(); //时钟设置

	USART1_Init(115200); //串口初始化（参数是波特率）
  USART2_Init(115200); 
	while(1)
	{
		//查询方式接收
//		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET)  //查询串口待处理标志位
//		{  
//			a =USART_ReceiveData(USART1);                   //读取接收到的数据
//			printf("%c",a);                                 //把收到的数据发送回电脑		  
//		}
//		 

//      delay_ms(1000); //延时
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



