#ifndef __ADC_H
#define __ADC_H 			   
#include "sys.h"


#define ADC1_DR_Address    ((uint32_t)0x4001244C) //ADC1�������ĵ�ַ����ο��ֲ�ó���

#define ADCPORT		GPIOA	//����ADC�ӿ�
#define ADC_CH4		GPIO_Pin_4	//����ADC�ӿ� ��ѹ��λ��
#define ADC_CH5		GPIO_Pin_5	//����ADC�ӿ� ��������
#define ADC_CH6		GPIO_Pin_6	//����ADC�ӿ� ҡ��X��
#define ADC_CH7		GPIO_Pin_7	//����ADC�ӿ� ҡ��Y��


void ADC_DMA_Init(void);
void ADC_GPIO_Init(void);
void ADC_Configuration(void);

#endif





























