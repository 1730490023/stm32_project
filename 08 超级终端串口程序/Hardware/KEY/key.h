#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

//#define KEY1 PAin(0)// PA0
//#define KEY2 PAin(1)// PA1

#define KEYPORT	GPIOA	//����IO�ӿ���
#define KEY1	GPIO_Pin_0	//����IO�ӿ�
#define KEY2	GPIO_Pin_1	//����IO�ӿ�


void KEY_Init(void);//��ʼ��

		 				    
#endif
