
/*
//�������ҳ�Ʒ
//����ϵ�п�����Ӧ�ó���
//��ע΢�Ź��ںţ����ҵ���
//���ҿ������������� www.DoYoung.net/YT 
//������ѿ����н�ѧ��Ƶ�����ؼ������ϣ�������������
//�������ݾ��� ����������ҳ www.doyoung.net
*/

/*
���޸���־��
1-201708202312 ������


*/

#include "NVIC.h"

u8 INT_MARK;//�жϱ�־λ

void KEY_INT_INIT (void){	 //�����жϳ�ʼ��
	NVIC_InitTypeDef  NVIC_InitStruct;	//����ṹ�����
	EXTI_InitTypeDef  EXTI_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //����GPIOʱ�� ����Ҫ�븴��ʱ��һͬ������     
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);//���ö˿��ж���Ҫ���ø���ʱ��

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);  //���� GPIO  �ж�
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;  //�����ж���
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;              //�ж�ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;     //�ж�ģʽΪ �ж�
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;   //�½��ش���
	
	EXTI_Init(& EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;   //�ж���     
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //ʹ���ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;  //��ռ���ȼ� 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;     //�����ȼ�  2
	NVIC_Init(& NVIC_InitStruct);

}

void  EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET){//�ж�ĳ�����ϵ��ж��Ƿ��� 
		INT_MARK=1;//��־λ��1����ʾ�а����ж�
		EXTI_ClearITPendingBit(EXTI_Line0);   //��� LINE �ϵ��жϱ�־λ
	}     
}





