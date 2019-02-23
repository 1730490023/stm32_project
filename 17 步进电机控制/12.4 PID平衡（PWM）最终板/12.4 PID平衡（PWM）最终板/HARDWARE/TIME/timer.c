#include "led.h"
#include "time.h"
#include "imu.h"
#include "take.h"
#include "delay.h"


//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
#define ZERO_SPEED 65535 //零速

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
	);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}


void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到10为1ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM2, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
							 
}

void TIM2_IRQHandler(void)   //TIM2中断
{
	static uint8_t ms1 = 0,ms50 = 0,ms10 = 0,ms30=0,ms100 = 0,ms20=0;				//中断次数计数器
	static uint16_t ms500=0;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
			
			ms10++;
			ms500++;
		
			millis++;//

			if(ms10==2){
				Prepare_Data();	
				Recursive_Fliter(&MPU6050_GYRO_LAST,&MPU6050_GYRO_NOW ,5);			
				Get_Attitude();		//姿态计算	//10ms计算一次6050数值
				ms10=0;
			}
			if(ms500==500)
			{
				ms500=0;
				LED0=!LED0;
				LED1=!LED1;    
			}
	}
}
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			  TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
			
			  counter_m[0]++;
			  counter_m[1]++;
			  if (counter_m[0] >= period_m[0][period_m_index[0]])
			  {
				counter_m[0] = 0;
				if (period_m[0][0]==ZERO_SPEED)
				  return;
				if (dir_m[0])
				  LDIR=0;  //DIR电机1
				else
				  LDIR=1;
				// 我们需要等待，以免200ns的产生步进脉冲...
				period_m_index[0] = (period_m_index[0]+1)&0x07; // 周期M指数从0到7
				//delay_200ns();
				LSTEP=1; // 步进电机1
				delay_us(1);
				LSTEP=0;
			  }
				
			  if (counter_m[1] >= period_m[1][period_m_index[1]])
			  {
				counter_m[1] = 0;
				if (period_m[1][0]==ZERO_SPEED)
				  return;
				if (dir_m[1])
				  RDIR=1;   // DIR电机2
				else
				  RDIR=0;
				period_m_index[1] = (period_m_index[1]+1)&0x07;
				//delay_200ns();
				RSTEP=1; // 步进电机2
				delay_us(1); 
				RSTEP=0;
			  }
		}
}

