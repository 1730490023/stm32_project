/*********************************************************************************************
��������	LED�����Ƴ���
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  

*********************************************************************************************/
#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "led.h"

int main (void)     //������
	{
	//������Ҫ�ı���
	u8 MENU;
	u16 t,i;
	//��ʼ������
	RCC_Configuration(); //ʱ������
	LED_Init();
	//���ñ����ĳ�ʼֵ
	MENU = 0;
	t = 1;
	//��ѭ��
	while(1){
		//�˵�0
		if(MENU == 0)       //����ѭ��
			{ 
			for(i = 0; i < 10; i++)
				{
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED1�ӿ�����ߵ�ƽ1
				delay_us(t); //��ʱ
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED1�ӿ�����͵�ƽ0
				delay_us(501-t); //��ʱ
			  }
			  t++;
			  if(t==500)
				{
				MENU = 1;
			  }
		}
		//�˵�1
		if(MENU == 1)     //�䰵ѭ��
			{
			for(i = 0; i < 10; i++)
				{
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED1�ӿ�����ߵ�ƽ1
				delay_us(t); //��ʱ
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED1�ӿ�����͵�ƽ0
				delay_us(501-t); //��ʱ
		   	}
			 t--;
			 if(t==1)
				 {
			  	MENU = 0;
			   }
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

*/



