

/*
//杜洋工作室出品
//洋桃系列开发板应用程序
//关注微信公众号：洋桃电子
//洋桃开发板资料下载 www.DoYoung.net/YT 
//即可免费看所有教学视频，下载技术资料，技术疑难提问
//更多内容尽在 杜洋工作室主页 www.doyoung.net
*/

/*
《修改日志》
1-201708202309 创建。


*/



#include "wwdg.h"


void WWDG_Init(void){ //初始化窗口看门狗
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); // WWDG 时钟使能
	WWDG_SetPrescaler(fprer); //设置 IWDG 预分频值
	WWDG_SetWindowValue(wr); //设置窗口值
	WWDG_Enable(WWDG_CNT); //使能看门狗,设置 counter
	WWDG_ClearFlag(); //清除提前唤醒中断标志位
	WWDG_NVIC_Init(); //初始化窗口看门狗 NVIC
	WWDG_EnableIT(); //开启窗口看门狗中断
}

void WWDG_NVIC_Init(void){ //窗口看门狗中断服务程序（被WWDG_Init调用）
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn; //WWDG 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占 2 子优先级 3 组 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //抢占 2,子优先级 3,组 2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure); //NVIC 初始化
}

void WWDG_Feed(void){ //窗口喂狗程序
    WWDG_SetCounter(WWDG_CNT); //固件库的喂狗函数
}

void WWDG_IRQHandler(void){	//窗口看门狗中断处理程序
	WWDG_ClearFlag(); //清除提前唤醒中断标志位

	//此处加入在复位前需要处理的工作或保存数据
}
 
/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/


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
