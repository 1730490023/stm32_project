#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "pwm.h"
#include "sys.h"
#include "usart.h"
#include "control.h"
#include "MPU6050.h"
#include "time.h"
#include "imu.h"
#include "exti.h"

static PID sPID, dPID;
static PID *sptr = &sPID, *dptr = &dPID;
u16 Speed_to_exit=0;


//电机PID 参数初始化
void Motodriver_IncPIDInit(void)
{
      sptr->SumError = 0; 
      sptr->LastError = 0;  //Error[-1]
      sptr->PrevError = 0;  //Error[-2]
      sptr->Proportion =0.1; //比例常数 Proportional Const
      sptr->Integral = 0;  //积分常数 Integral Const
      sptr->Derivative = 0; //微分常数 Derivative Const
      sptr->SetPoint = 0;
}

//PID 调节控制做电机速度控制 
//增量式 PID 控制设计
int Motodriver_IncPIDCalc(int NextPoint, int SetP)
{
      static int iError, iIncpid;
      double iIncpi;
      //当前误差
	  sptr->SetPoint=SetP;
      iError = sptr->SetPoint - NextPoint;
	  sptr->PrevError = iError - sptr->LastError;
      sptr->LastError = iError;
	  //增量计算
      iIncpi = sptr->Proportion * iError  + sptr->Derivative * sptr->PrevError; //E[k]项  E[k－1]项  E[k－2]项
      iIncpid = (int)iIncpi;
      //返回增量值
      return(iIncpid);
}

void Control(int Speed)
{
	int i;
	int Dir;
	static int Not_Blance_Flag=0;
	
	if(Speed>=0){
		Speed=Speed;
		Dir=1;
	}else{
		Speed=-Speed;
		Dir=0;
	}
	EN=1;
	Speed_to_exit=Speed;
	if(Dir==1) //Dir=0代表向前，否则代表向后转
	{
		LDIR=0;
		RDIR=1;
	}else{
		LDIR=1;
		RDIR=0;
	}
	if(Q_ANGLE.X>35 || Q_ANGLE.X<-35){
			EN=1;
	}
	else{
		if(Q_ANGLE.X>12 || Q_ANGLE.X<-12)
		{
			TIM3_PWM_Init(11520,0);//不分频。PWM频率=72000/(899+1)=80Khz 
			TIM_SetCompare1(TIM3,500);
			TIM_SetCompare3(TIM3,500);
		}
		else if(Q_ANGLE.X>6 || Q_ANGLE.X<-6)
		{
			TIM3_PWM_Init(11520,3);//不分频。PWM频率=72000/(899+1)=80Khz 
			TIM_SetCompare1(TIM3,500);
			TIM_SetCompare3(TIM3,500);
		}
		else if(Q_ANGLE.X>3 || Q_ANGLE.X<-3)
		{
			TIM3_PWM_Init(11520,7);//不分频。PWM频率=72000/(899+1)=80Khz
			TIM_SetCompare1(TIM3,500);
			TIM_SetCompare3(TIM3,500);
		}
		else
		{
			TIM3_PWM_Init(11520,9);//不分频。PWM频率=72000/(899+1)=80Khz 
			TIM_SetCompare1(TIM3,500);
			TIM_SetCompare3(TIM3,500);
		}
		OUT_PUT_Count=0;
		EN=0;
	}
}