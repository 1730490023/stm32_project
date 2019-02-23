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

//ALIENTEK miniSTM32������ʵ��1
//�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 int main(void)
 {
	uint8_t DataBuffer[14];
	u8 Comder;//���0�����������������1����ǰ����2������ˣ�3������ת��4������ת��5������ת��
	int INT_Q_X, OUT_PUT;
	int len, t, i;
	float OFFSET_Z=0;
	int Change=0;
	int StePoint=0;
	int16_t angular_velocity;
	int16_t estimated_speed;
	 
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ� 
	I2C_Congiguration();
	MPU6050_Init();
	Get_Offset();
	TIM3_Int_Init(3,719);//100Khz�ļ���Ƶ�ʣ�����4��400us 
	TIM2_Int_Init(9,7199);//10Khz�ļ���Ƶ�ʣ�������10Ϊ1ms 
	Motodriver_IncPIDInit();
	EXTIX_Init();		//�ⲿ�жϳ�ʼ��
	delay_ms(100);
	
	EN=1; // digitalWrite(4,HIGH);   // Disbale motors
	timer_old = millis;
	
	
	while(1)
	{
		kongzhi();//���ܿ���ָ��
		timer_value = millis;
		if (Q_ANGLE.X!=angle_adjusted)
		{
			loop_counter++;
			slow_loop_counter++;
			dt=2;//dt = (timer_value-timer_old);
			timer_old = timer_value;  
			angle_adjusted_Old = angle_adjusted;
			angle_adjusted = Q_ANGLE.X;//dmpGetPhi();
			// ���Ǽ�����ƻ����˵��ٶ�
			actual_robot_speed_Old = actual_robot_speed;
			actual_robot_speed = (speed_m[1] - speed_m[0])/2;  // ���棺ǰ��
			angular_velocity = (angle_adjusted-angle_adjusted_Old)*90.0;     // ���ٶȽǶȵ����Ƕȵ�����
			estimated_speed = actual_robot_speed_Old - angular_velocity;     // �������û������ٶȣ�T-1����T-2�����Բ������ӳ�
			estimated_speed_filtered = estimated_speed_filtered*0.95 + (float)estimated_speed*0.05;//�����ٶȹ��ƹ�������
			target_angle = speedPIControl(dt,estimated_speed_filtered,throttle,Kp_thr,Ki_thr); //Ŀ����ٶ�PIC ONTROL dt���ٶȹ��ƹ�������Kp_thr Ki_thr
			target_angle = constrain(target_angle,-max_target_angle,max_target_angle);   // ���޵����  Ŀ��Ƕ�Լ��Ŀ��Ƕ����Ŀ��Ƕ����Ŀ��Ƕ�
			//����������������ٶȣ�
			control_output += stabilityPDControl(dt,angle_adjusted,target_angle,Kp,Kd);
			control_output = constrain(control_output,-800,800);   // ��������������
			// ���Ƶ�ת�򲿷ֵ����ֱ��ע��
			motor1 = -control_output - steering;
			motor2 = -control_output + steering;   //���2��ת
			// ��������ٶ�
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