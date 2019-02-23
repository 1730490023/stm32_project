#ifndef __crc_H
#define __crc_H	 
#include "sys.h"

//看门狗定时时间计算公式:Tout=(预分频值*重装载值)/40 (单位：ms)
//当前pre为64，rlr为625，计算得到Tout时间为1秒（大概值）。

#define pre		IWDG_Prescaler_64 //分频值范围：4,8,16,32,64,128,256
#define rlr		625 //重装载值范围：0～0xFFF（4095）


void IWDG_Init(void);
void IWDG_Feed(void);
		 				    
#endif
