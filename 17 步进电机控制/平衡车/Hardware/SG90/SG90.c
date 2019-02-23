

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
1- 创建。


*/




#include "SG90.h"

void SG90_Init(void){ //舵机接口初始化
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);       
    GPIO_InitStructure.GPIO_Pin = SE_OUT; //选择端口号（0~15或all）                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择IO接口工作方式       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(SE_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(0)); //接口输出
}

void SG90_angle(u8 a){ //舵机角度控制设置（参数值0～180）对应角度0～180度
	u8 b=100;//角度校正偏移量
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(1)); //接口输出
	delay_us(500+a*10+b); //延时
	GPIO_WriteBit(SE_PORT,SE_OUT,(BitAction)(0)); //接口输出
	delay_us(19500-a*10-b); //延时
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
