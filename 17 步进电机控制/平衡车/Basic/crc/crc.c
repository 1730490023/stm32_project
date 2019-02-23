

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



#include "crc.h"


void CRC_Init(void){ //初始化CRC
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);//开启CRC时钟
	CRC_ResetDR();//复位CRC
}


//	以下是CRC固件库函数，可在主程序中直接调用  //

//	CRC_ResetDR();//复位CRC，需要清0重新计算时先复位
//	uint32_t CRC_CalcCRC(uint32_t Data);//CRC计算一个32位数据。参数：32位数据。返回值：32位计算结果
//	uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);//CRC计算一个32位数组。参数：32位数组名，数组长度。返回值：32位计算结果
//	uint32_t CRC_GetCRC(void);//从CRC中读出计算结果。返回值：32位计算结果。

//	void CRC_SetIDRegister(uint8_t IDValue);//向独立寄存器CRC_IDR写数据。参数：8位数据。
//	uint8_t CRC_GetIDRegister(void);//从独立寄存器CRC_IDR读数据。返回值：8位数据。
 
/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/


