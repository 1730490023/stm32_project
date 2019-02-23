#ifndef __CH376_H
#define __CH376_H	 
#include "sys.h"
#include "spi.h"
#include "delay.h"
#include "ch376inc.h"

#define CH376_INTPORT		GPIOA	//����IO�ӿ�
#define CH376_INT			GPIO_Pin_15	//����IO�ӿ�


void 	CH376_PORT_INIT( void ); /* CH376ͨѶ�ӿڳ�ʼ�� */
void	xEndCH376Cmd( void ); /* ����SPI���� */
void 	xWriteCH376Cmd( u8 mCmd ); /* ��CH376д���� */
void 	xWriteCH376Data( u8 mData );/* ��CH376д���� */
u8 	xReadCH376Data( void );	/* ��CH376������ */
u8 	Query376Interrupt( void );/* ��ѯCH376�ж�(INT#����Ϊ�͵�ƽ) */
u8 	mInitCH376Host( void ); /* ��ʼ��CH376 */

		 				    
#endif
