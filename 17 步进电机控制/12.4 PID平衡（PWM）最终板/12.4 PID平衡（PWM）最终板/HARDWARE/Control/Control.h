#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
				
typedef struct PID
{
    int SetPoint; //�趨Ŀ�� Desired Value
    long SumError; //����ۼ�
    float Proportion; //�������� Proportional Const
    float Integral; //���ֳ��� Integral Const
    float Derivative; //΢�ֳ��� Derivative Const
    int LastError; //Error[-1]
    int PrevError; //Error[-2]
} PID;			

extern u16 Speed_to_exit;
				
void Control(int Speed);
void Motodriver_IncPIDInit(void);
int Motodriver_IncPIDCalc(int NextPoint, int SetP);

#endif
