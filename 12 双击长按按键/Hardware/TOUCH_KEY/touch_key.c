

#include "touch_key.h"

void TOUCH_KEY_Init(void)     //微动开关的接口初始化
{
	GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构	
    GPIO_InitStructure.GPIO_Pin = TOUCH_KEY_A | TOUCH_KEY_B | TOUCH_KEY_C | TOUCH_KEY_D; //选择端口                       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //选择IO接口工作方式 //下拉输入     
	GPIO_Init(TOUCH_KEYPORT,&GPIO_InitStructure);			
}
 



/*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/
