

#include "touch_key.h"

void TOUCH_KEY_Init(void)     //΢�����صĽӿڳ�ʼ��
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
    GPIO_InitStructure.GPIO_Pin = TOUCH_KEY_A | TOUCH_KEY_B | TOUCH_KEY_C | TOUCH_KEY_D; //ѡ��˿�                       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //ѡ��IO�ӿڹ�����ʽ //��������     
	GPIO_Init(TOUCH_KEYPORT,&GPIO_InitStructure);			
}
 



/*
ѡ��IO�ӿڹ�����ʽ��
GPIO_Mode_AIN ģ������
GPIO_Mode_IN_FLOATING ��������
GPIO_Mode_IPD ��������
GPIO_Mode_IPU ��������
GPIO_Mode_Out_PP �������
GPIO_Mode_Out_OD ��©���
GPIO_Mode_AF_PP �����������
GPIO_Mode_AF_OD ���ÿ�©���
*/
