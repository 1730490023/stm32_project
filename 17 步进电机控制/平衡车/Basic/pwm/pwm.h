#ifndef  __PWM_H
#define  __PWM_H
#include "sys.h"

void TIM3_PWM_Init(u16 arr,u16 psc,u16 CCR1_val);
void TIM3_NVIC_Init (void);
extern unsigned int tims;

#endif
