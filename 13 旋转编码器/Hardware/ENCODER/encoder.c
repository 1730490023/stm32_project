

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
1-201709052329 ������


*/



#include "encoder.h"


u8 KUP;//��ť������־��1Ϊ������
u16 cou;

void ENCODER_Init(void){ //�ӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = ENCODER_L | ENCODER_D; //ѡ��˿ں�                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������       
	GPIO_Init(ENCODER_PORT_A,&GPIO_InitStructure);	

    GPIO_InitStructure.GPIO_Pin = ENCODER_R; //ѡ��˿ں�                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������       
	GPIO_Init(ENCODER_PORT_B,&GPIO_InitStructure);				
}

u8 ENCODER_READ(void){ //�ӿڳ�ʼ��
	u8 a;//��Ű�����ֵ
	u8 kt;
	a=0;
	if(GPIO_ReadInputDataBit(ENCODER_PORT_A,ENCODER_L))KUP=0;	//�ж���ť�Ƿ�������
	if(!GPIO_ReadInputDataBit(ENCODER_PORT_A,ENCODER_L)&&KUP==0){ //�ж��Ƿ���ת��ť��ͬʱ�ж��Ƿ�����ť����
		delay_us(100);
		kt=GPIO_ReadInputDataBit(ENCODER_PORT_B,ENCODER_R);	//����ť��һ�˵�ƽ״̬��¼
		delay_ms(3); //��ʱ
		if(!GPIO_ReadInputDataBit(ENCODER_PORT_A,ENCODER_L)){ //ȥ��
			if(kt==0){ //����һ���ж��������ת
				a=1;//��ת
			}else{
				a=2;//��ת
			}
			cou=0; //��ʼ�����жϼ�����
			while(!GPIO_ReadInputDataBit(ENCODER_PORT_A,ENCODER_L)&&cou<60000){ //�ȴ��ſ���ť��ͬʱ�ۼ��ж�����
				cou++;KUP=1;delay_us(20); //
			}
		}
	}
	if(!GPIO_ReadInputDataBit(ENCODER_PORT_A,ENCODER_D)&&KUP==0){ //�ж���ť�Ƿ���  
		delay_ms(20);
		if(!GPIO_ReadInputDataBit(ENCODER_PORT_A,ENCODER_D)){ //ȥ����
			a=3;//�ڰ�������ʱ���ϰ�����״ֵ̬
			//while(ENCODER_D==0);	�ȵ���ť�ſ�
		}
	}
	return a;
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
