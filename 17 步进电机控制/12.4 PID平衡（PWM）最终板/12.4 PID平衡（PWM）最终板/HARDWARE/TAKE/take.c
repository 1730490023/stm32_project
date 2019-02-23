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

#define DEBUG 0
#define ZERO_SPEED 65535 //零速
#define MAX_ACCEL 7 //最大ACCEL
#define MAX_THROTTLE 600 //最大油门530
#define MAX_STEERING 136 //最大转向
#define MAX_TARGET_ANGLE 12 //最大目标角度12
#define I2C_SPEED 400000L //I2C速度
#define Gyro_Gain 0.03048//陀螺增益
#define Gyro_Scaled(x) x*Gyro_Gain //返回每秒度的缩放陀螺仪的原始数据
#define RAD2GRAD 57.2957795//57.2957795
#define GRAD2RAD 0.01745329251994329576923690768489//0.01745329251994329576923690768489
// 默认控制条款  
#define KP 0.22 // 0.22        
#define KD 24  // 30 28  26  
#define KP_THROTTLE 0.065  //0.08//0.065
#define KI_THROTTLE 0.05//0.05
// 对于raiseup控制增益
#define KP_RAISEUP 0.16 //kp兴起
#define KD_RAISEUP 40   //kd兴起
#define KP_THROTTLE_RAISEUP 0  //没有对raiseup速度控制
#define KI_THROTTLE_RAISEUP 0.0//油门兴起
#define ITERM_MAX_ERROR 40   // ITERM饱和常数
#define ITERM_MAX 5000
// MPU控制/状态瓦尔
int dmpReady = 0;  // 设置为true，如果DMP初始化成功
uint8_t mpuIntStatus;   // 拥有从MPU实际中断状态字节
uint8_t devStatus;      // 每个设备操作后返回的状态（0=成功！0=错误）
uint16_t packetSize;    // 预计DMP数据包大小（我们18字节）
uint16_t fifoCount;     // 目前在FIFO中的所有字节数
uint8_t fifoBuffer[18]; // FIFO存储缓冲器
//Quaternion q;
uint8_t loop_counter;       // 要生成媒体40Hz的循环
uint8_t slow_loop_counter;  // 慢环2HZ
unsigned long timer_old;//计时器老
unsigned long timer_value;//定时器的值
int debug_counter;//调试计数器
float dt;
int lkf;
// 类的默认I2C地址为0X68
//MPU6050 mpu;
float angle_adjusted;//角度调整
float angle_adjusted_Old;//角度调整
float Kp=KP;
float Kd=KD;
float Kp_thr=KP_THROTTLE;//油门
float Ki_thr=KI_THROTTLE;
float Kp_user=KP;
float Kd_user=KD;
float Kp_thr_user=KP_THROTTLE;
float Ki_thr_user=KI_THROTTLE;
int newControlParameters = 0;//布尔新的控制参数 0=false  1=ture
int modifing_control_parameters=0;//布尔新的控制参数
float PID_errorSum;
float PID_errorOld = 0;
float PID_errorOld2 = 0;
float setPointOld = 0;
float target_angle=0;
float throttle;
float kkll;
float steering;
float max_throttle = MAX_THROTTLE;//最大油门=最大油门
float max_steering = MAX_STEERING;
float max_target_angle = MAX_TARGET_ANGLE;
float control_output=0;
int16_t motor1;
int16_t motor2;
int16_t speed_m[2];           // 电机的实际转速
uint8_t dir_m[2];             // 步进电机的实际方向
int16_t actual_robot_speed;          // 整个机器人的速度（从踏步机速测）
int16_t actual_robot_speed_Old;          // 整个机器人的速度（从踏步机速测）
float estimated_speed_filtered;//估计速度过滤
uint16_t counter_m[2];        // 计数器周期
uint16_t period_m[2][8];      // 八子时期
uint8_t period_m_index[2];    //索引子时期
unsigned long millis=0;    //代替millis（）函数

float constrain(float amt, float low, float high) //限幅函数
{
	float i;
	if(amt<low) amt=low;
	if(amt>high) amt=high;
	return amt;
}


