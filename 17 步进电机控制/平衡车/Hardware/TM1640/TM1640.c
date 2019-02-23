

/*
//�������ҳ�Ʒ
//����ϵ�п�����Ӧ�ó���
//��ע΢�Ź��ںţ����ҵ���
//���ҿ������������� www.DoYoung.net/YT 
//������ѿ����н�ѧ��Ƶ�����ؼ������ϣ�������������
//�������ݾ��� ����������ҳ www.doyoung.net
*/

/*
TM1640���������оƬ

���޸���־��
1-201708311855 ������


*/

#include "TM1640.h"
#include "delay.h"

#define DEL  1   //�궨�� ͨ�����ʣ�Ĭ��Ϊ1���粻��ͨ�ſɼӴ���ֵ��

//��ַģʽ������
//#define TM1640MEDO_ADD  0x40   //�궨��	�Զ���һģʽ
#define TM1640MEDO_ADD  0x44   //�궨�� �̶���ַģʽ���Ƽ���

//��ʾ���ȵ�����
//#define TM1640MEDO_DISPLAY  0x88   //�궨�� ����  ��С
//#define TM1640MEDO_DISPLAY  0x89   //�궨�� ����
//#define TM1640MEDO_DISPLAY  0x8a   //�궨�� ����
//#define TM1640MEDO_DISPLAY  0x8b   //�궨�� ����
#define TM1640MEDO_DISPLAY  0x8c   //�궨�� ���ȣ��Ƽ���
//#define TM1640MEDO_DISPLAY  0x8d   //�궨�� ����
//#define TM1640MEDO_DISPLAY  0x8f   //�궨�� ���� ���

#define TM1640MEDO_DISPLAY_OFF  0x80   //�궨�� ���� ��



void TM1640_start(){ //ͨ��ʱ�� ��ʼ������GPIO���������Ͳ㣩
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(1)); //�ӿ�����ߵ�ƽ1	
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(1)); //�ӿ�����ߵ�ƽ1	
	delay_us(DEL);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0)); //�ӿ����0	
	delay_us(DEL);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(0)); //�ӿ����0	
	delay_us(DEL);
}
void TM1640_stop(){ //ͨ��ʱ�� ����������GPIO���������Ͳ㣩
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0)); //�ӿ����0	
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(1)); //�ӿ�����ߵ�ƽ1	
	delay_us(DEL);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(1)); //�ӿ�����ߵ�ƽ1	
	delay_us(DEL);
}
void TM1640_write(u8 date){	//д���ݣ��Ͳ㣩
	u8 i;
	u8 aa;
	aa=date;
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0)); //�ӿ����0	
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(0)); //�ӿ����0	
	for(i=0;i<8;i++){
		GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(0)); //�ӿ����0	
		delay_us(DEL);

		if(aa&0x01){
			GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(1)); //�ӿ�����ߵ�ƽ1	
			delay_us(DEL);
		}else{
			GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0)); //�ӿ����0	
			delay_us(DEL);
		}
		GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(1)); //�ӿ�����ߵ�ƽ1	
		delay_us(DEL);
		aa=aa>>1;
   }
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0)); //�ӿ����0	
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(0)); //�ӿ����0	
}

void TM1640_Init(void){ //TM1640�ӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = TM1640_DIN | TM1640_SCLK; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(TM1640_GPIOPORT, &GPIO_InitStructure);

	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(1)); //�ӿ�����ߵ�ƽ1	
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(1)); //�ӿ�����ߵ�ƽ1	
	TM1640_start();
	TM1640_write(TM1640MEDO_ADD); //�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	TM1640_stop();
	TM1640_start();
	TM1640_write(TM1640MEDO_DISPLAY); //������ʾ������ʾ��0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f�ֱ��Ӧ������Ϊ:
					 				  //------------------1/16,  2/16,  4/16,  10/16, 11/16, 12/16, 13/16, 14/16	 //0x80����ʾ
	TM1640_stop();	
				
}
void TM1640_led(u8 date){ //�̶���ַģʽ����ʾ���8��LED����
   TM1640_start();
   TM1640_write(TM1640_LEDPORT);	        //����ʾ���ݶ�Ӧ�ĵ�ַ
   TM1640_write(date);	//��1BYTE��ʾ����
   TM1640_stop();
}
void TM1640_display(u8 address,u8 date){ //�̶���ַģʽ����ʾ���
 	const u8 buff[21]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x00};//����0~9��0~9�ӵ���ʾ�����
    //---------------   0    1    2    3    4    5    6    7    8    9    0.   1.   2.   3.   4.   5.   6.   7.   8.   9.   ��   
   TM1640_start();
   TM1640_write(0xC0+address);	         //����ʾ���ݶ�Ӧ�ĵ�ַ
   TM1640_write(buff[date]);				 //��1BYTE��ʾ����
   TM1640_stop();
}
void TM1640_display_add(u8 address,u8 date){	//��ַ�Զ���һģʽ����ʾ��� 
	u8 i;
 	const u8 buff[21]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x00};//����0~9��0~9�ӵ���ʾ�����
    //---------------   0    1    2    3    4    5    6    7    8    9    0.   1.   2.   3.   4.   5.   6.   7.   8.   9.   ��   
  TM1640_start();
   TM1640_write(0xC0+address);	         //������ʼ��ַ
   for(i=0;i<16;i++){
      TM1640_write(buff[date]); 
   }
   TM1640_stop(); 
}


/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/


