#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"


#define CAN_INT_ENABLE	0	//1 �������жϣ�0 �ؽ����ж�

//����ģʽ�Ͳ�����
//������=(pclk1/((1+8+7)*9)) = 36Mhz/16/9 = 250Kbits�趨��һ��ʱ�䵥λ�ĳ���9
#define tsjw	CAN_SJW_1tq	//������Ŀ��1~4��
#define tbs1	CAN_BS1_8tq	//������Ŀ��1~16��
#define tbs2	CAN_BS2_7tq	//������Ŀ��1~8��
#define brp		9	//������Ŀ



u8 CAN1_Configuration(void);//��ʼ��
u8 CAN_Send_Msg(u8* msg,u8 len);//��������
u8 CAN_Receive_Msg(u8 *buf);//��������
		 				    
#endif
