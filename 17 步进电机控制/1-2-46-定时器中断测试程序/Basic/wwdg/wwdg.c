

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
1-201708202309 ������


*/



#include "wwdg.h"


void WWDG_Init(void){ //��ʼ�����ڿ��Ź�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); // WWDG ʱ��ʹ��
	WWDG_SetPrescaler(fprer); //���� IWDG Ԥ��Ƶֵ
	WWDG_SetWindowValue(wr); //���ô���ֵ
	WWDG_Enable(WWDG_CNT); //ʹ�ܿ��Ź�,���� counter
	WWDG_ClearFlag(); //�����ǰ�����жϱ�־λ
	WWDG_NVIC_Init(); //��ʼ�����ڿ��Ź� NVIC
	WWDG_EnableIT(); //�������ڿ��Ź��ж�
}

void WWDG_NVIC_Init(void){ //���ڿ��Ź��жϷ�����򣨱�WWDG_Init���ã�
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn; //WWDG �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ 2 �����ȼ� 3 �� 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //��ռ 2,�����ȼ� 3,�� 2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure); //NVIC ��ʼ��
}

void WWDG_Feed(void){ //����ι������
    WWDG_SetCounter(WWDG_CNT); //�̼����ι������
}

void WWDG_IRQHandler(void){	//���ڿ��Ź��жϴ������
	WWDG_ClearFlag(); //�����ǰ�����жϱ�־λ

	//�˴������ڸ�λǰ��Ҫ����Ĺ����򱣴�����
}
 
/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/


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
