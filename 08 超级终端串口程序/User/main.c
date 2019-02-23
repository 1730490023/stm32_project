/*********************************************************************************************
程序名：	超级终端串口控制程序
编写人：	杜洋	
编写时间：	2018年1月13日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "usart.h"


int main (void){//主程序
	RCC_Configuration();
	LED_Init();//LED初始化
	KEY_Init();//按键初始化
	BUZZER_Init();//蜂鸣器初始化
	USART1_Init(115200); //串口初始化，参数中写波特率
	USART1_RX_STA=0xC000; //初始值设为有回车的状态，即显示一次欢迎词
	while(1){
		if(USART1_RX_STA&0xC000){ //如果标志位是0xC000表示收到数据串完成，可以处理。
			if((USART1_RX_STA&0x3FFF)==0){ //单独的回车键再显示一次欢迎词
				printf("\033[1;47;33m\r\n"); //设置颜色（参考超级终端使用）
				printf(" 1y--开LED1灯      1n--关LED1灯 \n\r");
				printf(" 2y--开LED2灯      2n--关LED2灯 \r\n");
				printf(" 请输入控制指令，按回车键执行！ \033[0m\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='1' && USART1_RX_BUF[1]=='y'){ //判断数据是不是2个，第一个数据是不是“1”，第二个是不是“y”
				GPIO_SetBits(LEDPORT,LED1); //LED灯都为高电平（1）
				printf("1y -- LED1灯已经点亮！\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='1' && USART1_RX_BUF[1]=='n'){
				GPIO_ResetBits(LEDPORT,LED1); ////LED灯都为低电平（0）
				printf("1n -- LED1灯已经熄灭！\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='2' && USART1_RX_BUF[1]=='y'){
				GPIO_SetBits(LEDPORT,LED2); //LED灯都为高电平（1）
				printf("2y -- LED2灯已经点亮！\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='2' && USART1_RX_BUF[1]=='n'){
				GPIO_ResetBits(LEDPORT,LED2); ////LED灯都为低电平（0）
				printf("2n -- LED2灯已经熄灭！\r\n");
			}else{ //如果以上都不是，即是错误的指令。
				printf("指令错误！\r\n"); 
			}
			USART1_RX_STA=0; //将串口数据标志位清0
		}
	}
}

/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/
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



