/*********************************************************************************************
程序名：	按键双击和长按程序
编写人：	杜洋	
编写时间：	2018年1月28日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h"

#define KEYA_SPEED1	80	  //长按的时间长度（单位10mS）
#define KEYA_SPEED2	10	  //双击的时间长度（单位20mS）


int main (void)
{
	u8 a=0,b,c=0;
	RCC_Configuration(); //系统时钟初始化 
	LED_Init();          //LED初始化
	TOUCH_KEY_Init();    //按键初始化
	while(1)
	{
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A))   //检测按键是否按下
			{
			delay_ms(20); //延时去抖动
			if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A)) //判断长短键
			{
				while((GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A))&& c < KEYA_SPEED1) //循环判断长按，到时跳转
				{
					c++;delay_ms(10); //长按判断的计时
				}
				if(c>=KEYA_SPEED1) //长键处理
				{ 
					//长按后执行的程序放到此处
					GPIO_WriteBit(LEDPORT,LED1|LED2,(BitAction)(0));//LED控制
					while(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A));
				}
				else     //单击处理
				{ 
					for(b=0;b<KEYA_SPEED2;b++) //检测双击
					{
						delay_ms(20);
						if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A))
						{
							a=1;
							//双击后执行的程序放到此处
							GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));//LED控制
							while(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A));
						}
					}
					if(a==0)   //判断单击
					{ 
						//单击后执行的程序放到此处
						GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));//LED控制
					}
				}
				a=0;c=0; //参数清0
			}
		} //按键判断在此结束

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



