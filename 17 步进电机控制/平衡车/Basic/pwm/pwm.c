
#include "pwm.h"
unsigned int tims;

void TIM3_PWM_Init(u16 arr,u16 psc,u16 CCR1_val)  //TIM3 PWM初始化 arr重装载值 psc预分频系数
{  
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    TIM3_NVIC_Init ();
	  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3和相关GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOB时钟(LED在PB0引脚)
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能AFIO时钟(定时器3通道3需要重映射到BP5引脚)
    
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_0;            // TIM_CH3  通道3输出方式
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;      // 复用推挽
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //设置最大输出速度
    GPIO_Init(GPIOB,&GPIO_InitStrue);              //GPIO端口初始化设置
	  
	  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_1;            // TIM_CH4  通道4输出方式
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;      // 复用推挽
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //设置最大输出速度
    GPIO_Init(GPIOB,&GPIO_InitStrue);              //GPIO端口初始化设置
    
   //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //映射，重映射只用于64、100、144脚单片机
   //当没有重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PA6，PA7,PB0,PB1
   //当部分重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PB4，PB5,PB0,PB1 (GPIO_PartialRemap_TIM3)
   //当完全重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PC6，PC7,PC8,PC9 (GPIO_FullRemap_TIM3) 
	 
    TIM_TimeBaseInitStrue.TIM_Period=0xffff;    //设置自动重装载值
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //预分频系数
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    //计数器向上溢出
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);        //TIM3初始化设置(设置PWM的周期)
		
		
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_Toggle;         // TIM 输出比较触发模式
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// 设置极性-有效电平为：高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// 输出使能
		TIM_OCInitStrue.TIM_Pulse = CCR1_val;       //待捕获值
    TIM_OC3Init(TIM3,&TIM_OCInitStrue);        //TIM3的通道3 PWM 模式设置
    TIM_OC4Init(TIM3,&TIM_OCInitStrue);        //TIM3的通道4 PWM 模式设置
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Disable);        //使能预装载寄存器
    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Disable);        //使能预装载寄存器
		
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//使能 TIM3 中断 
    TIM_Cmd(TIM3,ENABLE);        //使能TIM3		
}



void TIM3_NVIC_Init (void)    //开启TIM3中断向量
{     
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;	//设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_IRQHandler(void)  //TIM3??????
{ 
	unsigned int OCH=720;
	unsigned int OCL=1080;
	
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//判断是否产生中断
		{	
      TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
      //中断服务函数
			TIM_SetCompare3(TIM3,10000); 
    }
}


