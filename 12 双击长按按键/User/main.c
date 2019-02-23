/*********************************************************************************************
��������	����˫���ͳ�������
��д�ˣ�	����	
��дʱ�䣺	2018��1��28��
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  

*********************************************************************************************/
#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "touch_key.h"

#define KEYA_SPEED1	80	  //������ʱ�䳤�ȣ���λ10mS��
#define KEYA_SPEED2	10	  //˫����ʱ�䳤�ȣ���λ20mS��


int main (void)
{
	u8 a=0,b,c=0;
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ�� 
	LED_Init();          //LED��ʼ��
	TOUCH_KEY_Init();    //������ʼ��
	while(1)
	{
		if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A))   //��ⰴ���Ƿ���
			{
			delay_ms(20); //��ʱȥ����
			if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A)) //�жϳ��̼�
			{
				while((GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A))&& c < KEYA_SPEED1) //ѭ���жϳ�������ʱ��ת
				{
					c++;delay_ms(10); //�����жϵļ�ʱ
				}
				if(c>=KEYA_SPEED1) //��������
				{ 
					//������ִ�еĳ���ŵ��˴�
					GPIO_WriteBit(LEDPORT,LED1|LED2,(BitAction)(0));//LED����
					while(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A));
				}
				else     //��������
				{ 
					for(b=0;b<KEYA_SPEED2;b++) //���˫��
					{
						delay_ms(20);
						if(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A))
						{
							a=1;
							//˫����ִ�еĳ���ŵ��˴�
							GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));//LED����
							while(GPIO_ReadInputDataBit(TOUCH_KEYPORT,TOUCH_KEY_A));
						}
					}
					if(a==0)   //�жϵ���
					{ 
						//������ִ�еĳ���ŵ��˴�
						GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));//LED����
					}
				}
				a=0;c=0; //������0
			}
		} //�����ж��ڴ˽���

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



