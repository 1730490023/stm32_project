#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0  PCout(6)	// PC6
#define LED1  PCout(7)	// PC7	
#define LED3  PCout(13)	// PC13	
#define LDIR  PAout(7)	// PA7
#define LSTEP PAout(6)	// PA6
#define RDIR  PBout(1)	// PB1
#define RSTEP PBout(0)	// PB0
#define EN PBout(12)	  // PB12


void LED_Init(void);//��ʼ��

		 				    
#endif
