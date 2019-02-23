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


//���PID ������ʼ��
void Motodriver_IncPIDInit(void)
{
      sptr->SumError = 0; 
      sptr->LastError = 0;  //Error[-1]
      sptr->PrevError = 0;  //Error[-2]
      sptr->Proportion =0.1; //�������� Proportional Const
      sptr->Integral = 0;  //���ֳ��� Integral Const
      sptr->Derivative = 0; //΢�ֳ��� Derivative Const
      sptr->SetPoint = 0;
}

//PID ���ڿ���������ٶȿ��� 
//����ʽ PID �������
int Motodriver_IncPIDCalc(int NextPoint, int SetP)
{
      static int iError, iIncpid;
      double iIncpi;
      //��ǰ���
	  sptr->SetPoint=SetP;
      iError = sptr->SetPoint - NextPoint;
	  sptr->PrevError = iError - sptr->LastError;
      sptr->LastError = iError;
	  //��������
      iIncpi = sptr->Proportion * iError  + sptr->Derivative * sptr->PrevError; //E[k]��  E[k��1]��  E[k��2]��
      iIncpid = (int)iIncpi;
      //��������ֵ
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
	if(Dir==1) //Dir=0������ǰ������������ת
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
			TIM3_PWM_Init(11520,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
			TIM_SetCompare1(TIM3,500);
			TIM_SetCompare3(TIM3,500);
		}
		else if(Q_ANGLE.X>6 || Q_ANGLE.X<-6)
		{
			TIM3_PWM_Init(11520,3);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
			TIM_SetCompare1(TIM3,500);
			TIM_SetCompare3(TIM3,500);
		}
		else if(Q_ANGLE.X>3 || Q_ANGLE.X<-3)
		{
			TIM3_PWM_Init(11520,7);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
			TIM_SetCompare1(TIM3,500);
			TIM_SetCompare3(TIM3,500);
		}
		else
		{
			TIM3_PWM_Init(11520,9);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
			TIM_SetCompare1(TIM3,500);
			TIM_SetCompare3(TIM3,500);
		}
		OUT_PUT_Count=0;
		EN=0;
	}
}