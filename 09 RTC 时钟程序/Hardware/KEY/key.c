

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



#include "key.h"

void KEY_Init(void){ //΢�����صĽӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = KEY1 | KEY2; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������       
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(KEYPORT,&GPIO_InitStructure);			
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
