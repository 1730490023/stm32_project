

#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "i2c.h"
#include "usart.h"
#include "MPU6050.h"
#include "led.h"
#include "tim.h"

  float SetAngle=0.0;         //�趨��ʼ�Ƕ�ֵ
  float ActualAngle;          //ʵ�ʽǶ�ֵ��6050������roll�Ƕ�
  float err=0.0;              //ƫ��
  float err_next=0.0;         //����ǰ��ƫ��ֵ
  float err_last=0.0;         //��һ��ƫ��ֵ
  float Kp = 0.05;             //���������֡�΢��ϵ��
  float Ki = 0.08;
  float Kd = 0.1;
	float incrementAngle;
  int Angle_pwm;         //��¼������ֵ
int Roll;
u8 speed_max = 210;
u8 speed_min = 20;
float Angle_PID(float Angle)     //PID�㷨
{
    SetAngle=Angle;     
    err=SetAngle-ActualAngle;
    incrementAngle = Kp*(err-err_next)+Ki*err + Kd*(err-2*err_next+err_last);
    //ActualAngle+=incrementAngle;
    err_last=err_next;
    err_next=err;
    return incrementAngle;
}


int main(void)
{
	u16 t[6]={0};
	delay_ms(500); //�ϵ�ʱ�ȴ�������������
	RCC_Configuration();   //ϵͳʱ�ӳ�ʼ�� 
	LED_Init();            //GPIO ��ʼ��
	I2C_Configuration(); 	 
	MPU6050_Init();
	USART1_Init(115200);	   //���ڳ�ʼ��Ϊ9600
	
	TIM3_Init(10,100);     //��ʱ����ʼ������ʱ100us��10��360��
  
	while(1)
	{
//		moto01(200,0);
//    moto02(200,0); 	
		MPU6050_READ(t);	//���ٶ�
    if(t[1]<=32768)
		{
			Roll=t[1];
		}
		else
		{
			Roll=-(65535-t[1]);
		}
		
		ActualAngle = Roll;
		Angle_pwm = (int)Angle_PID(0);
		printf("y= %d\n",t[1]/16);
		delay_ms(50);

//		if(Angle_pwm<0)
//		{
//			if(-Angle_pwm<=speed_min)
//			{	
//				moto01(speed_min,1); 
//				moto02(speed_min,1); 
//			}
//			else if(-Angle_pwm>speed_min && -Angle_pwm<speed_max)
//			{
//				moto01(-Angle_pwm,1); 
//				moto02(-Angle_pwm,1); 
//			}
//			else if(-Angle_pwm>=speed_max)
//			{
//				moto01(speed_max,1); 
//				moto02(speed_max,1); 
//			}	
//		}
//		else
//		{
//			if(Angle_pwm<=speed_min)
//			{	
//				moto01(speed_min,0); 
//				moto02(speed_min,0); 
//			}
//			else if(Angle_pwm>speed_min && Angle_pwm<speed_max)
//			{
//				moto01(Angle_pwm,0); 
//				moto02(Angle_pwm,0); 
//			}
//			else if(Angle_pwm>=speed_max)
//			{
//				moto01(speed_max,0); 
//				moto02(speed_max,0); 
//			}	
//		}	  
	}

}
/*

���������塿
u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8     a; //����8λ�޷��ű���a
vu32     a; //�����ױ��32λ�޷��ű���a
vu16     a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32     a; //����ֻ����32λ�޷��ű���a
uc16     a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

#define ONE  1   //�궨��

delay_us(1); //��ʱ1΢��
delay_ms(1); //��ʱ1����
delay_s(1); //��ʱ1��
GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED����
*/

