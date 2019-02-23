

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



#include "dht11.h"


void DHT11_IO_OUT (void){ //�˿ڱ�Ϊ���
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    GPIO_InitStructure.GPIO_Pin = DHT11_IO; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(DHT11PORT, &GPIO_InitStructure);
}

void DHT11_IO_IN (void){ //�˿ڱ�Ϊ����
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    GPIO_InitStructure.GPIO_Pin = DHT11_IO; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ       
	GPIO_Init(DHT11PORT, &GPIO_InitStructure);
}

void DHT11_RST (void){ //DHT11�˿ڸ�λ��������ʼ�źţ�IO���ͣ�
	DHT11_IO_OUT();
	GPIO_ResetBits(DHT11PORT,DHT11_IO); //	
	delay_ms(20); //��������18ms						
	GPIO_SetBits(DHT11PORT,DHT11_IO); //							
	delay_us(30); //��������20~40us
}

u8 Dht11_Check(void){ //�ȴ�DHT11��Ӧ������1:δ��⵽DHT11������0:�ɹ���IO���գ�	   
    u8 retry=0;
    DHT11_IO_IN();//IO������״̬	 
    while (GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO)&&retry<100){//DHT11������40~80us
        retry++;
        delay_us(1);
    }	 
    if(retry>=100)return 1; else retry=0;
    while (!GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO)&&retry<100){//DHT11���ͺ���ٴ�����40~80us
        retry++;
        delay_us(1);
    }
    if(retry>=100)return 1;	    
    return 0;
}

u8 Dht11_ReadBit(void){ //��DHT11��ȡһ��λ ����ֵ��1/0
    u8 retry=0;
    while(GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO)&&retry<100){//�ȴ���Ϊ�͵�ƽ
        retry++;
        delay_us(1);
    }
    retry=0;
    while(!GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO)&&retry<100){//�ȴ���ߵ�ƽ
        retry++;
        delay_us(1);
    }
    delay_us(40);//�ȴ�40us	//�����жϸߵ͵�ƽ��������1��0
    if(GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO))return 1; else return 0;		   
}

u8 Dht11_ReadByte(void){  //��DHT11��ȡһ���ֽ�  ����ֵ������������
    u8 i,dat;
    dat=0;
    for (i=0;i<8;i++){ 
        dat<<=1; 
        dat|=Dht11_ReadBit();
    }						    
    return dat;
}

u8 DHT11_Init (void){	//DHT11��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE); //APB2����ʱ��ʹ��      
	DHT11_RST();//DHT11�˿ڸ�λ��������ʼ�ź�
	return Dht11_Check(); //�ȴ�DHT11��Ӧ
}

u8 DHT11_ReadData(u8 *h){ //��ȡһ������//ʪ��ֵ(ʮ���ƣ���Χ:20%~90%) ���¶�ֵ(ʮ���ƣ���Χ:0~50��)������ֵ��0,����;1,ʧ�� 
    u8 buf[5];
    u8 i;
    DHT11_RST();//DHT11�˿ڸ�λ��������ʼ�ź�
    if(Dht11_Check()==0){ //�ȴ�DHT11��Ӧ
        for(i=0;i<5;i++){//��ȡ5λ����
            buf[i]=Dht11_ReadByte(); //��������
        }
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4]){	//����У��
            *h=buf[0]; //��ʪ��ֵ����ָ��1
			h++;
            *h=buf[2]; //���¶�ֵ����ָ��2
        }
    }else return 1;
    return 0;	    
}
 
/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/
