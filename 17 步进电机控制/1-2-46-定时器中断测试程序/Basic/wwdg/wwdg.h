#ifndef __WWDG_H
#define __WWDG_H	 
#include "sys.h"

//窗口看门狗定时时间计算公式:
//上窗口超时时间（单位us） = 4096*预分频值*(计数器初始值-窗口值)/APB1时钟频率（单位MHz）
//下窗口超时时间（单位us） = 4096*预分频值*(计数器初始值-0x40)/APB1时钟频率（单位MHz）

#define WWDG_CNT	0x7F //计数器初始值，范围：0x40～0x7F
#define wr		0x50 //窗口值，范围：0x40～0x7F
#define fprer	WWDG_Prescaler_8 //预分频值，取值：1,2,4,8

//如上三个值是：0x7f，0x50，8时，上窗口48MS，下窗口64MS。

void WWDG_Init(void);
void WWDG_NVIC_Init(void);
void WWDG_Feed(void);
		 				    
#endif
