/*********************************************************************************************
模板制作：  杜洋工作室/洋桃电子
程序名：	超级终端显示日历程序
编写人：	杜洋	
编写时间：	2018年1月21日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "usart.h"
#include "rtc.h"

int main (void){//主程序
	u8 bya;
	RCC_Configuration(); //系统时钟初始化
	RTC_Config(); //实时时钟初始化
	LED_Init();//LED初始化
	KEY_Init();//按键初始化
	BUZZER_Init();//蜂鸣器初始化
	USART1_Init(115200); //串口初始化，参数中写波特率
	USART1_RX_STA=0xC000; //初始值设为有回车的状态，即显示一次欢迎词
	while(1)
	{
		if(USART1_RX_STA&0xC000){ //如果标志位是0xC000表示收到数据串完成，可以处理。
			if((USART1_RX_STA&0x3FFF)==0){ //单独的回车键再显示一次欢迎词
				if(RTC_Get()==0){ //读出时间值，同时判断返回值是不是0，非0时读取的值是错误的。
					printf(" 洋桃开发板STM32实时时钟测试程序   \r\n");
					printf(" 现在实时时间：%d-%d-%d %d:%d:%d  ",ryear,rmon,rday,rhour,rmin,rsec);//显示日期时间
					if(rweek==0)printf("星期日   \r\n");//rweek值为0时表示星期日
					if(rweek==1)printf("星期一   \r\n");
					if(rweek==2)printf("星期二   \r\n");
					if(rweek==3)printf("星期三   \r\n");
					if(rweek==4)printf("星期四   \r\n");
					if(rweek==5)printf("星期五   \r\n");
					if(rweek==6)printf("星期六   \r\n");
					printf(" 单按回车键更新时间。输入字母C初始化时钟 \r\n");
					printf(" 请输入设置时间，格式20170806120000，按回车键确定！ \r\n");
				}else{
					printf("读取失败！\r\n");
				}
			}else if((USART1_RX_STA&0x3FFF)==1){ //判断数据是不是2个
				if(USART1_RX_BUF[0]=='c' || USART1_RX_BUF[0]=='C'){
					RTC_First_Config(); //键盘输入c或C，初始化时钟
					BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);//配置完成后，向后备寄存器中写特殊字符0xA5A5
					printf("初始化成功！      \r\n");//显示初始化成功
				}else{
					printf("指令错误！          \r\n"); //显示指令错误！
				} 
			}else if((USART1_RX_STA&0x3FFF)==14){ //判断数据是不是14个
				//将超级终端发过来的数据换算并写入RTC
				ryear = (USART1_RX_BUF[0]-0x30)*1000+(USART1_RX_BUF[1]-0x30)*100+(USART1_RX_BUF[2]-0x30)*10+USART1_RX_BUF[3]-0x30;
				rmon = (USART1_RX_BUF[4]-0x30)*10+USART1_RX_BUF[5]-0x30;//串口发来的是字符，减0x30后才能得到十进制0~9的数据
				rday = (USART1_RX_BUF[6]-0x30)*10+USART1_RX_BUF[7]-0x30;
				rhour = (USART1_RX_BUF[8]-0x30)*10+USART1_RX_BUF[9]-0x30;
				rmin = (USART1_RX_BUF[10]-0x30)*10+USART1_RX_BUF[11]-0x30;
				rsec = (USART1_RX_BUF[12]-0x30)*10+USART1_RX_BUF[13]-0x30;
				bya=RTC_Set(ryear,rmon,rday,rhour,rmin,rsec); //将数据写入RTC计算器的程序
				if(bya==0)printf("写入成功！      \r\n");//显示写入成功 
				else printf("写入失败！       \r\n"); //显示写入失败
			}else{ //如果以上都不是，即是错误的指令。
				printf("指令错误！          \r\n"); //如果不是以上正确的操作，显示指令错误！
			}
			USART1_RX_STA=0; //将串口数据标志位清0
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



