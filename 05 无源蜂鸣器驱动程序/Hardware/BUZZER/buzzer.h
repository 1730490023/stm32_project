#ifndef __BUZZER_H
#define __BUZZER_H	 
#include "sys.h"

#define BUZZERPORT	GPIOB	//����IO�ӿ�
#define BUZZER	GPIO_Pin_5	//����IO�ӿ�



void BUZZER_Init(void);//��ʼ��
void BUZZER_BEEP1(void);//��һ��

		 				    
#endif
