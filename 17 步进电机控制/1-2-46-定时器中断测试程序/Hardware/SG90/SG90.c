

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
1- ������


*/




#include "SG90.h"

void SG90_Init(void){ //����ӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = SE_OUT; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(SE_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(0)); //�ӿ����
}

void SG90_angle(u8 a){ //����Ƕȿ������ã�����ֵ0��180����Ӧ�Ƕ�0��180��
	u8 b=100;//�Ƕ�У��ƫ����
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(1)); //�ӿ����
	delay_us(500+a*10+b); //��ʱ
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(0)); //�ӿ����
	delay_us(19500-a*10-b); //��ʱ
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
