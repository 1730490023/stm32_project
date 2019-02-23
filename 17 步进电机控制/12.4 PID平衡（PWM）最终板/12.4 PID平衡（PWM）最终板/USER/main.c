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
#include "take.h"

//ALIENTEK miniSTM32开发板实验1
//跑马灯实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 int main(void)
 {
	uint8_t DataBuffer[14];
	u8 Comder;//命令：0或者其他代表无命令。1代表前进，2代表后退，3代表左转，4代表右转，5代表旋转。
	int INT_Q_X, OUT_PUT;
	int len, t, i;
	float OFFSET_Z=0;
	int Change=0;
	int StePoint=0;
	int16_t angular_velocity;
	int16_t estimated_speed;
	 
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(9600);	 //串口初始化为9600
	LED_Init();		  	//初始化与LED连接的硬件接口 
	I2C_Congiguration();
	MPU6050_Init();
	Get_Offset();
	TIM3_Int_Init(3,719);//100Khz的计数频率，计数4到400us 
	TIM2_Int_Init(9,7199);//10Khz的计数频率，计数到10为1ms 
	Motodriver_IncPIDInit();
	EXTIX_Init();		//外部中断初始化
	delay_ms(100);
	
	EN=1; // digitalWrite(4,HIGH);   // Disbale motors
	timer_old = millis;
	
	
	while(1)
	{
		kongzhi();//接受控制指令
		timer_value = millis;
		if (Q_ANGLE.X!=angle_adjusted)
		{
			loop_counter++;
			slow_loop_counter++;
			dt=2;//dt = (timer_value-timer_old);
			timer_old = timer_value;  
			angle_adjusted_Old = angle_adjusted;
			angle_adjusted = Q_ANGLE.X;//dmpGetPhi();
			// 我们计算估计机器人的速度
			actual_robot_speed_Old = actual_robot_speed;
			actual_robot_speed = (speed_m[1] - speed_m[0])/2;  // 正面：前锋
			angular_velocity = (angle_adjusted-angle_adjusted_Old)*90.0;     // 角速度角度调整角度调整旧
			estimated_speed = actual_robot_speed_Old - angular_velocity;     // 我们利用机器人速度（T-1）或（T-2），以补偿该延迟
			estimated_speed_filtered = estimated_speed_filtered*0.95 + (float)estimated_speed*0.05;//估计速度估计过滤滤速
			target_angle = speedPIControl(dt,estimated_speed_filtered,throttle,Kp_thr,Ki_thr); //目标角速度PIC ONTROL dt的速度估计过滤油门Kp_thr Ki_thr
			target_angle = constrain(target_angle,-max_target_angle,max_target_angle);   // 有限的输出  目标角度约束目标角度最大目标角度最大目标角度
			//我们整合输出（加速度）
			control_output += stabilityPDControl(dt,angle_adjusted,target_angle,Kp,Kd);
			control_output = constrain(control_output,-800,800);   // 限制最大输出控制
			// 控制的转向部分的输出直接注射
			motor1 = -control_output - steering;
			motor2 = -control_output + steering;   //马达2反转
			// 限制最大速度
			motor1 = constrain(motor1,-600,600);
			motor2 = constrain(motor2,-600,600);
			setMotorSpeed(0,motor1);
			setMotorSpeed(1,motor2);
		}
		  
		if(LED0==1) 
		{
			LED0=0;
			//printf("%.3fm/s2	%d	 %.3fm/s2      %.3fm/s2   %.3fm/s2   %.3fm/s2  \n",angle_adjusted,motor1,control_output, target_angle, dt, throttle);
		}
    }
  }