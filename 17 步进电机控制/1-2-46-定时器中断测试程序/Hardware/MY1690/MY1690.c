

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
1-20170919 ������


*/




#include "MY1690.h"

void MY1690_Init(void){ //��ʼ��
	USART3_Init(9600);//����3��ʼ��������
	MY1690_STOP(); //�ϵ��ʼ������һ��ָ���MP3оƬ
}
void MY1690_PLAY(void){ //����
	USART3_printf("\x7e\x03\x11\x12\xef"); //���� \x ���ʮ����������
}
void MY1690_PAUSE(void){ //��ͣ
	USART3_printf("\x7e\x03\x12\x11\xef");
}
void MY1690_PREV(void){ //��һ��
	USART3_printf("\x7e\x03\x14\x17\xef");
}
void MY1690_NEXT(void){ //��һ��
	USART3_printf("\x7e\x03\x13\x10\xef");
}
void MY1690_VUP(void){ //������1
	USART3_printf("\x7e\x03\x15\x16\xef");
}
void MY1690_VDOWN(void){ //������1
	USART3_printf("\x7e\x03\x16\x15\xef");
}
void MY1690_STOP(void){ //ֹͣ
	USART3_printf("\x7e\x03\x1E\x1D\xef");
}

void MY1690_CMD1(u8 a){	//�޲�����ָ���  a������
	u8 i;
	i=3^a;//ȡУ���루���
	USART_SendData(USART3 , 0x7e);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , 0x03);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , a);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , i);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , 0xef);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
}
void MY1690_CMD2(u8 a,u8 b){ //�в�����ָ��� a������ b����
	u8 i;
	i=4^a;//ȡУ���루���
	i=i^b;//ȡУ���루���
	USART_SendData(USART3 , 0x7e);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , 0x04);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , a);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , b);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , i);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , 0xef);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
}
void MY1690_CMD3(u8 a,u16 b){ //�в�����ָ��� a������ b������16λ��
	u8 i,c,d;
	c=b/0x100; //��16λ�����ֳ�2��8λ����
	d=b%0x100;
	i=5^a;//ȡУ���루���
	i=i^c;//ȡУ���루���
	i=i^d;//ȡУ���루���
	USART_SendData(USART3 , 0x7e);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , 0x05);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , a);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , c);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , d);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , i);		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
	USART_SendData(USART3 , 0xef);	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET); //��鷢���жϱ�־λ
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
