
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
1-201708271933 ����������ʱ������


*/


#include "sys.h"
#include "usart.h"	  	 
//���ʹ��ucos,����������ͷ�ļ�����.
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x){ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f){      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib����*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
   //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ��� 
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//����ENABLE/�ر�DISABLE�ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}

void USART1_IRQHandler(void){ //����1�жϷ�����򣨹̶��ĺ����������޸ģ�	
	u8 Res;
	//�������ַ������յ�USART_RX_BUF[]�ĳ���(USART_RX_STA&0x3FFF)�����ݵĳ��ȣ��������س���
	//��(USART_RX_STA&0xC000)Ϊ��ʱ��ʾ���ݽ�����ɣ��������ն��ﰴ�»س�����
	//����������д�ж�if(USART_RX_STA&0xC000)��Ȼ���USART_RX_BUF[]���飬����0x0d 0x0a���ǽ�����
	//ע���������������괮�����ݺ�Ҫ��USART_RX_STA��0
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)		
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		printf("%c",Res); //���յ��������� a���ű��� ���ͻص���		
		if((USART_RX_STA&0x8000)==0){//����δ���			
			if(USART_RX_STA&0x4000){//���յ���0x0d				
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
			}else{ //��û�յ�0X0D					
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ; //���յ������ݷ�������
					USART_RX_STA++;	//���ݳ��ȼ�����1
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
	} 
} 
#endif	

/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/

/*
a���ŵ����ã�

%d ʮ�����з�������
%u ʮ�����޷�������
%f ������
%s �ַ���
%c �����ַ�
%p ָ���ֵ
%e ָ����ʽ�ĸ�����
%x, %X �޷�����ʮ�����Ʊ�ʾ������
%o �޷����԰˽��Ʊ�ʾ������
%g �Զ�ѡ����ʵı�ʾ��
%p �����ַ��

*/






