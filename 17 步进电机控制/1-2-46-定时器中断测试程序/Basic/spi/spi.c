

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



#include "spi.h"


void SPI2_Init(void){ //SPI2��ʼ��
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);//ʹ��SPI_2ʱ��

	GPIO_InitStructure.GPIO_Pin = SPI2_MISO;  //SPI2��MISO��PB14��Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI2PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI2_MOSI | SPI2_SCK;	//SPI2��MOSI��PB15����SCLK��PB13��Ϊ�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI2PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI2_NSS;	 //SPI2��NSS��PB12��Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SPI2PORT,&GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//˫���������ȫ˫��ģʽ
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//����ΪSPI������ģʽ��SCK��������ʱ�ӣ�
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//SPI���ݴ�С������8λ֡���ݽṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//����״̬ʱSCK��״̬��HighΪ�ߵ�ƽ��LowΪ�͵�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//ʱ����λ��1��ʾ��SCK�������ر߲�����2��ʾż���ر߲���
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS������ؼ�Ƭѡ
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//ʱ�ӵ�Ԥ��Ƶֵ��0~256��
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //MSB��λ��ǰ
	SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC����͵Ķ���ʽ
	SPI_Init(SPI2,&SPI_InitStructure); //��ʼ��SPI2��������
	SPI_Cmd(SPI2,ENABLE); //ʹ��SPI2  
}

//SPI2���ݷ�+�ճ�����Ҫ���ڷ��ͣ�
u8 SPI2_SendByte(u8 Byte){ //ͨ��SPI2�ڷ���1�����ݣ�ͬʱ����1������
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET); //������ͼĴ�������û�з����꣬ѭ���ȴ�
	SPI_I2S_SendData(SPI2,Byte);  //�����ͼĴ���д��Ҫ���͵�����
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET); //������ܼĴ���û���յ����ݣ�ѭ��
	return SPI_I2S_ReceiveData(SPI2);
}

 
/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/


/*
Ӧ�õķ�����

SPI_SendByte(a); //����һ���ֽ����ݣ�a��һ������������ֵ


*/
