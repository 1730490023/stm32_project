/*********************************************************************************************
程序名：	MIDI音乐播放程序
编写时间：	2017年12月30日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h" 
#include "flash.h" 

#include "buzzer.h"

#define FLASH_START_ADDR  0x0801f000	  //写入的起始地址


int main (void){//主程序
	u16 a; //定义变量
	//初始化程序
	RCC_Configuration(); //时钟设置
	LED_Init();//LED初始化
	KEY_Init();//按键初始化

	BUZZER_Init();//蜂鸣器初始化
//	BUZZER_BEEP1();//蜂鸣器音1
	MIDI_PLAY(); //播放MIDI音乐

    a = FLASH_R(FLASH_START_ADDR);//从指定页的地址读FLASH
	GPIO_Write(LEDPORT,a|0xfffc&GPIO_ReadOutputData(LEDPORT)); //直接数值操作将变量值写入LED（LED在GPIOB组的PB0和PB1上）


	//主循环
	while(1){

		//示例4：有锁存
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){ //读按键接口的电平
			delay_ms(20); //延时20ms去抖动
			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){ //读按键接口的电平
				//在2个LED上显示二进制加法
				a++; //变量加1
				if(a>3){ //当变量大于3时清0
					a=0; 
				}
				GPIO_Write(LEDPORT,a|0xfffc&GPIO_ReadOutputData(LEDPORT)); //直接数值操作将变量值写入LED（LED在GPIOB组的PB0和PB1上）
			
				BUZZER_BEEP1();//蜂鸣器音1

				FLASH_W(FLASH_START_ADDR,a); //从指定页的地址写入FLASH
				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1)); //等待按键松开 
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



