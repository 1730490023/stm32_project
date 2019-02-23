#ifndef __TM1640_H
#define __TM1640_H	 
#include "sys.h"

#define TM1640_GPIOPORT	GPIOA	//����IO�ӿ�
#define TM1640_DIN	GPIO_Pin_12	//����IO�ӿ�
#define TM1640_SCLK	GPIO_Pin_11	//����IO�ӿ�

#define TM1640_LEDPORT	0xC8	//����IO�ӿ�


void TM1640_Init(void);//��ʼ��
void TM1640_led(u8 date);//
void TM1640_display(u8 address,u8 date);//
void TM1640_display_add(u8 address,u8 date);//

		 				    
#endif
