#include "delay.h"
#include "led.h"
#include "imu.h"
#include "math.h"
#include "MPU6050.h"

#define RtA 		57.324841				//弧度到角度
#define AtR    	0.0174533				//度到角度
#define Acc_G 	0.0011963				//加速度变成G
#define Gyro_G 	0.0610351				//角速度变成度   此参数对应陀螺2000度每秒
#define Gyro_Gr	0.0010653				//角速度变成弧度	此参数对应陀螺2000度每秒
#define ACC_Count 200						//加速度长期积分计数
#define FILTER_NUM 20
#define COUNT_Offset 60

//S_INT16_XYZ ACC_AVG;			//平均值滤波后的ACC
S_INT16_XYZ ACC_Integral_AVG;//平均值滤波后的ACC的长期积分平均值
S_INT32_XYZ ACC_Integral;	//平均值滤波后的ACC的长期积分值
S_INT16_XYZ ACC_AVG;			//平均值滤波后的ACC
S_FLOAT_XYZ GYRO_I;				//陀螺仪积分
S_FLOAT_XYZ EXP_ANGLE;		//期望角度
S_FLOAT_XYZ DIF_ANGLE;		//期望角度与实际角度差
S_FLOAT_XYZ Q_ANGLE;			//四元数计算出的角度
S_INT16_XYZ	MPU6050_ACC_LAST,MPU6050_GYRO_LAST;		//最新一次读取值
S_INT16_XYZ MPU6050_ACC_NOW,MPU6050_GYRO_NOW;
int16_t Accel_X_Offset = 0, Accel_Y_Offset = 0, Accel_Z_Offset = 0, Gyro_X_Offset = 0, Gyro_Y_Offset = 0, Gyro_Z_Offset = 0;
int16_t TempaX = 0, TempaY = 0, TempaZ = 0, TempgX = 0, TempgY = 0, TempgZ = 0;

/*__round_*/
int16_t round_ACC_LASTY=0;
/*__==round==_*/

int16_t	ACC_X_BUF[FILTER_NUM],ACC_Y_BUF[FILTER_NUM],ACC_Z_BUF[FILTER_NUM];	//加速度滑动窗口滤波数组
int16_t ACC_Timer=0;

void Recursive_Fliter(S_INT16_XYZ *data_in,S_INT16_XYZ *data_out,uint8_t fliter_num)
{
	static int16_t	data_X_BUF[5],data_Y_BUF[5],data_Z_BUF[5];
	int64_t temp1=0,temp2=0,temp3=0;
	uint8_t i;
	//----------------------窗口滑动滤波--------------------//
	data_X_BUF[0] = data_in->X;
	data_Y_BUF[0] = data_in->Y;
	data_Z_BUF[0] = data_in->Z;
	for(i=0;i<fliter_num;i++)   // ACC累加
	{
		temp1 += data_X_BUF[i];
		temp2 += data_Y_BUF[i];
		temp3 += data_Z_BUF[i];
	}
	data_out->X = temp1 / fliter_num;
	data_out->Y = temp2 / fliter_num;
	data_out->Z = temp3 / fliter_num;
	for(i=0;i<fliter_num-1;i++)// ACC递推
	{
		data_X_BUF[fliter_num-1-i]= data_X_BUF[fliter_num-2-i];
		data_Y_BUF[fliter_num-1-i]= data_Y_BUF[fliter_num-2-i];
		data_Z_BUF[fliter_num-1-i]= data_Z_BUF[fliter_num-2-i];
	}
}

//计算出MPU6050的零偏值
void Get_Offset(void)
{
	uint16_t i;
	uint8_t DataBuffer[14];
	
	
	for(i = 0; i < COUNT_Offset; i++)
	{
		I2C_ReadBuffer(DataBuffer, 0x3b, 14);
		delay_ms(1);
		//加速度
		TempaX += ((((int16_t)DataBuffer[0])<<8)|DataBuffer[1]);
		TempaY += ((((int16_t)DataBuffer[2])<<8)|DataBuffer[3]);
		TempaZ += ((((int16_t)DataBuffer[4])<<8)|DataBuffer[5]);
		//陀螺仪
		TempgX += ((((int16_t)DataBuffer[8])<<8)|DataBuffer[9]);
		TempgY += ((((int16_t)DataBuffer[10])<<8)|DataBuffer[11]);
		TempgZ += ((((int16_t)DataBuffer[12])<<8)|DataBuffer[13]);	
	}
	Accel_X_Offset = (TempaX / COUNT_Offset);//加速度计x轴的漂移
	TempaX = 0;
	Accel_Y_Offset = (TempaY / COUNT_Offset);//加速度计y轴的漂移
	TempaY = 0;
	Accel_Z_Offset = (TempaZ / COUNT_Offset);//加速度计z轴的漂移
	TempaZ = 0;
	Gyro_X_Offset = (TempgX / COUNT_Offset);//陀螺仪x轴的漂移
	TempgX = 0;
	Gyro_Y_Offset = (TempgY / COUNT_Offset);//陀螺仪y轴的漂移
	TempgY = 0;
	Gyro_Z_Offset = (TempgZ / COUNT_Offset);//陀螺仪z轴的漂移
	TempgZ = 0;
}

