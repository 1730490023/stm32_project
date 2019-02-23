


#include "led.h" //因在中断处理函数中用到LED驱动

#include "tim.h"

//定时器时间计算公式Tout = ((重装载值+1)*(预分频系数+1))/时钟频率;36m
//例如：1秒定时，重装载值=9999，预分频系数=7199
u8 pwms01=0;
u8 pwms02=0;
u8 tims01=0;
u8 tims02=0;

void TIM3_Init(u16 arr,u16 psc){  //TIM3 初始化 arr重装载值 psc预分频系数
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3
    TIM3_NVIC_Init (); //开启TIM3中断向量
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr; //设置自动重装载值
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //预分频系数
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //计数器向上溢出
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue); //TIM3初始化设置
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//使能TIM3中断    
    TIM_Cmd(TIM3,ENABLE); //使能TIM3
}

void TIM3_NVIC_Init (void){ //开启TIM3中断向量
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;	//设置抢占和子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_IRQHandler(void){ //TIM3中断处理函数
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //判断是否是TIM3中断
		{	
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

      //此处写入用户自己的处理程序
		  //GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1-GPIO_ReadOutputDataBit(LEDPORT,LED1))); //取反LED1
			pwms01++;
			pwms02++;
			
			if(pwms01>=tims01)    //速度值10~200
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

void moto01(u8 a,u8 ir)      //a 控制速度；IR控制方向
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

void moto02(u8 b,u8 ir)     //b 控制速度；IR控制方向
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
