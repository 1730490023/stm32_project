

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



#include "iwdg.h"


void IWDG_Init(void){ //��ʼ���������Ź�
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
    IWDG_SetPrescaler(pre); //����IWDGԤ��Ƶֵ
    IWDG_SetReload(rlr); //����IWDG��װ��ֵ
    IWDG_ReloadCounter(); //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
    IWDG_Enable(); //ʹ��IWDG
}

void IWDG_Feed(void){ //ι������
    IWDG_ReloadCounter();//�̼����ι������
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
