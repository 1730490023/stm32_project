
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
1-20170903


*/



#include "adc.h"

vu16 ADC_DMA_IN[2]; //ADC��ֵ��ŵı���

void ADC_DMA_Init(void){ //DMA��ʼ������
	DMA_InitTypeDef DMA_InitStructure;//����DMA��ʼ���ṹ��
	DMA_DeInit(DMA1_Channel1);//��λDMAͨ��1
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; //���� DMAͨ���������ַ=ADC1_DR_Address
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_DMA_IN; //!!!����DMAͨ��ADC���ݴ洢��������������ֱ�Ӷ��˱�������ADCֵ��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//ָ������ΪԴ��ַ
	DMA_InitStructure.DMA_BufferSize = 2;//!!!����DMA��������С������ADC�ɼ�ͨ�������޸ģ�
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//��ǰ����Ĵ�����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//!!! ��ǰ�洢����ַ��Disable���䣬Enable���������ڶ�ͨ���ɼ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�����������ݿ��16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //����洢�����ݿ��16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMAͨ������ģʽλ���λ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMAͨ�����ȼ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//��ֹDMAͨ���洢�����洢������
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);//��ʼ��DMAͨ��1
	DMA_Cmd(DMA1_Channel1, ENABLE); //ʹ��DMAͨ��1
}
void ADC_GPIO_Init(void){ //GPIO��ʼ������
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//ʹ��DMAʱ�ӣ�����ADC�����ݴ��ͣ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//ʹ��ADC1ʱ��
    GPIO_InitStructure.GPIO_Pin = ADC_CH6 | ADC_CH7; //!!!ѡ��˿�                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ѡ��IO�ӿڹ�����ʽ       
	GPIO_Init(ADCPORT, &GPIO_InitStructure);			
}
void ADC_Configuration(void){ //��ʼ������
	ADC_InitTypeDef ADC_InitStructure;//����ADC��ʼ���ṹ�����
	ADC_GPIO_Init();//GPIO��ʼ������
	ADC_DMA_Init();//DMA��ʼ������
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; //ʹ��ɨ��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ADCת������������ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���������ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ת�������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 2;//!!!˳����й���ת����ADCͨ������Ŀ������ADC�ɼ�ͨ�������޸ģ�
	ADC_Init(ADC1, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	//ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ28����		 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_28Cycles5);//!!! ADC1ѡ���ŵ�x,����˳��y,����ʱ��n������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_28Cycles5);//!!! ADC1ѡ���ŵ�x,����˳��y,����ʱ��n������

	ADC_DMACmd(ADC1, ENABLE);// ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
	ADC_Cmd(ADC1, ENABLE);//ʹ��ADC1
	ADC_ResetCalibration(ADC1); //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼�������
	ADC_StartCalibration(ADC1);//��ʼADC1У׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ʹ��ADC1�����ʼת��
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






























