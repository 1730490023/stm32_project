/*********************************************************************************************
程序名：	  按键控制LED呼吸灯快慢 程序
编写时间：	2017年12月29日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz

bug : 按键会随机使单片机 进入死区，导致程序跑飞　  
*********************************************************************************************/

#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h" 

int main (void)   //主程序
{
	u8 MENU,mosi; //定义变量  
  u16 t,i,timer; 
  timer = 600;
	mosi = 0;
	MENU = 0;
	t = 1;
	RCC_Configuration(); //时钟设置
	LED_Init();          //LED初始化
	KEY_Init();          //按键初始化

	while(1)
	{
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1))  //读按键接口的电平
		{ 
			delay_ms(20); //延时去抖动
			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)) //读按键接口的电平
			{
				if(mosi == 0)
				{
					timer = timer-100;
					if(timer < 100)
					{
						mosi = 1;
					}
				}
				if(mosi == 1)
				{
					timer = timer+100;
					if(timer > 600)
					{
						mosi = 0;
					}
				}
			}
				//GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1-GPIO_ReadOutputDataBit(LEDPORT,LED1))); //LED取反
				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1)); //等待按键松开
			
		}
		
		if(MENU == 0)  //变亮循环
		{ 
			for(i = 0; i < 10; i++)
				{
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED1接口输出高电平1
				delay_us(t);   //延时
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED1接口输出低电平0
				delay_us(timer+1-t); //延时
			  }
			t++;
			if(t==timer)
			{
				MENU = 1;
			}
		}
		if(MENU == 1)  //变暗循环
		{ 
			for(i = 0; i < 10; i++)
				{
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED1接口输出高电平1
				delay_us(t); //延时
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED1接口输出低电平0
				delay_us(timer+1-t); //延时
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

		//示例1：无锁存
//		if(GPIO_ReadInputDataBit(KEYPORT,KEY1))//读按键接口的电平
//			{ 
//			 GPIO_ResetBits(LEDPORT,LED1); //LED灯都为低电平（0） 
//		  }
//			else
//			{	
//       GPIO_SetBits(LEDPORT,LED1);    //LED灯都为高电平（1） 
//		  }

		//示例2：无锁存
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(!GPIO_ReadInputDataBit(KEYPORT,KEY1))); 

		//示例3：有锁存
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1))  //读按键接口的电平
//		{ 
//			delay_ms(20); //延时去抖动
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)) //读按键接口的电平
//			{ 
//				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1-GPIO_ReadOutputDataBit(LEDPORT,LED1))); //LED取反
//				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1)); //等待按键松开 
//			}
//		}

		//示例4：有锁存
//		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)) //读按键接口的电平
//			{ 
//			delay_ms(20); //延时20ms去抖动
//			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1))   //读按键接口的电平
//				{ 
//				//在2个LED上显示二进制加法
//				a++;          //变量加1
//				if(a>3)       //当变量大于3时清0
//				{ 
//					a=0; 
//				}
//				GPIO_Write(LEDPORT,a); //直接数值操作将变量值写入LED（LED在GPIOB组的PB0和PB1上）
//				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1)); //等待按键松开 
//			}
//		}
//
