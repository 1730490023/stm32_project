#ifndef __IMU_H
#define __IMU_H
#include "sys.h"

typedef struct{
				float X;
				float Y;
				float Z;}S_FLOAT_XYZ;

typedef struct{
				int16_t X;
				int16_t Y;
				int16_t Z;}S_INT16_XYZ;

typedef struct{
				int32_t X;
				int32_t Y;
				int32_t Z;}S_INT32_XYZ;

extern S_FLOAT_XYZ	Q_ANGLE;			//四元数计算出的角度
extern S_INT16_XYZ	MPU6050_ACC_LAST,MPU6050_GYRO_LAST;		//最新一次读取值
extern S_INT16_XYZ	MPU6050_ACC_NOW,MPU6050_GYRO_NOW;

				
				
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);
void Recursive_Fliter(S_INT16_XYZ *data_in,S_INT16_XYZ *data_out,uint8_t fliter_num);
void Prepare_Data(void);
void Get_Attitude(void);
void Get_Offset(void);
#endif

				