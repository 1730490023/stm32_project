#ifndef __RTC_H
#define __RTC_H	 
#include "sys.h" 


//ȫ�ֱ�������������rtc.c�ļ��ж���
//����2����ʹ��extern�������ȫ�ֱ���
//ע�⣺���ﲻ�ܸ�������ֵ
extern u16 ryear;
extern u8 rmon,rday,rhour,rmin,rsec,rweek;



void RTC_First_Config(void);//�״�����RTC������
void RTC_Config(void);//ʵʱʱ�ӳ�ʼ��
u8 Is_Leap_Year(u16 year);//�ж��Ƿ������꺯��                    
u8 RTC_Get(void);//������ǰʱ��ֵ	
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//д�뵱ǰʱ��
u8 RTC_Get_Week(u16 year,u8 month,u8 day);//�������ռ�������




#endif


















