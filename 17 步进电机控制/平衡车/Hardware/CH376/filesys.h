
#ifndef	__FILESYS_H__
#define __FILESYS_H__
#include "sys.h"
#include "ch376.h"
#include"CH376INC.H"

#define	STRUCT_OFFSET( s, m )	( (UINT8)( & ((s *)0) -> m ) )							/* �����ȡ�ṹ��Ա���ƫ�Ƶ�ַ�ĺ� */
#ifdef	EN_LONG_NAME
#ifndef	LONG_NAME_BUF_LEN
#define	LONG_NAME_BUF_LEN	( LONG_NAME_PER_DIR * 20 )									/* ���ж���ĳ��ļ�������������,��СֵΪLONG_NAME_PER_DIR*1 */
#endif
#endif

UINT8	CH376ReadBlock( PUINT8 buf );  													/* �ӵ�ǰ�����˵�Ľ��ջ�������ȡ���ݿ�,���س��� */

UINT8	CH376WriteReqBlock( PUINT8 buf );  												/* ���ڲ�ָ��������д����������ݿ�,���س��� */

void	CH376WriteHostBlock( PUINT8 buf, UINT8 len );  									/* ��USB�����˵�ķ��ͻ�����д�����ݿ� */

void	CH376WriteOfsBlock( PUINT8 buf, UINT8 ofs, UINT8 len );  						/* ���ڲ�������ָ��ƫ�Ƶ�ַд�����ݿ� */

void	CH376SetFileName( PUINT8 name );  												/* ���ý�Ҫ�������ļ����ļ��� */

UINT32	CH376Read32bitDat( void );  													/* ��CH376оƬ��ȡ32λ�����ݲ��������� */

UINT8	CH376ReadVar8( UINT8 var );  													/* ��CH376оƬ�ڲ���8λ���� */

void	CH376WriteVar8( UINT8 var, UINT8 dat );  										/* дCH376оƬ�ڲ���8λ���� */

UINT32	CH376ReadVar32( UINT8 var );  													/* ��CH376оƬ�ڲ���32λ���� */

void	CH376WriteVar32( UINT8 var, UINT32 dat );  										/* дCH376оƬ�ڲ���32λ���� */

void	CH376EndDirInfo( void );  														/* �ڵ���CH376DirInfoRead��ȡFAT_DIR_INFO�ṹ֮��Ӧ��֪ͨCH376���� */

UINT32	CH376GetFileSize( void );  														/* ��ȡ��ǰ�ļ����� */

UINT8	CH376GetDiskStatus( void );                                                     /* ��ȡ���̺��ļ�ϵͳ�Ĺ���״̬ */

UINT8	CH376GetIntStatus( void );                                                      /* ��ȡ�ж�״̬��ȡ���ж����� */

#ifndef	NO_DEFAULT_CH376_INT
UINT8	Wait376Interrupt( void );                                                       /* �ȴ�CH376�ж�(INT#�͵�ƽ)�������ж�״̬��, ��ʱ�򷵻�ERR_USB_UNKNOWN */
#endif

UINT8	CH376SendCmdWaitInt( UINT8 mCmd );                                              /* �����������,�ȴ��ж� */

UINT8	CH376SendCmdDatWaitInt( UINT8 mCmd, UINT8 mDat );                               /* �����������һ�ֽ����ݺ�,�ȴ��ж� */

UINT8	CH376DiskReqSense( void );                                                      /* ���USB�洢������ */

UINT8	CH376DiskConnect( void );                                                       /* ���U���Ƿ�����,��֧��SD�� */

UINT8	CH376DiskMount( void );                                                         /* ��ʼ�����̲����Դ����Ƿ���� */

UINT8	CH376FileOpen( PUINT8 name );                                                   /* �ڸ�Ŀ¼���ߵ�ǰĿ¼�´��ļ�����Ŀ¼(�ļ���) */

UINT8	CH376FileCreate( PUINT8 name );                                                 /* �ڸ�Ŀ¼���ߵ�ǰĿ¼���½��ļ�,����ļ��Ѿ�������ô��ɾ�� */

UINT8	CH376DirCreate( PUINT8 name );                                                  /* �ڸ�Ŀ¼���½�Ŀ¼(�ļ���)����,���Ŀ¼�Ѿ�������ôֱ�Ӵ� */

UINT8	CH376SeparatePath( PUINT8 path );                                               /* ��·���з�������һ���ļ�������Ŀ¼(�ļ���)��,�������һ���ļ�������Ŀ¼�����ֽ�ƫ�� */

UINT8	CH376FileOpenDir( PUINT8 PathName, UINT8 StopName );                            /* �򿪶༶Ŀ¼�µ��ļ�����Ŀ¼���ϼ�Ŀ¼,֧�ֶ༶Ŀ¼·��,֧��·���ָ���,·�����Ȳ�����255���ַ� */
/* StopName ָ�����һ���ļ�������Ŀ¼�� */

UINT8	CH376FileOpenPath( PUINT8 PathName );                                           /* �򿪶༶Ŀ¼�µ��ļ�����Ŀ¼(�ļ���),֧�ֶ༶Ŀ¼·��,֧��·���ָ���,·�����Ȳ�����255���ַ� */

