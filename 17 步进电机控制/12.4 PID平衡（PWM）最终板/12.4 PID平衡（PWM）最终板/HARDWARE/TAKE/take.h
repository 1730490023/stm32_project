#ifndef __TAKE_H
#define __TAKE_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
extern unsigned long millis;
extern unsigned long timer_value;//定时器的值
extern unsigned long timer_old;//计时器老
extern uint8_t loop_counter;       // 要生成媒体40Hz的循环
extern uint8_t slow_loop_counter;  // 慢环2HZ
extern float dt;
extern float angle_adjusted;//角度调整
extern float angle_adjusted_Old;//角度调整
extern int16_t actual_robot_speed;          // 整个机器人的速度（从踏步机速测）
extern int16_t actual_robot_speed_Old;          // 整个机器人的速度（从踏步机速测）
extern int16_t speed_m[2];           // 电机的实际转速
extern uint8_t dir_m[2];             // 步进电机的实际方向
extern float estimated_speed_filtered;//估计速度过滤
extern float target_angle;
extern float throttle;
extern float max_target_angle;
extern float Kp_thr;//油门
extern float Ki_thr;
extern float control_output;
extern int16_t motor1;
extern int16_t motor2;
extern float steering;
extern float Kp;
extern float Kd;
extern uint16_t counter_m[2];        // 计数器周期
extern uint16_t period_m[2][8];      // 八子时期
extern uint8_t period_m_index[2];    //索引子时期


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
