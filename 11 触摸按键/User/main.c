/*********************************************************************************************
ģ��������  ��������/���ҵ���
��������	����������������
��д�ˣ�	����	
��дʱ�䣺	2018��1��27��
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  

*********************************************************************************************/
#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h"

int main (void)
{
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ�� 
	LED_Init();//LED��ʼ��
	TOUCH_KEY_Init();//������ʼ��
	while(1)
	{
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A))    //�����������ĵ�ƽ
		{ 
			GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));   //LED����	
		}
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_B))    //�����������ĵ�ƽ
		{ 
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));   //LED����	
		}
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_C))    //�����������ĵ�ƽ
		{
			GPIO_WriteBit(LEDPORT,LED1|LED2,(BitAction)(0));//LED����	
		}
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_D))    //�����������ĵ�ƽ
		{ 
			GPIO_WriteBit(LEDPORT,LED1|LED2,(BitAction)(1));//LED����	
		}
	}
}



/*

���������塿
u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8     a; //����8λ�޷��ű���a
vu32     a; //�����ױ��32λ�޷��ű���a
vu16     a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32     a; //����ֻ����32λ�޷��ű���a
uc16     a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

#define ONE  1   //�궨��

delay_us(1); //��ʱ1΢��
delay_ms(1); //��ʱ1����
delay_s(1); //��ʱ1��

GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED����

*/



