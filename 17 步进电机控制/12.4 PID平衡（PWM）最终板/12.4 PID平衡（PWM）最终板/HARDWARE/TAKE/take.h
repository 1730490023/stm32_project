#ifndef __TAKE_H
#define __TAKE_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
extern unsigned long millis;
extern unsigned long timer_value;//��ʱ����ֵ
extern unsigned long timer_old;//��ʱ����
extern uint8_t loop_counter;       // Ҫ����ý��40Hz��ѭ��
extern uint8_t slow_loop_counter;  // ����2HZ
extern float dt;
extern float angle_adjusted;//�Ƕȵ���
extern float angle_adjusted_Old;//�Ƕȵ���
extern int16_t actual_robot_speed;          // ���������˵��ٶȣ���̤�����ٲ⣩
extern int16_t actual_robot_speed_Old;          // ���������˵��ٶȣ���̤�����ٲ⣩
extern int16_t speed_m[2];           // �����ʵ��ת��
extern uint8_t dir_m[2];             // ���������ʵ�ʷ���
extern float estimated_speed_filtered;//�����ٶȹ���
extern float target_angle;
extern float throttle;
extern float max_target_angle;
extern float Kp_thr;//����
extern float Ki_thr;
extern float control_output;
extern int16_t motor1;
extern int16_t motor2;
extern float steering;
extern float Kp;
extern float Kd;
extern uint16_t counter_m[2];        // ����������
extern uint16_t period_m[2][8];      // ����ʱ��
extern uint8_t period_m_index[2];    //������ʱ��


void kongzhi();
void calculateSubperiods(uint8_t motor);
void setMotorSpeed(uint8_t motor, int16_t tspeed);
float constrain(float amt, float low, float high);
float speedPIControl(float DT, float input, float setPoint,  float Kp, float Ki);
float stabilityPDControl(float DT, float input, float setPoint,  float Kp, float Kd);
void qian();
void hou();
void zuo();
void you();
void ting();
		 				    
#endif
