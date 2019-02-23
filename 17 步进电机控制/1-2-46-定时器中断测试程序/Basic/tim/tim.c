


#include "led.h" //�����жϴ��������õ�LED����

#include "tim.h"

//��ʱ��ʱ����㹫ʽTout = ((��װ��ֵ+1)*(Ԥ��Ƶϵ��+1))/ʱ��Ƶ��;36m
//���磺1�붨ʱ����װ��ֵ=9999��Ԥ��Ƶϵ��=7199
u8 pwms01=0;
u8 pwms02=0;
u8 tims01=0;
u8 tims02=0;

void TIM3_Init(u16 arr,u16 psc){  //TIM3 ��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3
    TIM3_NVIC_Init (); //����TIM3�ж�����
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr; //�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue); //TIM3��ʼ������
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//ʹ��TIM3�ж�    
    TIM_Cmd(TIM3,ENABLE); //ʹ��TIM3
}

void TIM3_NVIC_Init (void){ //����TIM3�ж�����
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;	//������ռ�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_IRQHandler(void){ //TIM3�жϴ�����
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //�ж��Ƿ���TIM3�ж�
		{	
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

      //�˴�д���û��Լ��Ĵ������
		  //GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1-GPIO_ReadOutputDataBit(LEDPORT,LED1))); //ȡ��LED1
			pwms01++;
			pwms02++;
			
			if(pwms01>=tims01)    //�ٶ�ֵ10~200
			{
				
				GPIO_WriteBit(LEDPORT,Setp1,(BitAction)(1-GPIO_ReadOutputDataBit(LEDPORT,Setp1)));
				pwms01=0;
				
			}				
			if(pwms02>=tims02)
			{
				
				GPIO_WriteBit(LEDPORT,Setp2,(BitAction)(1-GPIO_ReadOutputDataBit(LEDPORT,Setp2)));
				pwms02=0;
				
			}			
    }
}

void moto01(u8 a,u8 ir)      //a �����ٶȣ�IR���Ʒ���
{
	tims01 = 220-a;

	if(ir==0)
	{
	 GPIO_WriteBit(LEDPORT,Dir1,(BitAction)(1));
	}
	else
	{
	 GPIO_WriteBit(LEDPORT,Dir1,(BitAction)(0));
	}
}

void moto02(u8 b,u8 ir)     //b �����ٶȣ�IR���Ʒ���
{
	tims02 = 220-b;
	
	if(ir==0)
	{
	 GPIO_WriteBit(LEDPORT,Dir2,(BitAction)(1));
	}
	else
	{
	 GPIO_WriteBit(LEDPORT,Dir2,(BitAction)(0));
	}
}
