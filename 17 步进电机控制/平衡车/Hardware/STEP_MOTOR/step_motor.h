#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H	 
#include "sys.h"
#include "delay.h"

extern u8 STEP; //���嵥������ ȫ�ֱ���

#define STEP_MOTOR_PORT	GPIOB	//����IO�ӿ�������
#define STEP_MOTOR_A	GPIO_Pin_3	//����IO�ӿ�
#define STEP_MOTOR_B	GPIO_Pin_4	//����IO�ӿ�
#define STEP_MOTOR_C	GPIO_Pin_8	//����IO�ӿ�
#define STEP_MOTOR_D	GPIO_Pin_9	//����IO�ӿ�



void STEP_MOTOR_Init(void);//��ʼ��
void STEP_MOTOR_OFF (void);//�ϵ�״̬
void STEP_MOTOR_8A (u8 a,u16 speed);
void STEP_MOTOR_NUM (u8 RL,u16 num,u8 speed);//�������������
void STEP_MOTOR_LOOP (u8 RL,u8 LOOP,u8 speed);//�����Ȧ������


		 				    
#endif