float speedPIControl(float DT, float input, float setPoint,  float Kp, float Ki)
{
	  float error;
	  float output;
	  error = setPoint-input;
	  PID_errorSum += constrain(error,-ITERM_MAX_ERROR,ITERM_MAX_ERROR);
	  PID_errorSum = constrain(PID_errorSum,-ITERM_MAX,ITERM_MAX);
	  output = Kp*error + Ki*PID_errorSum*DT*0.001;
	  return(output);
}

float stabilityPDControl(float DT, float input, float setPoint,  float Kp, float Kd)
{
  float error;
  float output;
  error = setPoint-input;
  // Kd的两部分实施
  //仅使用输入（传感器）的一部分而不是设定值输入输入（T-2）最大的一个
  //而第二个使用该设定值，使之更有点侵略性设定点设定点（T-1）
  output = Kp*error + (Kd*(setPoint - setPointOld) - Kd*(input - PID_errorOld2))/DT;       // + 错误 - PID_error_Old2
  //Serial.print(Kd*(error-PID_errorOld));Serial.print("\t");
  PID_errorOld2 = PID_errorOld;
  PID_errorOld = input;  // 误差为Kd值是唯一的输入组件
  setPointOld = setPoint;
  return(output);
}

void setMotorSpeed(uint8_t motor, int16_t tspeed)
{
  // 我们限制最大加速度
  if ((speed_m[motor] - tspeed)>MAX_ACCEL)
    speed_m[motor] -= MAX_ACCEL;
  else if ((speed_m[motor] - tspeed)<-MAX_ACCEL)
    speed_m[motor] += MAX_ACCEL;
  else
    speed_m[motor] = tspeed;  
  calculateSubperiods(motor);  //我们采用四个子周期来提高分辨率
  // 为了节省能量，当它没有运行...
  if ((speed_m[0]==0)&&(speed_m[1]==0))
    EN=1;//digitalWrite(4,HIGH);   //禁用电机
  else
    EN=0;//digitalWrite(4,LOW);   // 使电机
}

void calculateSubperiods(uint8_t motor)
{
	  int subperiod;
	  int absSpeed;
	  uint8_t j;
	  
	  if (speed_m[motor] == 0)
		{
			for (j=0;j<8;j++)
			  period_m[motor][j] = ZERO_SPEED;
			return;
		}
	  if (speed_m[motor] > 0 )   // 正速度
		{
			dir_m[motor] = 1; //前进LDIR=0;RDIR=1;
			absSpeed = speed_m[motor];
		}
	  else                       // 负速度
		{
			dir_m[motor] = 0; //后退LDIR=0;RDIR=1;
			absSpeed = -speed_m[motor];
		}
		
	  for (j=0;j<8;j++)
		period_m[motor][j] = 1000/absSpeed;
	  // 计算亚期。如果模块<0.25=>子期间= 0，如果模块<0.5=>子周期= 1。如果模块<0.75子期间=2其他子期间=3
	  subperiod = ((1000 % absSpeed)*8)/absSpeed;   // 优化代码来计算子期间（整数运算）
	  if (subperiod>0)
	   period_m[motor][1]++;
	  if (subperiod>1)
	   period_m[motor][5]++;
	  if (subperiod>2)
	   period_m[motor][3]++;
	  if (subperiod>3)
	   period_m[motor][7]++;
	  if (subperiod>4)
	   period_m[motor][0]++;
	  if (subperiod>5)
	   period_m[motor][4]++;
	  if (subperiod>6)
	   period_m[motor][2]++; 
}

void kongzhi()
{
	if(USART_RX_STA&0x8000)
	{
		lkf=USART_RX_BUF[0];
		USART2->DR=lkf;
		USART_RX_STA=0;
	}
	if(lkf==1) qian();
	else if(lkf==2) hou();
	else if(lkf==3) zuo();
	else if(lkf==4) you();
	else if(lkf==5) ting();
}

void qian()
{
   throttle=-100;
}
void hou()
{
  throttle = 100;
}
void zuo()
{
    steering = -80;
}
void you()
{
    steering = 80;
}
void ting()
{
    throttle = 0;
   steering =0;
}