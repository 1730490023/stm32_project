/*********************************************************************************************
��������	�����ն˴��ڿ��Ƴ���
��д�ˣ�	����	
��дʱ�䣺	2018��1��13��
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  

*********************************************************************************************/
#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "usart.h"


int main (void){//������
	RCC_Configuration();
	LED_Init();//LED��ʼ��
	KEY_Init();//������ʼ��
	BUZZER_Init();//��������ʼ��
	USART1_Init(115200); //���ڳ�ʼ����������д������
	USART1_RX_STA=0xC000; //��ʼֵ��Ϊ�лس���״̬������ʾһ�λ�ӭ��
	while(1){
		if(USART1_RX_STA&0xC000){ //�����־λ��0xC000��ʾ�յ����ݴ���ɣ����Դ���
			if((USART1_RX_STA&0x3FFF)==0){ //�����Ļس�������ʾһ�λ�ӭ��
				printf("\033[1;47;33m\r\n"); //������ɫ���ο������ն�ʹ�ã�
				printf(" 1y--��LED1��      1n--��LED1�� \n\r");
				printf(" 2y--��LED2��      2n--��LED2�� \r\n");
				printf(" ���������ָ����س���ִ�У� \033[0m\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='1' && USART1_RX_BUF[1]=='y'){ //�ж������ǲ���2������һ�������ǲ��ǡ�1�����ڶ����ǲ��ǡ�y��
				GPIO_SetBits(LEDPORT,LED1); //LED�ƶ�Ϊ�ߵ�ƽ��1��
				printf("1y -- LED1���Ѿ�������\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='1' && USART1_RX_BUF[1]=='n'){
				GPIO_ResetBits(LEDPORT,LED1); ////LED�ƶ�Ϊ�͵�ƽ��0��
				printf("1n -- LED1���Ѿ�Ϩ��\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='2' && USART1_RX_BUF[1]=='y'){
				GPIO_SetBits(LEDPORT,LED2); //LED�ƶ�Ϊ�ߵ�ƽ��1��
				printf("2y -- LED2���Ѿ�������\r\n");
			}else if((USART1_RX_STA&0x3FFF)==2 && USART1_RX_BUF[0]=='2' && USART1_RX_BUF[1]=='n'){
				GPIO_ResetBits(LEDPORT,LED2); ////LED�ƶ�Ϊ�͵�ƽ��0��
				printf("2n -- LED2���Ѿ�Ϩ��\r\n");
			}else{ //������϶����ǣ����Ǵ����ָ�
				printf("ָ�����\r\n"); 
			}
			USART1_RX_STA=0; //���������ݱ�־λ��0
		}
	}
}

/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/
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



