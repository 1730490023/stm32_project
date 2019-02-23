#include "led.h"

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LDIR-->PA.7 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.7
	 GPIO_SetBits(GPIOA,GPIO_Pin_7);						 //PA.7 输出高
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LSTEP-->PA.7 端口配置, 推挽输出
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOA,GPIO_Pin_6); 						 //PE.A 输出高 
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //RDIR-->PB.1 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB,1
	 GPIO_SetBits(GPIOB,GPIO_Pin_1);						 //PB.1 输出高
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //RSTEP-->PB.0 端口配置
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB,0
	 GPIO_SetBits(GPIOB,GPIO_Pin_6);	

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //RDIR-->PB.1 端口配置
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB,1
		


	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->PC.6 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.6
	 GPIO_SetBits(GPIOC,GPIO_Pin_6);						 //PC.6 输出高

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //LED1-->PC.7 端口配置, 推挽输出
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOC,GPIO_Pin_7); 						 //PE.C 输出高 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //LED2-->PC.13 端口配置, 推挽输出
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOC,GPIO_Pin_13); 						 //PC.13 输出高 
}
 