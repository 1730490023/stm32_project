

/*
//�������ҳ�Ʒ
//����ϵ�п�����Ӧ�ó���
//��ע΢�Ź��ںţ����ҵ���
//���ҿ������������� www.DoYoung.net/YT 
//������ѿ����н�ѧ��Ƶ�����ؼ������ϣ�������������
//�������ݾ��� ����������ҳ www.doyoung.net
*/

/*
���޸���־��
1-201708202309 ������


*/



#include "crc.h"


void CRC_Init(void){ //��ʼ��CRC
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);//����CRCʱ��
	CRC_ResetDR();//��λCRC
}


//	������CRC�̼��⺯����������������ֱ�ӵ���  //

//	CRC_ResetDR();//��λCRC����Ҫ��0���¼���ʱ�ȸ�λ
//	uint32_t CRC_CalcCRC(uint32_t Data);//CRC����һ��32λ���ݡ�������32λ���ݡ�����ֵ��32λ������
//	uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);//CRC����һ��32λ���顣������32λ�����������鳤�ȡ�����ֵ��32λ������
//	uint32_t CRC_GetCRC(void);//��CRC�ж���������������ֵ��32λ��������

//	void CRC_SetIDRegister(uint8_t IDValue);//������Ĵ���CRC_IDRд���ݡ�������8λ���ݡ�
//	uint8_t CRC_GetIDRegister(void);//�Ӷ����Ĵ���CRC_IDR�����ݡ�����ֵ��8λ���ݡ�
 
/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/


