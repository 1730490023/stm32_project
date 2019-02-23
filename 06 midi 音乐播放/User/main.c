/*********************************************************************************************
��������	MIDI���ֲ��ų���
��дʱ�䣺	2017��12��30��
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  

*********************************************************************************************/
#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h" 
#include "flash.h" 

#include "buzzer.h"

#define FLASH_START_ADDR  0x0801f000	  //д�����ʼ��ַ


int main (void){//������
	u16 a; //�������
	//��ʼ������
	RCC_Configuration(); //ʱ������
	LED_Init();//LED��ʼ��
	KEY_Init();//������ʼ��

	BUZZER_Init();//��������ʼ��
//	BUZZER_BEEP1();//��������1
	MIDI_PLAY(); //����MIDI����

    a = FLASH_R(FLASH_START_ADDR);//��ָ��ҳ�ĵ�ַ��FLASH
	GPIO_Write(LEDPORT,a|0xfffc&GPIO_ReadOutputData(LEDPORT)); //ֱ����ֵ����������ֵд��LED��LED��GPIOB���PB0��PB1�ϣ�


	//��ѭ��
	while(1){

		//ʾ��4��������
		if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){ //�������ӿڵĵ�ƽ
			delay_ms(20); //��ʱ20msȥ����
			if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){ //�������ӿڵĵ�ƽ
				//��2��LED����ʾ�����Ƽӷ�
				a++; //������1
				if(a>3){ //����������3ʱ��0
					a=0; 
				}
				GPIO_Write(LEDPORT,a|0xfffc&GPIO_ReadOutputData(LEDPORT)); //ֱ����ֵ����������ֵд��LED��LED��GPIOB���PB0��PB1�ϣ�
			
				BUZZER_BEEP1();//��������1

				FLASH_W(FLASH_START_ADDR,a); //��ָ��ҳ�ĵ�ַд��FLASH
				while(!GPIO_ReadInputDataBit(KEYPORT,KEY1)); //�ȴ������ɿ� 
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



