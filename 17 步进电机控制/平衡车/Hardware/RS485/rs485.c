

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


#include "sys.h"
#include "usart.h"
#include "rs485.h"

void RS485_Init(void){ //RS485�ӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    GPIO_InitStructure.GPIO_Pin = RS485_RE; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(RS485PORT, &GPIO_InitStructure);
	GPIO_ResetBits(RS485PORT,RS485_RE); //RE�˿��ƽ���/����״̬��REΪ1ʱ���ͣ�Ϊ0ʱ���ա�
	
}
 
/*
RS485����ͨ�ţ�ʹ��USART3������RS485ר�õ�printf����
���÷�����RS485_printf("123"); //��USART3�����ַ�123
*/
void RS485_printf (char *fmt, ...){ 
	char buffer[USART3_REC_LEN+1];  // ���ݳ���
	u8 i = 0;
	va_list arg_ptr;
	GPIO_SetBits(RS485PORT,RS485_RE); //Ϊ�ߵ�ƽ�����ͣ�//RS485�շ�ѡ����	
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART3_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART3_REC_LEN) && (i < strlen(buffer))){
        USART_SendData(USART3, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET); 
	}
	va_end(arg_ptr);
	GPIO_ResetBits(RS485PORT,RS485_RE); //Ϊ�͵�ƽ�����գ�//RS485�շ�ѡ����	
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
