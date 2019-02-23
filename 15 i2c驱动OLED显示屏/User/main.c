/*********************************************************************************************
��������	�¶�ֵOLED����ʾ����
��д�ˣ�	����	
��дʱ�䣺	2018��2��27��
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  
*********************************************************************************************/
#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "lm75a.h"
#include "oled0561.h"

int main (void)
{
	u8 buffer[3];
	delay_ms(100); //�ϵ�ʱ�ȴ�������������
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ�� 

	I2C_Configuration();//I2C��ʼ��
	LM75A_GetTemp(buffer); //��ȡLM75A���¶�����

	OLED0561_Init(); //OLED��ʼ��

	OLED_DISPLAY_8x16_BUFFER(0,"   YoungTalk "); //��ʾ�ַ���
	OLED_DISPLAY_8x16_BUFFER(6,"  Temp:"); //��ʾ�ַ���

	while(1)
	{
		LM75A_GetTemp(buffer); //��ȡLM75A���¶�����
			
		if(buffer[0])OLED_DISPLAY_8x16(6,7*8,'-'); //�����1��Ϊ1���Ǹ��¶�
		OLED_DISPLAY_8x16(6,8*8,buffer[1]/10+0x30);//��ʾ�¶�ֵ
		OLED_DISPLAY_8x16(6,9*8,buffer[1]%10+0x30);//
		OLED_DISPLAY_8x16(6,10*8,'.');//
		OLED_DISPLAY_8x16(6,11*8,buffer[2]/10+0x30);//
		OLED_DISPLAY_8x16(6,12*8,buffer[2]%10+0x30);//
		OLED_DISPLAY_8x16(6,13*8,'C');//

		delay_ms(200); //��ʱ
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



