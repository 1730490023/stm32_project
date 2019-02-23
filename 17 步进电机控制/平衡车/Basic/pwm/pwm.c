
#include "pwm.h"
unsigned int tims;

void TIM3_PWM_Init(u16 arr,u16 psc,u16 CCR1_val)  //TIM3 PWM��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
{  
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    TIM3_NVIC_Init ();
	  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3�����GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOBʱ��(LED��PB0����)
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��AFIOʱ��(��ʱ��3ͨ��3��Ҫ��ӳ�䵽BP5����)
    
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_0;            // TIM_CH3  ͨ��3�����ʽ
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;      // ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
    GPIO_Init(GPIOB,&GPIO_InitStrue);              //GPIO�˿ڳ�ʼ������
	  
	  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_1;            // TIM_CH4  ͨ��4�����ʽ
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;      // ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
    GPIO_Init(GPIOB,&GPIO_InitStrue);              //GPIO�˿ڳ�ʼ������
    
   //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //ӳ�䣬��ӳ��ֻ����64��100��144�ŵ�Ƭ��
   //��û����ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPA6��PA7,PB0,PB1
   //��������ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPB4��PB5,PB0,PB1 (GPIO_PartialRemap_TIM3)
   //����ȫ��ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPC6��PC7,PC8,PC9 (GPIO_FullRemap_TIM3) 
	 
    TIM_TimeBaseInitStrue.TIM_Period=0xffff;    //�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);        //TIM3��ʼ������(����PWM������)
		
		
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_Toggle;         // TIM ����Ƚϴ���ģʽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
		TIM_OCInitStrue.TIM_Pulse = CCR1_val;       //������ֵ
    TIM_OC3Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��3 PWM ģʽ����
    TIM_OC4Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��4 PWM ģʽ����
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Disable);        //ʹ��Ԥװ�ؼĴ���
    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Disable);        //ʹ��Ԥװ�ؼĴ���
		
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//ʹ�� TIM3 �ж� 
    TIM_Cmd(TIM3,ENABLE);        //ʹ��TIM3		
}



void TIM3_NVIC_Init (void)    //����TIM3�ж�����
{     
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;	//������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_IRQHandler(void)  //TIM3??????
{ 
	unsigned int OCH=720;
	unsigned int OCL=1080;
	
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//�ж��Ƿ�����ж�
		{	
      TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
      //�жϷ�����
			TIM_SetCompare3(TIM3,10000); 
    }
}


