#ifndef __WWDG_H
#define __WWDG_H	 
#include "sys.h"

//���ڿ��Ź���ʱʱ����㹫ʽ:
//�ϴ��ڳ�ʱʱ�䣨��λus�� = 4096*Ԥ��Ƶֵ*(��������ʼֵ-����ֵ)/APB1ʱ��Ƶ�ʣ���λMHz��
//�´��ڳ�ʱʱ�䣨��λus�� = 4096*Ԥ��Ƶֵ*(��������ʼֵ-0x40)/APB1ʱ��Ƶ�ʣ���λMHz��

#define WWDG_CNT	0x7F //��������ʼֵ����Χ��0x40��0x7F
#define wr		0x50 //����ֵ����Χ��0x40��0x7F
#define fprer	WWDG_Prescaler_8 //Ԥ��Ƶֵ��ȡֵ��1,2,4,8

//��������ֵ�ǣ�0x7f��0x50��8ʱ���ϴ���48MS���´���64MS��

void WWDG_Init(void);
void WWDG_NVIC_Init(void);
void WWDG_Feed(void);
		 				    
#endif
