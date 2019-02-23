

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
1-201708221422 ����RCCʱ�ӵ����ú�����


*/


#include "sys.h"

void NVIC_Configuration(void){ //Ƕ���ж����������� ������
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
}

void RCC_Configuration(void){ //RCCʱ�ӵ�����  
	ErrorStatus HSEStartUpStatus;   
	RCC_DeInit();              /* RCC system reset(for debug purpose) RCC�Ĵ����ָ���ʼ��ֵ*/   
	RCC_HSEConfig(RCC_HSE_ON); /* Enable HSE ʹ���ⲿ���پ���*/   
	HSEStartUpStatus = RCC_WaitForHSEStartUp(); /* Wait till HSE is ready �ȴ��ⲿ���پ���ʹ�����*/   
	if(HSEStartUpStatus == SUCCESS){   
		/*����PLLʱ��Դ����Ƶϵ��*/   
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); //RCC_PLLMul_x��ö��2~16���Ǳ�Ƶֵ����HSE=8MHZ,RCC_PLLMul_9ʱPLLCLK=72MHZ   
		/*����AHBʱ�ӣ�HCLK��*/   
		RCC_HCLKConfig(RCC_SYSCLK_Div1); //RCC_SYSCLK_Div1����AHBʱ�� = ϵͳʱ��(SYSCLK) = 72MHZ���ⲿ����8HMZ��   
		/*ע��˴������ã����ʹ��SYSTICK����ʱ���򣬴�ʱSYSTICK(Cortex System timer)=HCLK/8=9MHZ*/   
		RCC_PCLK1Config(RCC_HCLK_Div2); //���õ���AHBʱ�ӣ�PCLK1��,RCC_HCLK_Div2����APB1ʱ�� = HCLK/2 = 36MHZ���ⲿ����8HMZ��   
		RCC_PCLK2Config(RCC_HCLK_Div1); //���ø���AHBʱ�ӣ�PCLK2��,RCC_HCLK_Div1����APB2ʱ�� = HCLK = 72MHZ���ⲿ����8HMZ��   
		/*ע��AHB��Ҫ�����ⲿ�洢��ʱ�ӡ�APB2����AD��I/O���߼�TIM������1��APB1����DA��USB��SPI��I2C��CAN������2��3��4��5����ͨTIM */  
		FLASH_SetLatency(FLASH_Latency_2); //����FLASH�洢����ʱʱ��������   
		/*FLASHʱ���ӳټ������ڣ��ȴ�����ͬ��������   
		�Ƽ����յ�Ƭ��ϵͳ����Ƶ�ʣ�
		0��24MHzʱ��ȡLatency_0��   
		24��48MHzʱ��ȡLatency_1��   
		48~72MHzʱ��ȡLatency_2*/   
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //ѡ��FLASHԤȡָ�����ģʽ��Ԥȡָ����ʹ��   
		RCC_PLLCmd(ENABLE);	//ʹ��PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); //�ȴ�PLL����ȶ�   
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //ѡ��SYSCLKʱ��ԴΪPLL
		while(RCC_GetSYSCLKSource() != 0x08); //�ȴ�PLL��ΪSYSCLKʱ��Դ   
	}  
	/*��ʼʹ�ܳ�������Ҫʹ�õ�����ʱ��*/   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |   
	RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE); //APB2����ʱ��ʹ��      
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //APB1����ʱ��ʹ��  
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);   
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);   	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    
}  

/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/
