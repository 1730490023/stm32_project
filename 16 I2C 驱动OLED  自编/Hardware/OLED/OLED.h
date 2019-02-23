#ifndef __OLED_H
#define __OLED_H	




void IIC_Init(void);

void SDA_OUT(void);
/**
**  设置SDA为输入
**/
void SDA_IN(void);
//开始信号
void IIC_Start(void);
void IIC_Stop(void);
/*
*   返回1--应答出错
*   放回0--应答正确
*/
u8 IIC_Wait_Ask(void);
//写一个字节
void IIC_WriteByte(u8 data);
IIC_ReadByte(void);
void WriteCmd(u8 command);
void WriteDat(u8 data);
void OLED_Init(void);
void OLED_ON(void);
void OLED_SetPos(unsigned char x, unsigned char y); //设置起始点坐标
void OLED_Fill(unsigned char fill_Data);//全屏填充
void OLED_CLS(void);//清屏
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);



#endif 