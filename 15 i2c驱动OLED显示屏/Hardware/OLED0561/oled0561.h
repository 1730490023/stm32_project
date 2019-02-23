#ifndef __OLED_H
#define __OLED_H	 
#include "sys.h"
#include "i2c.h"

#define OLED0561_ADD	0x78  // OLED��I2C��ַ����ֹ�޸ģ�
#define COM				0x00  // OLED ָ���ֹ�޸ģ�
#define DAT 			0x40  // OLED ���ݣ���ֹ�޸ģ�

void OLED0561_Init(void);//��ʼ��
void OLED_DISPLAY_ON (void);//OLED������ʾ
void OLED_DISPLAY_OFF (void);//OLED������ʾ
void OLED_DISPLAY_LIT (u8 x);//OLED���������ã�0~255��
void OLED_DISPLAY_CLEAR(void);//��������
void OLED_DISPLAY_8x16(u8 x,u8 y,u16 w);//��ʾ8x16�ĵ����ַ� 
void OLED_DISPLAY_8x16_BUFFER(u8 row,u8 *str);//��ʾ8x16���ַ���

		 				    
#endif
