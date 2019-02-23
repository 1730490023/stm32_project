

#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "i2c.h"
#include "usart.h"
#include "MPU6050.h"
#include "led.h"
#include "tim.h"

  float SetAngle=0.0;         //设定初始角度值
  float ActualAngle;          //实际角度值，6050反馈的roll角度
  float err=0.0;              //偏差
  float err_next=0.0;         //最上前的偏差值
  float err_last=0.0;         //上一个偏差值
  float Kp = 0.05;             //比例、积分、微分系数
  float Ki = 0.08;
  float Kd = 0.1;
	float incrementAngle;
  int Angle_pwm;         //记录反馈的值
int Roll;
u8 speed_max = 210;
u8 speed_min = 20;
float Angle_PID(float Angle)     //PID算法
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
	delay_ms(500); //上电时等待其他器件就绪
	RCC_Configuration();   //系统时钟初始化 
	LED_Init();            //GPIO 初始化
	I2C_Configuration(); 	 
	MPU6050_Init();
	USART1_Init(115200);	   //串口初始化为9600
	
	TIM3_Init(10,100);     //定时器初始化，定时100us（10，360）
  
	while(1)
	{
//		moto01(200,0);
//    moto02(200,0); 	
		MPU6050_READ(t);	//加速度
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

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒
GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED控制
*/