void Prepare_Data(void)
{
	int64_t temp1=0,temp2=0,temp3=0;
	uint8_t i;
	uint8_t DataBuffer[14];
	
	
	I2C_ReadBuffer(DataBuffer, 0x3b, 14);
	/*****************加速度***************************************/
	MPU6050_ACC_LAST.X=((((int16_t)DataBuffer[0])<<8)|DataBuffer[1])- Accel_X_Offset;
	MPU6050_ACC_LAST.Y=((((int16_t)DataBuffer[2])<<8)|DataBuffer[3])- Accel_Y_Offset;
	MPU6050_ACC_LAST.Z=((((int16_t)DataBuffer[4])<<8)|DataBuffer[5])- Accel_Z_Offset;
	/*****************角速度***************************************/
	MPU6050_GYRO_LAST.X =((((int16_t)DataBuffer[8])<<8)|DataBuffer[9]) - Gyro_X_Offset;
	MPU6050_GYRO_LAST.Y =((((int16_t)DataBuffer[10])<<8)|DataBuffer[11]) - Gyro_Y_Offset;
	MPU6050_GYRO_LAST.Z =((((int16_t)DataBuffer[12])<<8)|DataBuffer[13]) - Gyro_Z_Offset;			
//	/*****************温度***************************************/
//	Temp=((short)((DataBuffer[6]<<8)+DataBuffer[7]))*1.0/340+36.53;
	
	ACC_X_BUF[0] = MPU6050_ACC_LAST.X;//更新滑动窗口数组
	ACC_Y_BUF[0] = MPU6050_ACC_LAST.Y;
	ACC_Z_BUF[0] = MPU6050_ACC_LAST.Z;
	for(i=0;i<FILTER_NUM;i++)
	{
		temp1 += ACC_X_BUF[i];
		temp2 += ACC_Y_BUF[i];
		temp3 += ACC_Z_BUF[i];
	}
	ACC_AVG.X = temp1 / FILTER_NUM;
	ACC_AVG.Y = temp2 / FILTER_NUM;
	ACC_AVG.Z = temp3 / FILTER_NUM;
	for(i=0;i<FILTER_NUM-1;i++)
	{
		ACC_X_BUF[FILTER_NUM-1-i] = ACC_X_BUF[FILTER_NUM-i-2];
		ACC_Y_BUF[FILTER_NUM-1-i] = ACC_Y_BUF[FILTER_NUM-2-i];
		ACC_Z_BUF[FILTER_NUM-1-i] = ACC_Z_BUF[FILTER_NUM-2-i];
	}
	
	round_ACC_LASTY=ACC_AVG.Y;

	
	GYRO_I.Z += MPU6050_GYRO_LAST.Z*Gyro_G*0.004;
}

void Get_Attitude(void)
{
	IMUupdate(MPU6050_GYRO_LAST.X*Gyro_Gr,
						MPU6050_GYRO_LAST.Y*Gyro_Gr,
						MPU6050_GYRO_LAST.Z*Gyro_Gr,
						ACC_AVG.X,ACC_AVG.Y,ACC_AVG.Z);	//*0.0174转成弧度
}
 
 //===============================四元素============================================
#define Kp 1.6f //10.0f                       // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.001f//1.2f // //0.008f                      // integral gain governs rate of convergence of gyroscope biases
#define halfT 0.001f                   // half the sample period采样周期的一半

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;    // quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0;    // scaled integral error

void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
{
  float norm;
//  float hx, hy, hz, bx, bz;
  float vx, vy, vz;// wx, wy, wz;
  float ex, ey, ez;

  // 先把这些用得到的值算好
  float q0q0 = q0*q0;
  float q0q1 = q0*q1;
  float q0q2 = q0*q2;
//  float q0q3 = q0*q3;
  float q1q1 = q1*q1;
//  float q1q2 = q1*q2;
  float q1q3 = q1*q3;
  float q2q2 = q2*q2;
  float q2q3 = q2*q3;
  float q3q3 = q3*q3;
	
	if(ax*ay*az==0)
 		return;
		
  norm = sqrt(ax*ax + ay*ay + az*az);       //acc数据归一化
  ax = ax /norm;
  ay = ay / norm;
  az = az / norm;

  // estimated direction of gravity and flux (v and w)              估计重力方向和流量/变迁
  vx = 2*(q1q3 - q0q2);												//四元素中xyz的表示
  vy = 2*(q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3 ;

  // error is sum of cross product between reference direction of fields and direction measured by sensors
  ex = (ay*vz - az*vy) ;                           					 //向量外积在相减得到差分就是误差
  ey = (az*vx - ax*vz) ;
  ez = (ax*vy - ay*vx) ;

  exInt = exInt + ex * Ki;								  //对误差进行积分
  eyInt = eyInt + ey * Ki;
  ezInt = ezInt + ez * Ki;

  // adjusted gyroscope measurements
  gx = gx + Kp*ex + exInt;					   							//将误差PI后补偿到陀螺仪，即补偿零点漂移
  gy = gy + Kp*ey + eyInt;
  gz = gz + Kp*ez + ezInt;				   							//这里的gz由于没有观测者进行矫正会产生漂移，表现出来的就是积分自增或自减

  // integrate quaternion rate and normalise						   //四元素的微分方程
  q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
  q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
  q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
  q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

  // normalise quaternion
  norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;

//  Q_ANGLE.Z = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3* q3 + 1)* 57.3; // yaw 
//  Q_ANGLE.Y = asin(-2 * q1 * q3 + 2 * q0* q2)* 60.3; // pitch
  Q_ANGLE.X = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.2957795; // roll
}
