#ifndef __IWDG_H
#define __IWDG_H	 
#include "sys.h"

//���Ź���ʱʱ����㹫ʽ:Tout=(Ԥ��Ƶֵ*��װ��ֵ)/40 (��λ��ms)
//��ǰpreΪ64��rlrΪ625������õ�Toutʱ��Ϊ1�루���ֵ����

#define pre		IWDG_Prescaler_64 //��Ƶֵ��Χ��4,8,16,32,64,128,256
#define rlr		625 //��װ��ֵ��Χ��0��0xFFF��4095��


void IWDG_Init(void);
void IWDG_Feed(void);
		 				    
#endif
