/*********************************************************************************************
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  

*********************************************************************************************/
#include "stm32f10x.h"    //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "led.h"


int main (void)      //������
{
	RCC_Configuration(); //ʱ������
	LED_Init();
	while(1)
		{
		
		//����1��
		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED1�ӿ�����ߵ�ƽ1
		delay_us(50000); //��ʱ1��
		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0)); //LED1�ӿ�����͵�ƽ0
		delay_us(50000); //��ʱ1��
		
		//����2��
//		GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1-GPIO_ReadOutputDataBit(LEDPORT,LED1))); //ȡ��LED1
//		delay_ms(500); //��ʱ1��

		//����3��
//		GPIO_SetBits(LEDPORT,LED1); //LED�ƶ�Ϊ�ߵ�ƽ��1��
//		delay_s(1); //��ʱ1��
//		GPIO_ResetBits(LEDPORT,LED1); //LED�ƶ�Ϊ�͵�ƽ��0��
//		delay_s(1); //��ʱ1��

		//����4
//		GPIO_Write(LEDPORT,0x0001); //ֱ����ֵ����������ֵд��LED
//		delay_s(2); //��ʱ1��
//		GPIO_Write(LEDPORT,0x0000); //ֱ����ֵ����������ֵд��LED
//		delay_s(2); //��ʱ1��

	  }
}




/*

����������˵˵����
u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8      a; //����8λ�޷��ű���a
vu32    a; //�����ױ��32λ�޷��ű���a
vu16    a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32    a; //����ֻ����32λ�޷��ű���a
uc16    a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

#define ONE  1   //�궨��

delay_us(1); //��ʱ1΢��
delay_ms(1); //��ʱ1����
delay_s(1); //��ʱ1��

*/



