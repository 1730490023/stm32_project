#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//#define LED1 PBout(0)// PB0
//#define LED2 PBout(1)// PB1	
#define LEDPORT	GPIOB	//����IO�ӿ�
#define LED1	GPIO_Pin_0	//����IO�ӿ�
#define LED2	GPIO_Pin_1	//����IO�ӿ�



void LED_Init(void);//��ʼ��

		 				    
#endif
