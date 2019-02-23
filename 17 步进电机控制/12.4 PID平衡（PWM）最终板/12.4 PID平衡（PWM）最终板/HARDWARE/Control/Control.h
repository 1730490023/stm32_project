#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
				
typedef struct PID
{
    int SetPoint; //设定目标 Desired Value
    long SumError; //误差累计
    float Proportion; //比例常数 Proportional Const
    float Integral; //积分常数 Integral Const
    float Derivative; //微分常数 Derivative Const
    int LastError; //Error[-1]
    int PrevError; //Error[-2]
} PID;			

extern u16 Speed_to_exit;
				
void Control(int Speed);
void Motodriver_IncPIDInit(void);
int Motodriver_IncPIDCalc(int NextPoint, int SetP);

#endif
