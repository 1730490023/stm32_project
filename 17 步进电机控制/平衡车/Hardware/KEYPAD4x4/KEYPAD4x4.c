

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



#include "KEYPAD4x4.h"

void KEYPAD4x4_Init(void){ //΢�����صĽӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
    GPIO_InitStructure.GPIO_Pin = KEYa | KEYb | KEYc | KEYd; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������       
	GPIO_Init(KEYPAD4x4PORT,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = KEY1 | KEY2 | KEY3 | KEY4; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��     
	GPIO_Init(KEYPAD4x4PORT,&GPIO_InitStructure);

	GPIO_ResetBits(KEYPAD4x4PORT,KEY1|KEY2|KEY3|KEY4);
	GPIO_SetBits(KEYPAD4x4PORT,KEYa|KEYb|KEYc|KEYd);
}
void KEYPAD4x4_Init2(void){ //΢�����صĽӿڳ�ʼ��2������IO������ʽ��ת��
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
    GPIO_InitStructure.GPIO_Pin = KEY1 | KEY2 | KEY3 | KEY4; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������       
	GPIO_Init(KEYPAD4x4PORT,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = KEYa | KEYb | KEYc | KEYd; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ //��������  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��     
	GPIO_Init(KEYPAD4x4PORT,&GPIO_InitStructure);

	GPIO_SetBits(KEYPAD4x4PORT,KEY1|KEY2|KEY3|KEY4);
	GPIO_ResetBits(KEYPAD4x4PORT,KEYa|KEYb|KEYc|KEYd);
}
u8 KEYPAD4x4_Read (void){//���̴�����
	u8 a=0,b=0;//�������
	KEYPAD4x4_Init();//��ʼ��IO
	if(!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEYa) ||  	//��Ѱ���̿ڵ�ֵ�Ƿ�仯
		!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEYb) || 
		!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEYc) || 
		!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEYd)){
		delay_ms (20);//��ʱ20����
		if(!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEYa) ||  	//��Ѱ���̿ڵ�ֵ�Ƿ�仯
			!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEYb) || 
			!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEYc) || 
			!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEYd)){
	  		a = GPIO_ReadInputData(KEYPAD4x4PORT)&0xff;//��ֵ����Ĵ���a
		}
		KEYPAD4x4_Init2();//IO������ʽ��ת
		b = GPIO_ReadInputData(KEYPAD4x4PORT)&0xff;//���ڶ���ȡ��ֵ����Ĵ���b
		a = a|b;//�������������
		switch(a){//�Ա�����ֵ
			case 0xee: b = 16; break;//�Աȵõ��ļ�ֵ��bһ��Ӧ������
			case 0xed: b = 15; break;
			case 0xeb: b = 14; break;
			case 0xe7: b = 13; break;
			case 0xde: b = 12; break;
			case 0xdd: b = 11; break;
			case 0xdb: b = 10; break;
			case 0xd7: b = 9; break;
			case 0xbe: b = 8; break;
			case 0xbd: b = 7; break;
			case 0xbb: b = 6; break;
			case 0xb7: b = 5; break;
			case 0x7e: b = 4; break;
			case 0x7d: b = 3; break;
			case 0x7b: b = 2; break;
			case 0x77: b = 1; break;
			default: b = 0; break;//��ֵ������
		}
		while(!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEY1) ||  	//�ȴ������ſ�
			!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEY2) || 
			!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEY3) || 
			!GPIO_ReadInputDataBit(KEYPAD4x4PORT,KEY4));
		delay_ms (20);//��ʱ20����
	}
return (b);//��b��Ϊ����ֵ
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
