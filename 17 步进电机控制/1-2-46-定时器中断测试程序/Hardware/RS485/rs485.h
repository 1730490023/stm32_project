#ifndef __RS485_H
#define __RS485_H	 
#include "sys.h"

#define RS485PORT	GPIOA	//����IO�ӿ�
#define RS485_RE	GPIO_Pin_8	//����IO�ӿ�



void RS485_Init(void);//��ʼ��
void RS485_printf (char *fmt, ...); //RS485����
		 				    
#endif
