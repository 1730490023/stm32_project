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
#define ZERO_SPEED 65535 //����
#define MAX_ACCEL 7 //���ACCEL
#define MAX_THROTTLE 600 //�������530
#define MAX_STEERING 136 //���ת��
#define MAX_TARGET_ANGLE 12 //���Ŀ��Ƕ�12
#define I2C_SPEED 400000L //I2C�ٶ�
#define Gyro_Gain 0.03048//��������
#define Gyro_Scaled(x) x*Gyro_Gain //����ÿ��ȵ����������ǵ�ԭʼ����
#define RAD2GRAD 57.2957795//57.2957795
#define GRAD2RAD 0.01745329251994329576923690768489//0.01745329251994329576923690768489
// Ĭ�Ͽ�������  
#define KP 0.22 // 0.22        
#define KD 24  // 30 28  26  
#define KP_THROTTLE 0.065  //0.08//0.065
#define KI_THROTTLE 0.05//0.05
// ����raiseup��������
#define KP_RAISEUP 0.16 //kp����
#define KD_RAISEUP 40   //kd����
#define KP_THROTTLE_RAISEUP 0  //û�ж�raiseup�ٶȿ���
#define KI_THROTTLE_RAISEUP 0.0//��������
#define ITERM_MAX_ERROR 40   // ITERM���ͳ���
#define ITERM_MAX 5000
// MPU����/״̬�߶�
int dmpReady = 0;  // ����Ϊtrue�����DMP��ʼ���ɹ�
uint8_t mpuIntStatus;   // ӵ�д�MPUʵ���ж�״̬�ֽ�
uint8_t devStatus;      // ÿ���豸�����󷵻ص�״̬��0=�ɹ���0=����
uint16_t packetSize;    // Ԥ��DMP���ݰ���С������18�ֽڣ�
uint16_t fifoCount;     // Ŀǰ��FIFO�е������ֽ���
uint8_t fifoBuffer[18]; // FIFO�洢������
//Quaternion q;
uint8_t loop_counter;       // Ҫ����ý��40Hz��ѭ��
uint8_t slow_loop_counter;  // ����2HZ
unsigned long timer_old;//��ʱ����
unsigned long timer_value;//��ʱ����ֵ
int debug_counter;//���Լ�����
float dt;
int lkf;
// ���Ĭ��I2C��ַΪ0X68
//MPU6050 mpu;
float angle_adjusted;//�Ƕȵ���
float angle_adjusted_Old;//�Ƕȵ���
float Kp=KP;
float Kd=KD;
float Kp_thr=KP_THROTTLE;//����
float Ki_thr=KI_THROTTLE;
float Kp_user=KP;
float Kd_user=KD;
float Kp_thr_user=KP_THROTTLE;
float Ki_thr_user=KI_THROTTLE;
int newControlParameters = 0;//�����µĿ��Ʋ��� 0=false  1=ture
int modifing_control_parameters=0;//�����µĿ��Ʋ���
float PID_errorSum;
float PID_errorOld = 0;
float PID_errorOld2 = 0;
float setPointOld = 0;
float target_angle=0;
float throttle;
float kkll;
float steering;
float max_throttle = MAX_THROTTLE;//�������=�������
float max_steering = MAX_STEERING;
float max_target_angle = MAX_TARGET_ANGLE;
float control_output=0;
int16_t motor1;
int16_t motor2;
int16_t speed_m[2];           // �����ʵ��ת��
uint8_t dir_m[2];             // ���������ʵ�ʷ���
int16_t actual_robot_speed;          // ���������˵��ٶȣ���̤�����ٲ⣩
int16_t actual_robot_speed_Old;          // ���������˵��ٶȣ���̤�����ٲ⣩
float estimated_speed_filtered;//�����ٶȹ���
uint16_t counter_m[2];        // ����������
uint16_t period_m[2][8];      // ����ʱ��
uint8_t period_m_index[2];    //������ʱ��
unsigned long millis=0;    //����millis��������

float constrain(float amt, float low, float high) //�޷�����
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
  // Kd��������ʵʩ
  //��ʹ�����루����������һ���ֶ������趨ֵ�������루T-2������һ��
  //���ڶ���ʹ�ø��趨ֵ��ʹ֮���е��������趨���趨�㣨T-1��
  output = Kp*error + (Kd*(setPoint - setPointOld) - Kd*(input - PID_errorOld2))/DT;       // + ���� - PID_error_Old2
  //Serial.print(Kd*(error-PID_errorOld));Serial.print("\t");
  PID_errorOld2 = PID_errorOld;
  PID_errorOld = input;  // ���ΪKdֵ��Ψһ���������
  setPointOld = setPoint;
  return(output);
}

void setMotorSpeed(uint8_t motor, int16_t tspeed)
{
  // �������������ٶ�
  if ((speed_m[motor] - tspeed)>MAX_ACCEL)
    speed_m[motor] -= MAX_ACCEL;
  else if ((speed_m[motor] - tspeed)<-MAX_ACCEL)
    speed_m[motor] += MAX_ACCEL;
  else
    speed_m[motor] = tspeed;  
  calculateSubperiods(motor);  //���ǲ����ĸ�����������߷ֱ���
  // Ϊ�˽�ʡ����������û������...
  if ((speed_m[0]==0)&&(speed_m[1]==0))
    EN=1;//digitalWrite(4,HIGH);   //���õ��
  else
    EN=0;//digitalWrite(4,LOW);   // ʹ���
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
	  if (speed_m[motor] > 0 )   // ���ٶ�
		{
			dir_m[motor] = 1; //ǰ��LDIR=0;RDIR=1;
			absSpeed = speed_m[motor];
		}
	  else                       // ���ٶ�
		{
			dir_m[motor] = 0; //����LDIR=0;RDIR=1;
			absSpeed = -speed_m[motor];
		}
		
	  for (j=0;j<8;j++)
		period_m[motor][j] = 1000/absSpeed;
	  // �������ڡ����ģ��<0.25=>���ڼ�= 0�����ģ��<0.5=>������= 1�����ģ��<0.75���ڼ�=2�������ڼ�=3
	  subperiod = ((1000 % absSpeed)*8)/absSpeed;   // �Ż��������������ڼ䣨�������㣩
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