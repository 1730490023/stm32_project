

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





ע�⣺
��������ռ�õ�GPIO�ӿ�PA13��PA14�ϵ��ΪJTAG���ܣ�
��Ҫ��RCC����������AFIOʱ�ӣ�����RELAY_Init��������룺
GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
// �ı�ָ���ܽŵ�ӳ��,��ȫ����JTAG+SW-DP���ܽ�JATG�ӿ��ض���ΪGPIO

*/




#include "relay.h"

void RELAY_Init(void){ //�̵����Ľӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE); //APB2����ʱ��ʹ��      
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//����AFIO��ӳ�书��ʱ��    
    GPIO_InitStructure.GPIO_Pin = RELAY1 | RELAY2; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(RELAYPORT, &GPIO_InitStructure);
	//���뽫����JTAG���ܲ�����GPIOʹ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);// �ı�ָ���ܽŵ�ӳ��,��ȫ����JTAG+SW-DP
	GPIO_ResetBits(RELAYPORT,RELAY1 | RELAY2); //��Ϊ�͵�ƽ��0�� ��ʼΪ�ؼ̵���							
}

void RELAY_1(u8 c){ //�̵����Ŀ��Ƴ���c=0�̵����ſ���c=1�̵������ϣ�
	GPIO_WriteBit(RELAYPORT,RELAY1,(BitAction)(c));//ͨ������ֵд��ӿ�
}
void RELAY_2(u8 c){ //�̵����Ŀ��Ƴ���c=0�̵����ſ���c=1�̵������ϣ�
	GPIO_WriteBit(RELAYPORT,RELAY2,(BitAction)(c));//ͨ������ֵд��ӿ�
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
