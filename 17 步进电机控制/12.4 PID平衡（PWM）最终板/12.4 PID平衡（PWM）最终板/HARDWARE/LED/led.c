#include "led.h"

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LDIR-->PA.7 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.7
	 GPIO_SetBits(GPIOA,GPIO_Pin_7);						 //PA.7 �����
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LSTEP-->PA.7 �˿�����, �������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	 GPIO_SetBits(GPIOA,GPIO_Pin_6); 						 //PE.A ����� 
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //RDIR-->PB.1 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB,1
	 GPIO_SetBits(GPIOB,GPIO_Pin_1);						 //PB.1 �����
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //RSTEP-->PB.0 �˿�����
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB,0
	 GPIO_SetBits(GPIOB,GPIO_Pin_6);	

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //RDIR-->PB.1 �˿�����
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB,1
		


	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->PC.6 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.6
	 GPIO_SetBits(GPIOC,GPIO_Pin_6);						 //PC.6 �����

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //LED1-->PC.7 �˿�����, �������
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	 GPIO_SetBits(GPIOC,GPIO_Pin_7); 						 //PE.C ����� 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //LED2-->PC.13 �˿�����, �������
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	 GPIO_SetBits(GPIOC,GPIO_Pin_13); 						 //PC.13 ����� 
}
 