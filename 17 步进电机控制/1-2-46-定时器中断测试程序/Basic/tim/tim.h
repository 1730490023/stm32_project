#ifndef  __PWM_H
#define  __PWM_H
#include "sys.h"

void TIM3_Init(u16 arr,u16 psc);
void TIM3_NVIC_Init (void);
void moto01(u8 a,u8 ir);
void moto02(u8 b,u8 ir);

#endif