UINT8	CH376FileCreatePath( PUINT8 PathName );                                         /* �½��༶Ŀ¼�µ��ļ�,֧�ֶ༶Ŀ¼·��,֧��·���ָ���,·�����Ȳ�����255���ַ� */

#ifdef	EN_DIR_CREATE
UINT8	CH376DirCreatePath( PUINT8 PathName );                                          /* �½��༶Ŀ¼�µ�Ŀ¼(�ļ���)����,֧�ֶ༶Ŀ¼·��,֧��·���ָ���,·�����Ȳ�����255���ַ� */
#endif

UINT8	CH376FileErase( PUINT8 PathName );                                              /* ɾ���ļ�,����Ѿ�����ֱ��ɾ��,��������ļ����ȴ���ɾ��,֧�ֶ༶Ŀ¼·�� */

UINT8	CH376FileClose( UINT8 UpdateSz );                                               /* �رյ�ǰ�Ѿ��򿪵��ļ�����Ŀ¼(�ļ���) */

UINT8	CH376DirInfoRead( void );                                                       /* ��ȡ��ǰ�ļ���Ŀ¼��Ϣ */

UINT8	CH376DirInfoSave( void );                                                       /* �����ļ���Ŀ¼��Ϣ */

UINT8	CH376ByteLocate( UINT32 offset );                                               /* ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */

UINT8	CH376ByteRead( PUINT8 buf, UINT16 ReqCount, PUINT16 RealCount );                /* ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */

UINT8	CH376ByteWrite( PUINT8 buf, UINT16 ReqCount, PUINT16 RealCount );               /* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */

UINT8	CH376DiskCapacity( PUINT32 DiskCap );                                           /* ��ѯ������������,������ */

UINT8   CH376DiskQuery( PUINT32 DiskFre );                                              /* ��ѯ����ʣ��ռ���Ϣ,������ */

UINT8	CH376SecLocate( UINT32 offset );                                                /* ������Ϊ��λ�ƶ���ǰ�ļ�ָ�� */

#ifdef	EN_SECTOR_ACCESS

UINT8	CH376DiskReadSec( PUINT8 buf, UINT32 iLbaStart, UINT8 iSectorCount );           /* ��U�̶�ȡ������������ݿ鵽������,��֧��SD�� */

UINT8	CH376DiskWriteSec( PUINT8 buf, UINT32 iLbaStart, UINT8 iSectorCount );          /* ���������еĶ�����������ݿ�д��U��,��֧��SD�� */

UINT8	CH376SecRead( PUINT8 buf, UINT8 ReqCount, PUINT8 RealCount );                   /* ������Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ�,��֧��SD�� */

UINT8	CH376SecWrite( PUINT8 buf, UINT8 ReqCount, PUINT8 RealCount );                  /* ������Ϊ��λ�ڵ�ǰλ��д�����ݿ�,��֧��SD�� */

#endif

#ifdef	EN_LONG_NAME

UINT8	CH376LongNameWrite( PUINT8 buf, UINT16 ReqCount );                              /* ���ļ���ר�õ��ֽ�д�ӳ��� */

UINT8	CH376CheckNameSum( PUINT8 DirName );                                            /* ���㳤�ļ����Ķ��ļ��������,����Ϊ��С����ָ����Ĺ̶�11�ֽڸ�ʽ */

UINT8	CH376LocateInUpDir( PUINT8 PathName );                                          /* ���ϼ�Ŀ¼(�ļ���)���ƶ��ļ�ָ�뵽��ǰ�ļ�Ŀ¼��Ϣ���ڵ����� */
/* ����,˳�㽫��ǰ�ļ�Ŀ¼��Ϣ���ڵ�������ǰһ��������LBA��ַд��CH376�ڲ�VAR_FAT_DIR_LBA����(Ϊ�˷����ռ����ļ���ʱ��ǰ����,����Ҫ���ƶ�һ��) */
/* ʹ����ȫ�ֻ�����GlobalBuf��ǰ12���ֽ� */

UINT8	CH376GetLongName( PUINT8 PathName, PUINT8 LongName );                           /* �ɶ��ļ�������Ŀ¼(�ļ���)�������Ӧ�ĳ��ļ��� */
/* ��Ҫ������ļ���������·��PathName,��Ҫ�ṩ���������ճ��ļ���LongName(��UNICODEС�˱���,��˫0����) */
/* ʹ����ȫ�ֻ�����GlobalBuf��ǰ34���ֽ�,sizeof(GlobalBuf)>=sizeof(FAT_DIR_INFO)+2 */

UINT8	CH376CreateLongName( PUINT8 PathName, PUINT8 LongName );                        /* �½����г��ļ������ļ�,�ر��ļ��󷵻�,LongName����·��������RAM�� */
/* ��Ҫ������ļ���������·��PathName(�����Ȳο�FAT�淶�ɳ��ļ������в���),��Ҫ������UNICODEС�˱������˫0�����ĳ��ļ���LongName */
/* ʹ����ȫ�ֻ�����GlobalBuf��ǰ64���ֽ�,sizeof(GlobalBuf)>=sizeof(FAT_DIR_INFO)*2 */

#endif

#endif


