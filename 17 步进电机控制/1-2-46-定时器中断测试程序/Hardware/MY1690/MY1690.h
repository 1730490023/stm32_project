#ifndef __MY1690_H
#define __MY1690_H	 
#include "sys.h"
#include "usart.h"


void MY1690_Init(void);//��ʼ��

void MY1690_PLAY(void);	//ֱ�������ָ��
void MY1690_PREV(void);
void MY1690_NEXT(void);
void MY1690_PAUSE(void);
void MY1690_VUP(void);
void MY1690_VDOWN(void);
void MY1690_STOP(void);

void MY1690_CMD1(u8 a);	//ȫ��ָ������
void MY1690_CMD2(u8 a,u8 b); 
void MY1690_CMD3(u8 a,u16 b);
		 				    
#endif
