#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//#define LED1 PBout(0)// PB0
//#define LED2 PBout(1)// PB1	
#define LEDPORT	GPIOB	//����IO�ӿ�
#define Setp1	GPIO_Pin_13	//����IO�ӿ�
#define Dir1	GPIO_Pin_12	//����IO�ӿ�
 
#define Setp2	GPIO_Pin_10	//����IO�ӿ�
#define Dir2	GPIO_Pin_11	//����IO�ӿ�



void LED_Init(void);//��ʼ��
	 				    
#endif
