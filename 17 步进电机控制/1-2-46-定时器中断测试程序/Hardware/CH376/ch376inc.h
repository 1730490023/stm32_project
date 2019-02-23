#ifndef __CH376INC_H__
#define __CH376INC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* �������ͺͳ������� */

#ifndef		TRUE
#define		TRUE	1
#define		FALSE	0
#endif
#ifndef		NULL
#define		NULL	0
#endif

#ifndef UINT8
typedef unsigned char                UINT8;
#endif
#ifndef UINT16
typedef unsigned short               UINT16;
#endif
#ifndef UINT32
typedef unsigned long                UINT32;
#endif
#ifndef PUINT8
typedef unsigned char               *PUINT8;
#endif
#ifndef PUINT16
typedef unsigned short              *PUINT16;
#endif
#ifndef PUINT32
typedef unsigned long               *PUINT32;
#endif
#ifndef UINT8V
typedef unsigned char volatile       UINT8V;
#endif
#ifndef PUINT8V
typedef unsigned char volatile      *PUINT8V;
#endif

/* Ӳ������ */

#define		CH376_DAT_BLOCK_LEN		0x40	/* USB�������ݰ�, ���ݿ����󳤶�, Ĭ�ϻ������ĳ��� */

/* ********************************************************************************************************************* */
/* ������� */
/* �����������CH375оƬ, �����������ݻ���������ݵĿ��ֲܾ���ͬ) */
/* һ���������˳�����:
          һ��������(���ڴ��ڷ�ʽ,������֮ǰ����Ҫ����ͬ����),
          ���ɸ���������(������0��),
          �����ж�֪ͨ ���� ���ɸ��������(������0��), ��ѡһ, ���ж�֪ͨ��һ��û���������, �����������һ���������ж�
       ��CMD01_WR_REQ_DATA��������, ˳�����: һ��������, һ���������, ���ɸ���������
   ��������������: CMDxy_NAME
       ���е�x��y��������, x˵�������������ݸ���(�ֽ���), y˵������������ݸ���(�ֽ���), y�����H��˵�������ж�֪ͨ,
       ��Щ�����ܹ�ʵ��0������ֽڵ����ݿ��д, ���ݿ鱾����ֽ���δ����������x��y֮�� */
/* ���ļ�Ĭ�ϻ�ͬʱ�ṩ��CH375оƬ��������ݵ��������ʽ����ȥ��x��y֮��), �������Ҫ, ��ô���Զ���_NO_CH375_COMPATIBLE_��ֹ */

/* ********************************************************************************************************************* */
/* ��Ҫ����(�ֲ�һ), ���� */

#define	CMD01_GET_IC_VER	0x01			/* ��ȡоƬ���̼��汾 */
/* ���: �汾��( λ7Ϊ0, λ6Ϊ1, λ5~λ0Ϊ�汾�� ) */
/*           CH376���ذ汾�ŵ�ֵΪ041H���汾��Ϊ01H */

#define	CMD21_SET_BAUDRATE	0x02			/* ���ڷ�ʽ: ���ô���ͨѶ������(�ϵ���߸�λ���Ĭ�ϲ�����Ϊ9600bps,��D4/D5/D6����ѡ��) */
/* ����: �����ʷ�Ƶϵ��, �����ʷ�Ƶ���� */
/* ���: ����״̬( CMD_RET_SUCCESS��CMD_RET_ABORT, ����ֵ˵������δ��� ) */

#define	CMD00_ENTER_SLEEP	0x03			/* ����˯��״̬ */

#define	CMD00_RESET_ALL		0x05			/* ִ��Ӳ����λ */

#define	CMD11_CHECK_EXIST	0x06			/* ����ͨѶ�ӿں͹���״̬ */
/* ����: �������� */
/* ���: �������ݵİ�λȡ�� */

#define	CMD20_CHK_SUSPEND	0x0B			/* �豸��ʽ: ���ü��USB���߹���״̬�ķ�ʽ */
/* ����: ����10H, ��鷽ʽ */
/*           00H=�����USB����, 04H=��50mSΪ������USB����, 05H=��10mSΪ������USB���� */

#define	CMD20_SET_SDO_INT	0x0B			/* SPI�ӿڷ�ʽ: ����SPI��SDO���ŵ��жϷ�ʽ */
/* ����: ����16H, �жϷ�ʽ */
/*           10H=��ֹSDO���������ж����,��SCSƬѡ��Чʱ��̬�����ֹ, 90H=SDO������SCSƬѡ��Чʱ�����ж�������� */

#define	CMD14_GET_FILE_SIZE	0x0C			/* �����ļ�ģʽ: ��ȡ��ǰ�ļ����� */
/* ����: ����68H */
/* ���: ��ǰ�ļ�����(�ܳ���32λ,���ֽ���ǰ) */

#define	CMD50_SET_FILE_SIZE	0x0D			/* �����ļ�ģʽ: ���õ�ǰ�ļ����� */
/* ����: ����68H, ��ǰ�ļ�����(�ܳ���32λ,���ֽ���ǰ) */

#define	CMD11_SET_USB_MODE	0x15			/* ����USB����ģʽ */
//00H=δ���õ��豸��ʽ, 01H=�����õ��豸��ʽ����ʹ���ⲿ�̼�ģʽ(���ڲ�֧��), 
//02H=�����õ��豸��ʽ����ʹ�����ù̼�ģʽ 03H=SD������ģʽ/δ���õ�����ģʽ,���ڹ���ʹ�ȡSD���е��ļ� 
//04H=δ���õ�������ʽ, 05H=�����õ�������ʽ, 06H=�����õ�������ʽ�����Զ�����SOF��, 07H=�����õ�������ʽ���Ҹ�λUSB���� */
//���: ����״̬( CMD_RET_SUCCESS��CMD_RET_ABORT, ����ֵ˵������δ��� ) 

#define	CMD01_GET_STATUS	0x22			/* ��ȡ�ж�״̬��ȡ���ж����� */
/* ���: �ж�״̬ */

#define	CMD00_UNLOCK_USB	0x23			/* �豸��ʽ: �ͷŵ�ǰUSB������ */

#define	CMD01_RD_USB_DATA0	0x27			/* �ӵ�ǰUSB�жϵĶ˵㻺�������������˵�Ľ��ջ�������ȡ���ݿ� */
/* ���: ����, ������ */

#define	CMD01_RD_USB_DATA	0x28			/* �豸��ʽ: �ӵ�ǰUSB�жϵĶ˵㻺������ȡ���ݿ�, ���ͷŻ�����, �൱�� CMD01_RD_USB_DATA0 + CMD00_UNLOCK_USB */
/* ���: ����, ������ */

#define	CMD10_WR_USB_DATA7	0x2B			/* �豸��ʽ: ��USB�˵�2�ķ��ͻ�����д�����ݿ� */
/* ����: ����, ������ */

#define	CMD10_WR_HOST_DATA	0x2C			/* ��USB�����˵�ķ��ͻ�����д�����ݿ� */
/* ����: ����, ������ */

#define	CMD01_WR_REQ_DATA	0x2D			/* ���ڲ�ָ��������д����������ݿ� */
/* ���: ���� */
/* ����: ������ */

#define	CMD20_WR_OFS_DATA	0x2E			/* ���ڲ�������ָ��ƫ�Ƶ�ַд�����ݿ� */
/* ����: ƫ��, ����, ������ */

#define	CMD10_SET_FILE_NAME	0x2F			/* �����ļ�ģʽ: ���ý�Ҫ�������ļ����ļ��� */
/* ����: ��0�������ַ���(��������0���ڳ��Ȳ�����14���ַ�) */

/* ********************************************************************************************************************* */
/* ��Ҫ����(�ֲ�һ), ����, �������������ڲ�������ʱ�����ж�֪ͨ, ��������û��������� */

#define	CMD0H_DISK_CONNECT	0x30			/* �����ļ�ģʽ/��֧��SD��: �������Ƿ����� */
/* ����ж� */

#define	CMD0H_DISK_MOUNT	0x31			/* �����ļ�ģʽ: ��ʼ�����̲����Դ����Ƿ���� */
/* ����ж� */

#define	CMD0H_FILE_OPEN		0x32			/* �����ļ�ģʽ: ���ļ�����Ŀ¼(�ļ���),����ö���ļ���Ŀ¼(�ļ���) */
/* ����ж� */

#define	CMD0H_FILE_ENUM_GO	0x33			/* �����ļ�ģʽ: ����ö���ļ���Ŀ¼(�ļ���) */
/* ����ж� */

#define	CMD0H_FILE_CREATE	0x34			/* �����ļ�ģʽ: �½��ļ�,����ļ��Ѿ�������ô��ɾ�� */
/* ����ж� */

#define	CMD0H_FILE_ERASE	0x35			/* �����ļ�ģʽ: ɾ���ļ�,����Ѿ�����ֱ��ɾ��,��������ļ����ȴ���ɾ��,��Ŀ¼�����ȴ� */
/* ����ж� */

#define	CMD1H_FILE_CLOSE	0x36			/* �����ļ�ģʽ: �رյ�ǰ�Ѿ��򿪵��ļ�����Ŀ¼(�ļ���) */
/* ����: �Ƿ���������ļ����� */
/*          00H=��ֹ���³���, 01H=������³��� */
/* ����ж� */

#define	CMD1H_DIR_INFO_READ	0x37			/* �����ļ�ģʽ: ��ȡ�ļ���Ŀ¼��Ϣ */
/* ����: ָ����Ҫ��ȡ��Ŀ¼��Ϣ�ṹ�������ڵ������� */
/*           �����ŷ�ΧΪ00H~0FH, ������0FFH��Ϊ��ǰ�Ѿ��򿪵��ļ� */
/* ����ж� */

#define	CMD0H_DIR_INFO_SAVE	0x38			                                            /* �����ļ�ģʽ: �����ļ���Ŀ¼��Ϣ */
/* ����ж� */

#define	CMD4H_BYTE_LOCATE	0x39			                                            /* �����ļ�ģʽ: ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
/* ����: ƫ���ֽ���(�ܳ���32λ,���ֽ���ǰ) */
/* ����ж� */

#define	CMD2H_BYTE_READ		0x3A			                                            /* �����ļ�ģʽ: ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */
/* ����: �����ȡ���ֽ���(�ܳ���16λ,���ֽ���ǰ) */
/* ����ж� */

#define	CMD0H_BYTE_RD_GO	0x3B			/* �����ļ�ģʽ: �����ֽڶ� */
/* ����ж� */

#define	CMD2H_BYTE_WRITE	0x3C			/* �����ļ�ģʽ: ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
/* ����: ����д����ֽ���(�ܳ���16λ,���ֽ���ǰ) */
/* ����ж� */

#define	CMD0H_BYTE_WR_GO	0x3D			/* �����ļ�ģʽ: �����ֽ�д */
/* ����ж� */

#define	CMD0H_DISK_CAPACITY	0x3E			/* �����ļ�ģʽ: ��ѯ������������ */
/* ����ж� */

#define	CMD0H_DISK_QUERY	0x3F			/* �����ļ�ģʽ: ��ѯ���̿ռ���Ϣ */
/* ����ж� */

#define	CMD0H_DIR_CREATE	0x40			/* �����ļ�ģʽ: �½�Ŀ¼(�ļ���)����,���Ŀ¼�Ѿ�������ôֱ�Ӵ� */
/* ����ж� */

#define	CMD4H_SEC_LOCATE	0x4A			/* �����ļ�ģʽ: ������Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
/* ����: ƫ��������(�ܳ���32λ,���ֽ���ǰ) */
/* ����ж� */

#define	CMD1H_SEC_READ		0x4B			/* �����ļ�ģʽ/��֧��SD��: ������Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */
/* ����: �����ȡ�������� */
/* ����ж� */

#define	CMD1H_SEC_WRITE		0x4C			/* �����ļ�ģʽ/��֧��SD��: ������Ϊ��λ�ڵ�ǰλ��д�����ݿ� */
/* ����: ����д��������� */
/* ����ж� */

#define	CMD0H_DISK_BOC_CMD	0x50			/* ������ʽ/��֧��SD��: ��USB�洢��ִ��BulkOnly����Э������� */
/* ����ж� */

#define	CMD5H_DISK_READ		0x54			/* ������ʽ/��֧��SD��: ��USB�洢������������ */
/* ����: LBA����������ַ(�ܳ���32λ, ���ֽ���ǰ), ������(01H~FFH) */
/* ����ж� */

#define	CMD0H_DISK_RD_GO	0x55			/* ������ʽ/��֧��SD��: ����ִ��USB�洢������������������ */
/* ����ж� */

#define	CMD5H_DISK_WRITE	0x56			/* ������ʽ/��֧��SD��: ��USB�洢��д�������� */
/* ����: LBA����������ַ(�ܳ���32λ, ���ֽ���ǰ), ������(01H~FFH) */
/* ����ж� */

#define	CMD0H_DISK_WR_GO	0x57			/* ������ʽ/��֧��SD��: ����ִ��USB�洢������������д���� */
/* ����ж� */

/* ********************************************************************************************************************* */
/* ��������(�ֲ��), ��̫���û�����Ϊ����CH375��CH372���� */

#define	CMD10_SET_USB_SPEED	0x04			/* ����USB�����ٶ�, ��ÿ��CMD11_SET_USB_MODE����USB����ģʽʱ���Զ��ָ���12Mbpsȫ�� */
/* ����: �����ٶȴ��� */
/*           00H=12Mbpsȫ��FullSpeed��Ĭ��ֵ��, 01H=1.5Mbps�����޸�Ƶ�ʣ�, 02H=1.5Mbps����LowSpeed */

#define	CMD11_GET_DEV_RATE	0x0A			/* ������ʽ: ��ȡ��ǰ���ӵ�USB�豸�������������� */
/* ����: ����07H */
/* ���: ������������ */
/*           λ4Ϊ1����1.5Mbps����USB�豸, ������12Mbpsȫ��USB�豸 */

#define	CMD11_GET_TOGGLE	0x0A			/* ��ȡOUT�����ͬ��״̬ */
/* ����: ����1AH */
/* ���: ͬ��״̬ */
/*           λ4Ϊ1��OUT����ͬ��, ����OUT����ͬ�� */

#define	CMD11_READ_VAR8		0x0A			/* ��ȡָ����8λ�ļ�ϵͳ���� */
/* ����: ������ַ */
/* ���: ���� */

/*#define	CMD11_GET_MAX_LUN	= CMD11_READ_VAR8( VAR_UDISK_LUN )*/	/* ������ʽ: ��ȡUSB�洢�����͵�ǰ�߼���Ԫ�� */

#define	CMD20_SET_RETRY		0x0B			/* ������ʽ: ����USB������������Դ��� */
/* ����: ����25H, ���Դ��� */
/*       λ7Ϊ0���յ�NAKʱ������, λ7Ϊ1λ6Ϊ0���յ�NAKʱ��������, λ7Ϊ1λ6Ϊ1���յ�NAKʱ�������3��, λ5~λ0Ϊ��ʱ������Դ��� */

#define	CMD20_WRITE_VAR8	0x0B			/* ����ָ����8λ�ļ�ϵͳ���� */
/* ����: ������ַ, ���� */

/*#define	CMD20_SET_DISK_LUN	= CMD20_WRITE_VAR8( VAR_UDISK_LUN )*/	/* ������ʽ: ����USB�洢���ĵ�ǰ�߼���Ԫ�� */

#define	CMD14_READ_VAR32	0x0C			/* ��ȡָ����32λ�ļ�ϵͳ���� */
/* ����: ������ַ */
/* ���: ����(�ܳ���32λ,���ֽ���ǰ) */

#define	CMD50_WRITE_VAR32	0x0D			/* ����ָ����32λ�ļ�ϵͳ���� */
/* ����: ������ַ, ����(�ܳ���32λ,���ֽ���ǰ) */

#define	CMD01_DELAY_100US	0x0F			/* ��ʱ100uS(���ڲ�֧��) */
/* ���: ��ʱ�ڼ����0,��ʱ���������0 */

#define	CMD40_SET_USB_ID	0x12			/* �豸��ʽ: ����USB����VID�Ͳ�ƷPID */
/* ����: ����ID���ֽ�, ����ID���ֽ�, ��ƷID���ֽ�, ��ƷID���ֽ� */

#define	CMD10_SET_USB_ADDR	0x13			/* ����USB��ַ */
/* ����: ��ֵַ */

#define	CMD01_TEST_CONNECT	0x16			/* ������ʽ/��֧��SD��: ���USB�豸����״̬ */
/* ���: ״̬( USB_INT_CONNECT��USB_INT_DISCONNECT��USB_INT_USB_READY, ����ֵ˵������δ��� ) */

#define	CMD00_ABORT_NAK		0x17			/* ������ʽ: ������ǰNAK������ */

#define	CMD10_SET_ENDP2		0x18			/* �豸��ʽ(���ڲ�֧��): ����USB�˵�0�Ľ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD10_SET_ENDP3		0x19			/* �豸��ʽ(���ڲ�֧��): ����USB�˵�0�ķ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000~1000-����ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD10_SET_ENDP4		0x1A			/* �豸��ʽ(���ڲ�֧��): ����USB�˵�1�Ľ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD10_SET_ENDP5		0x1B			/* �豸��ʽ(���ڲ�֧��): ����USB�˵�1�ķ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000~1000-����ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD10_SET_ENDP6		0x1C			/* ����USB�˵�2/�����˵�Ľ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1101-������������ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD10_SET_ENDP7		0x1D			/* ����USB�˵�2/�����˵�ķ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1101-����������Ӧ��, 1110-��æNAK, 1111-����STALL */

#define	CMD00_DIRTY_BUFFER	0x25			/* �����ļ�ģʽ: ����ڲ��Ĵ��̺��ļ������� */

#define	CMD10_WR_USB_DATA3	0x29			/* �豸��ʽ(���ڲ�֧��): ��USB�˵�0�ķ��ͻ�����д�����ݿ� */
/* ����: ����, ������ */

#define	CMD10_WR_USB_DATA5	0x2A			/* �豸��ʽ(���ڲ�֧��): ��USB�˵�1�ķ��ͻ�����д�����ݿ� */
/* ����: ����, ������ */

/* ********************************************************************************************************************* */
/* ��������(�ֲ��), ��̫���û�����Ϊ����CH375��CH372����, �������������ڲ�������ʱ�����ж�֪ͨ, ��������û��������� */

#define	CMD1H_CLR_STALL		0x41			/* ������ʽ: ���ƴ���-����˵���� */
/* ����: �˵�� */
/* ����ж� */

#define	CMD1H_SET_ADDRESS	0x45			/* ������ʽ: ���ƴ���-����USB��ַ */
/* ����: ��ֵַ */
/* ����ж� */

#define	CMD1H_GET_DESCR		0x46			/* ������ʽ: ���ƴ���-��ȡ������ */
/* ����: ���������� */
/* ����ж� */

#define	CMD1H_SET_CONFIG	0x49			/* ������ʽ: ���ƴ���-����USB���� */
/* ����: ����ֵ */
/* ����ж� */

#define	CMD0H_AUTO_SETUP	0x4D			/* ������ʽ/��֧��SD��: �Զ�����USB�豸 */
/* ����ж� */

#define	CMD2H_ISSUE_TKN_X	0x4E			/* ������ʽ: ����ͬ������, ִ������, ������ɴ��� CMD10_SET_ENDP6/CMD10_SET_ENDP7 + CMD1H_ISSUE_TOKEN */
/* ����: ͬ����־, �������� */
/*           ͬ����־��λ7Ϊ�����˵�IN��ͬ������λ, λ6Ϊ�����˵�OUT��ͬ������λ, λ5~λ0����Ϊ0 */
/*           �������Եĵ�4λ������, ��4λ�Ƕ˵�� */
/* ����ж� */

#define	CMD1H_ISSUE_TOKEN	0x4F			/* ������ʽ: ��������, ִ������, ������CMD2H_ISSUE_TKN_X���� */
/* ����: �������� */
/*           ��4λ������, ��4λ�Ƕ˵�� */
/* ����ж� */

#define	CMD0H_DISK_INIT		0x51			/* ������ʽ/��֧��SD��: ��ʼ��USB�洢�� */
/* ����ж� */

#define	CMD0H_DISK_RESET	0x52			/* ������ʽ/��֧��SD��: ���ƴ���-��λUSB�洢�� */
/* ����ж� */

#define	CMD0H_DISK_SIZE		0x53			/* ������ʽ/��֧��SD��: ��ȡUSB�洢�������� */
/* ����ж� */

#define	CMD0H_DISK_INQUIRY	0x58			/* ������ʽ/��֧��SD��: ��ѯUSB�洢������ */
/* ����ж� */

#define	CMD0H_DISK_READY	0x59			/* ������ʽ/��֧��SD��: ���USB�洢������ */
/* ����ж� */

#define	CMD0H_DISK_R_SENSE	0x5A			/* ������ʽ/��֧��SD��: ���USB�洢������ */
/* ����ж� */

#define	CMD0H_RD_DISK_SEC	0x5B			/* �����ļ�ģʽ: �Ӵ��̶�ȡһ�����������ݵ��ڲ������� */
/* ����ж� */

#define	CMD0H_WR_DISK_SEC	0x5C			/* �����ļ�ģʽ: ���ڲ���������һ������������д����� */
/* ����ж� */

#define	CMD0H_DISK_MAX_LUN	0x5D			/* ������ʽ: ���ƴ���-��ȡUSB�洢������߼���Ԫ�� */
/* ����ж� */

/* ********************************************************************************************************************* */
/* ���¶���ֻ��Ϊ�˼���CH375��INCLUDE�ļ��е��������Ƹ�ʽ */

#ifndef	_NO_CH375_COMPATIBLE_
#define	CMD_GET_IC_VER		CMD01_GET_IC_VER
#define	CMD_SET_BAUDRATE	CMD21_SET_BAUDRATE
#define	CMD_ENTER_SLEEP		CMD00_ENTER_SLEEP
#define	CMD_RESET_ALL		CMD00_RESET_ALL
#define	CMD_CHECK_EXIST		CMD11_CHECK_EXIST
#define	CMD_CHK_SUSPEND		CMD20_CHK_SUSPEND
#define	CMD_SET_SDO_INT		CMD20_SET_SDO_INT
#define	CMD_GET_FILE_SIZE	CMD14_GET_FILE_SIZE
#define	CMD_SET_FILE_SIZE	CMD50_SET_FILE_SIZE
#define	CMD_SET_USB_MODE	CMD11_SET_USB_MODE
#define	CMD_GET_STATUS		CMD01_GET_STATUS
#define	CMD_UNLOCK_USB		CMD00_UNLOCK_USB
#define	CMD_RD_USB_DATA0	CMD01_RD_USB_DATA0
#define	CMD_RD_USB_DATA		CMD01_RD_USB_DATA
#define	CMD_WR_USB_DATA7	CMD10_WR_USB_DATA7
#define	CMD_WR_HOST_DATA	CMD10_WR_HOST_DATA
#define	CMD_WR_REQ_DATA		CMD01_WR_REQ_DATA
#define	CMD_WR_OFS_DATA		CMD20_WR_OFS_DATA
#define	CMD_SET_FILE_NAME	CMD10_SET_FILE_NAME
#define	CMD_DISK_CONNECT	CMD0H_DISK_CONNECT
#define	CMD_DISK_MOUNT		CMD0H_DISK_MOUNT
#define	CMD_FILE_OPEN		CMD0H_FILE_OPEN
#define	CMD_FILE_ENUM_GO	CMD0H_FILE_ENUM_GO
#define	CMD_FILE_CREATE		CMD0H_FILE_CREATE
#define	CMD_FILE_ERASE		CMD0H_FILE_ERASE
#define	CMD_FILE_CLOSE		CMD1H_FILE_CLOSE
#define	CMD_DIR_INFO_READ	CMD1H_DIR_INFO_READ
#define	CMD_DIR_INFO_SAVE	CMD0H_DIR_INFO_SAVE
#define	CMD_BYTE_LOCATE		CMD4H_BYTE_LOCATE
#define	CMD_BYTE_READ		CMD2H_BYTE_READ
#define	CMD_BYTE_RD_GO		CMD0H_BYTE_RD_GO
#define	CMD_BYTE_WRITE		CMD2H_BYTE_WRITE
#define	CMD_BYTE_WR_GO		CMD0H_BYTE_WR_GO
#define	CMD_DISK_CAPACITY	CMD0H_DISK_CAPACITY
#define	CMD_DISK_QUERY		CMD0H_DISK_QUERY
#define	CMD_DIR_CREATE		CMD0H_DIR_CREATE
#define	CMD_SEC_LOCATE		CMD4H_SEC_LOCATE
#define	CMD_SEC_READ		CMD1H_SEC_READ
#define	CMD_SEC_WRITE		CMD1H_SEC_WRITE
#define	CMD_DISK_BOC_CMD	CMD0H_DISK_BOC_CMD
#define	CMD_DISK_READ		CMD5H_DISK_READ
#define	CMD_DISK_RD_GO		CMD0H_DISK_RD_GO
#define	CMD_DISK_WRITE		CMD5H_DISK_WRITE
#define	CMD_DISK_WR_GO		CMD0H_DISK_WR_GO
#define	CMD_SET_USB_SPEED	CMD10_SET_USB_SPEED
#define	CMD_GET_DEV_RATE	CMD11_GET_DEV_RATE
#define	CMD_GET_TOGGLE		CMD11_GET_TOGGLE
#define	CMD_READ_VAR8		CMD11_READ_VAR8
#define	CMD_SET_RETRY		CMD20_SET_RETRY
#define	CMD_WRITE_VAR8		CMD20_WRITE_VAR8
#define	CMD_READ_VAR32		CMD14_READ_VAR32
#define	CMD_WRITE_VAR32		CMD50_WRITE_VAR32
#define	CMD_DELAY_100US		CMD01_DELAY_100US
#define	CMD_SET_USB_ID		CMD40_SET_USB_ID
#define	CMD_SET_USB_ADDR	CMD10_SET_USB_ADDR
#define	CMD_TEST_CONNECT	CMD01_TEST_CONNECT
#define	CMD_ABORT_NAK		CMD00_ABORT_NAK
#define	CMD_SET_ENDP2		CMD10_SET_ENDP2
#define	CMD_SET_ENDP3		CMD10_SET_ENDP3
#define	CMD_SET_ENDP4		CMD10_SET_ENDP4
#define	CMD_SET_ENDP5		CMD10_SET_ENDP5
#define	CMD_SET_ENDP6		CMD10_SET_ENDP6
#define	CMD_SET_ENDP7		CMD10_SET_ENDP7
#define	CMD_DIRTY_BUFFER	CMD00_DIRTY_BUFFER
#define	CMD_WR_USB_DATA3	CMD10_WR_USB_DATA3
#define	CMD_WR_USB_DATA5	CMD10_WR_USB_DATA5
#define	CMD_CLR_STALL		CMD1H_CLR_STALL
#define	CMD_SET_ADDRESS		CMD1H_SET_ADDRESS
#define	CMD_GET_DESCR		CMD1H_GET_DESCR
#define	CMD_SET_CONFIG		CMD1H_SET_CONFIG
#define	CMD_AUTO_SETUP		CMD0H_AUTO_SETUP
#define	CMD_ISSUE_TKN_X		CMD2H_ISSUE_TKN_X
#define	CMD_ISSUE_TOKEN		CMD1H_ISSUE_TOKEN
#define	CMD_DISK_INIT		CMD0H_DISK_INIT
#define	CMD_DISK_RESET		CMD0H_DISK_RESET
#define	CMD_DISK_SIZE		CMD0H_DISK_SIZE
#define	CMD_DISK_INQUIRY	CMD0H_DISK_INQUIRY
#define	CMD_DISK_READY		CMD0H_DISK_READY
#define	CMD_DISK_R_SENSE	CMD0H_DISK_R_SENSE
#define	CMD_RD_DISK_SEC		CMD0H_RD_DISK_SEC
#define	CMD_WR_DISK_SEC		CMD0H_WR_DISK_SEC
#define	CMD_DISK_MAX_LUN	CMD0H_DISK_MAX_LUN
#endif

/* ********************************************************************************************************************* */
/* ���ڷ�ʽ, ״̬�˿�(������˿�)��λ���� */
#ifndef	PARA_STATE_INTB
#define	PARA_STATE_INTB		0x80			/* ���ڷ�ʽ״̬�˿ڵ�λ7: �жϱ�־,����Ч */
#define	PARA_STATE_BUSY		0x10			/* ���ڷ�ʽ״̬�˿ڵ�λ4: æ��־,����Ч */
#endif

/* ********************************************************************************************************************* */
/* ���ڷ�ʽ, ��������ǰ������ͬ���� */
#ifndef	SER_CMD_TIMEOUT
#define	SER_CMD_TIMEOUT		32				/* �������ʱʱ��, ��λΪmS, ͬ����֮�估ͬ������������֮��ļ��Ӧ�þ�����, ��ʱ��Ĵ���ʽΪ���� */
#define	SER_SYNC_CODE1		0x57			/* ���������ĵ�1������ͬ���� */
#define	SER_SYNC_CODE2		0xAB			/* ���������ĵ�2������ͬ���� */
#endif

/* ********************************************************************************************************************* */
/* ����״̬ */

#ifndef	CMD_RET_SUCCESS
#define	CMD_RET_SUCCESS		0x51			/* ��������ɹ� */
#define	CMD_RET_ABORT		0x5F			/* �������ʧ�� */
#endif

/* ********************************************************************************************************************* */
/* USB�ж�״̬ */

#ifndef	USB_INT_EP0_SETUP

/* ����״̬����Ϊ�����¼��ж�, ���ͨ��CMD20_CHK_SUSPEND����USB���߹�����, ��ô���봦��USB���߹����˯�߻��ѵ��ж�״̬ */
#define	USB_INT_USB_SUSPEND	0x05			/* USB���߹����¼� */
#define	USB_INT_WAKE_UP		0x06			/* ��˯���б������¼� */

/* ����״̬����0XH����USB�豸��ʽ */
/*   ���ù̼�ģʽ��ֻ��Ҫ����: USB_INT_EP1_OUT, USB_INT_EP1_IN, USB_INT_EP2_OUT, USB_INT_EP2_IN */
/*   λ7-λ4Ϊ0000 */
/*   λ3-λ2ָʾ��ǰ����, 00=OUT, 10=IN, 11=SETUP */
/*   λ1-λ0ָʾ��ǰ�˵�, 00=�˵�0, 01=�˵�1, 10=�˵�2, 11=USB���߸�λ */
#define	USB_INT_EP0_SETUP	0x0C			/* USB�˵�0��SETUP */
#define	USB_INT_EP0_OUT		0x00			/* USB�˵�0��OUT */
#define	USB_INT_EP0_IN		0x08			/* USB�˵�0��IN */
#define	USB_INT_EP1_OUT		0x01			/* USB�˵�1��OUT */
#define	USB_INT_EP1_IN		0x09			/* USB�˵�1��IN */
#define	USB_INT_EP2_OUT		0x02			/* USB�˵�2��OUT */
#define	USB_INT_EP2_IN		0x0A			/* USB�˵�2��IN */
/* USB_INT_BUS_RESET	0x0000XX11B */		/* USB���߸�λ */
#define	USB_INT_BUS_RESET1	0x03			/* USB���߸�λ */
#define	USB_INT_BUS_RESET2	0x07			/* USB���߸�λ */
#define	USB_INT_BUS_RESET3	0x0B			/* USB���߸�λ */
#define	USB_INT_BUS_RESET4	0x0F			/* USB���߸�λ */

#endif

/* ����״̬����2XH-3XH����USB������ʽ��ͨѶʧ�ܴ��� */
/*   λ7-λ6Ϊ00 */
/*   λ5Ϊ1 */
/*   λ4ָʾ��ǰ���յ����ݰ��Ƿ�ͬ�� */
/*   λ3-λ0ָʾ����ͨѶʧ��ʱUSB�豸��Ӧ��: 0010=ACK, 1010=NAK, 1110=STALL, 0011=DATA0, 1011=DATA1, XX00=��ʱ */
/* USB_INT_RET_ACK	0x001X0010B */			/* ����:����IN���񷵻�ACK */
/* USB_INT_RET_NAK	0x001X1010B */			/* ����:����NAK */
/* USB_INT_RET_STALL	0x001X1110B */		/* ����:����STALL */
/* USB_INT_RET_DATA0	0x001X0011B */		/* ����:����OUT/SETUP���񷵻�DATA0 */
/* USB_INT_RET_DATA1	0x001X1011B */		/* ����:����OUT/SETUP���񷵻�DATA1 */
/* USB_INT_RET_TOUT	0x001XXX00B */			/* ����:���س�ʱ */
/* USB_INT_RET_TOGX	0x0010X011B */			/* ����:����IN���񷵻����ݲ�ͬ�� */
/* USB_INT_RET_PID	0x001XXXXXB */			/* ����:δ���� */

/* ����״̬����1XH����USB������ʽ�Ĳ���״̬���� */
#ifndef	USB_INT_SUCCESS
#define	USB_INT_SUCCESS		0x14			/* USB������ߴ�������ɹ� */
#define	USB_INT_CONNECT		0x15			/* ��⵽USB�豸�����¼�, �����������ӻ��߶Ͽ����������� */
#define	USB_INT_DISCONNECT	0x16			/* ��⵽USB�豸�Ͽ��¼� */
#define	USB_INT_BUF_OVER	0x17			/* USB��������������������̫�໺������� */
#define	USB_INT_USB_READY	0x18			/* USB�豸�Ѿ�����ʼ��(�Ѿ�����USB��ַ) */
#define	USB_INT_DISK_READ	0x1D			/* USB�洢���������ݶ��� */
#define	USB_INT_DISK_WRITE	0x1E			/* USB�洢����������д�� */
#define	USB_INT_DISK_ERR	0x1F			/* USB�洢������ʧ�� */
/* ���ӵ�USB����״̬���� */
#define ERR_USB_UNKNOWN		0xFA	    /* δ֪����,��Ӧ�÷��������,����Ӳ�����߳������ */

#endif

/* ����״̬�������������ļ�ģʽ�µ��ļ�ϵͳ������ */
#ifndef	ERR_DISK_DISCON
#define	ERR_DISK_DISCON		0x82			/* ������δ����,���ܴ����Ѿ��Ͽ� */
#define	ERR_LARGE_SECTOR	0x84			/* ���̵�����̫��,ֻ֧��ÿ����512�ֽ� */
#define	ERR_TYPE_ERROR		0x92			/* ���̷������Ͳ�֧��,ֻ֧��FAT12/FAT16/BigDOS/FAT32,��Ҫ�ɴ��̹��������·��� */
#define	ERR_BPB_ERROR		0xA1			/* ������δ��ʽ��,���߲�������,��Ҫ��WINDOWS����Ĭ�ϲ������¸�ʽ�� */
#define	ERR_DISK_FULL		0xB1			/* �����ļ�̫��,ʣ��ռ�̫�ٻ����Ѿ�û��,��Ҫ�������� */
#define	ERR_FDT_OVER		0xB2			/* Ŀ¼(�ļ���)���ļ�̫��,û�п��е�Ŀ¼��,FAT12/FAT16��Ŀ¼�µ��ļ���Ӧ������512��,��Ҫ�������� */
#define	ERR_FILE_CLOSE		0xB4			/* �ļ��Ѿ��ر�,�����Ҫʹ��,Ӧ�����´��ļ� */
#define	ERR_OPEN_DIR		0x41			/* ָ��·����Ŀ¼(�ļ���)���� */
#define	ERR_MISS_FILE		0x42			/* ָ��·�����ļ�û���ҵ�,�������ļ����ƴ��� */
#define	ERR_FOUND_NAME		0x43			/* ��������ƥ����ļ���,������Ҫ���Ŀ¼(�ļ���)��ʵ�ʽ��ȴ�����ļ� */
/* �����ļ�ϵͳ�����������ļ�ϵͳ�ӳ��� */
#define	ERR_MISS_DIR		0xB3			/* ָ��·����ĳ����Ŀ¼(�ļ���)û���ҵ�,������Ŀ¼���ƴ��� */
#define	ERR_LONG_BUF_OVER	0x48			/* ���ļ���������� */
#define	ERR_LONG_NAME_ERR	0x49			/* ���ļ���û�ж�Ӧ�ĳ��ļ������߳��ļ������� */
#define	ERR_NAME_EXIST		0x4A			/* ͬ���Ķ��ļ��Ѿ�����,����������������һ�����ļ��� */
#endif

/* ********************************************************************************************************************* */
/* ����״̬�������������ļ�ģʽ�µĴ��̼��ļ�״̬, VAR_DISK_STATUS */
#ifndef	DEF_DISK_UNKNOWN
#define	DEF_DISK_UNKNOWN	0x00			/* ��δ��ʼ��,δ֪״̬ */
#define	DEF_DISK_DISCONN	0x01			/* ����û�����ӻ����Ѿ��Ͽ� */
#define	DEF_DISK_CONNECT	0x02			/* �����Ѿ�����,������δ��ʼ�������޷�ʶ��ô��� */
#define	DEF_DISK_MOUNTED	0x03			/* �����Ѿ���ʼ���ɹ�,������δ�����ļ�ϵͳ�����ļ�ϵͳ��֧�� */
#define	DEF_DISK_READY		0x10			/* �Ѿ��������̵��ļ�ϵͳ�����ܹ�֧�� */
#define	DEF_DISK_OPEN_ROOT	0x12			/* �Ѿ��򿪸�Ŀ¼,ʹ�ú����ر�,ע��FAT12/FAT16��Ŀ¼�ǹ̶����� */
#define	DEF_DISK_OPEN_DIR	0x13			/* �Ѿ�����Ŀ¼(�ļ���) */
#define	DEF_DISK_OPEN_FILE	0x14			/* �Ѿ����ļ� */
#endif

/* ********************************************************************************************************************* */
/* �ļ�ϵͳ���ö��� */

#ifndef	DEF_SECTOR_SIZE
#define	DEF_SECTOR_SIZE		512				/* U�̻���SD��Ĭ�ϵ����������Ĵ�С */
#endif

#ifndef	DEF_WILDCARD_CHAR
#define	DEF_WILDCARD_CHAR	0x2A			/* ·������ͨ��� '*' */
#define	DEF_SEPAR_CHAR1		0x5C		/* ·�����ķָ��� '\' */
#define	DEF_SEPAR_CHAR2		0x2F		/* ·�����ķָ��� '/' */
#define	DEF_FILE_YEAR		2004			/* Ĭ���ļ�����: 2004�� */
#define	DEF_FILE_MONTH		1				/* Ĭ���ļ�����: 1�� */
#define	DEF_FILE_DATE		1				/* Ĭ���ļ�����: 1�� */
#endif

#ifndef	ATTR_DIRECTORY

/* FAT���������ļ�Ŀ¼��Ϣ */
typedef struct _FAT_DIR_INFO {
	UINT8	DIR_Name[11];					/* 00H,�ļ���,��11�ֽ�,���㴦��ո� */
	UINT8	DIR_Attr;						/* 0BH,�ļ�����,�ο������˵�� */
	UINT8	DIR_NTRes;						/* 0CH */
	UINT8	DIR_CrtTimeTenth;				/* 0DH,�ļ�������ʱ��,��0.1�뵥λ���� */
	UINT16	DIR_CrtTime;					/* 0EH,�ļ�������ʱ�� */
	UINT16	DIR_CrtDate;					/* 10H,�ļ����������� */
	UINT16	DIR_LstAccDate;					/* 12H,���һ�δ�ȡ���������� */
	UINT16	DIR_FstClusHI;					/* 14H */
	UINT16	DIR_WrtTime;					/* 16H,�ļ��޸�ʱ��,�ο�ǰ��ĺ�MAKE_FILE_TIME */
	UINT16	DIR_WrtDate;					/* 18H,�ļ��޸�����,�ο�ǰ��ĺ�MAKE_FILE_DATE */
	UINT16	DIR_FstClusLO;					/* 1AH */
	UINT32	DIR_FileSize;					/* 1CH,�ļ����� */
} FAT_DIR_INFO, *P_FAT_DIR_INFO;			/* 20H */

/* �ļ����� */
#define ATTR_READ_ONLY			0x01		/* �ļ�Ϊֻ������ */
#define ATTR_HIDDEN				0x02		/* �ļ�Ϊ�������� */
#define ATTR_SYSTEM				0x04		/* �ļ�Ϊϵͳ���� */
#define ATTR_VOLUME_ID			0x08		/* ��� */
#define ATTR_DIRECTORY			0x10		/* ��Ŀ¼(�ļ���) */
#define ATTR_ARCHIVE			0x20		/* �ļ�Ϊ�浵���� */
#define ATTR_LONG_NAME			( ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID )	/* ���ļ������� */
#define ATTR_LONG_NAME_MASK		( ATTR_LONG_NAME | ATTR_DIRECTORY | ATTR_ARCHIVE )
/* �ļ����� UINT8 */
/* bit0 bit1 bit2 bit3 bit4 bit5 bit6 bit7 */
/*  ֻ   ��   ϵ   ��   Ŀ   ��   δ����   */
/*  ��   ��   ͳ   ��   ¼   ��            */
/* �ļ�ʱ�� UINT16 */
/* Time = (Hour<<11) + (Minute<<5) + (Second>>1) */
#define MAKE_FILE_TIME( h, m, s )	( (h<<11) + (m<<5) + (s>>1) )	/* ����ָ��ʱ������ļ�ʱ������ */
/* �ļ����� UINT16 */
/* Date = ((Year-1980)<<9) + (Month<<5) + Day */
#define MAKE_FILE_DATE( y, m, d )	( ((y-1980)<<9) + (m<<5) + d )	/* ����ָ�������յ��ļ��������� */

#define LONE_NAME_MAX_CHAR		(255*2)		/* ���ļ�������ַ���/�ֽ��� */
#define LONG_NAME_PER_DIR		(13*2)		/* ���ļ�����ÿ���ļ�Ŀ¼��Ϣ�ṹ�е��ַ���/�ֽ��� */

#endif

/* ********************************************************************************************************************* */
/* SCSI�����������������ṹ */

#ifndef	SPC_CMD_INQUIRY

/* SCSI������ */
#define SPC_CMD_INQUIRY			0x12
#define SPC_CMD_READ_CAPACITY	0x25
#define SPC_CMD_READ10			0x28
#define SPC_CMD_WRITE10			0x2A
#define SPC_CMD_TEST_READY		0x00
#define SPC_CMD_REQUEST_SENSE	0x03
#define SPC_CMD_MODESENSE6		0x1A
#define SPC_CMD_MODESENSE10		0x5A
#define SPC_CMD_START_STOP		0x1B

/* BulkOnlyЭ�������� */
typedef struct _BULK_ONLY_CBW {
	UINT32	CBW_Sig;
	UINT32	CBW_Tag;
	UINT8	CBW_DataLen0;					/* 08H,����: ���ݴ��䳤��,����������������Чֵ��0��48,���������������ЧֵΪ0��33 */
	UINT8	CBW_DataLen1;
	UINT16	CBW_DataLen2;
	UINT8	CBW_Flag;						/* 0CH,����: ���䷽��ȱ�־,λ7Ϊ1����������,λΪ0��������ݻ���û������ */
	UINT8	CBW_LUN;
	UINT8	CBW_CB_Len;						/* 0EH,����: �����ĳ���,��Чֵ��1��16 */
	UINT8	CBW_CB_Buf[16];					/* 0FH,����: �����,�û��������Ϊ16���ֽ� */
} BULK_ONLY_CBW, *P_BULK_ONLY_CBW;			/* BulkOnlyЭ��������, ����CBW�ṹ */

/* INQUIRY����ķ������� */
typedef struct _INQUIRY_DATA {
	UINT8	DeviceType;					/* 00H, �豸���� */
	UINT8	RemovableMedia;				/* 01H, λ7Ϊ1˵�����ƶ��洢 */
	UINT8	Versions;					/* 02H, Э��汾 */
	UINT8	DataFormatAndEtc;			/* 03H, ָ���������ݸ�ʽ */
	UINT8	AdditionalLength;			/* 04H, �������ݵĳ��� */
	UINT8	Reserved1;
	UINT8	Reserved2;
	UINT8	MiscFlag;					/* 07H, һЩ���Ʊ�־ */
	UINT8	VendorIdStr[8];				/* 08H, ������Ϣ */
	UINT8	ProductIdStr[16];			/* 10H, ��Ʒ��Ϣ */
	UINT8	ProductRevStr[4];			/* 20H, ��Ʒ�汾 */
} INQUIRY_DATA, *P_INQUIRY_DATA;		/* 24H */

/* REQUEST SENSE����ķ������� */
typedef struct _SENSE_DATA {
	UINT8	ErrorCode;					/* 00H, ������뼰��Чλ */
	UINT8	SegmentNumber;
	UINT8	SenseKeyAndEtc;				/* 02H, ������ */
	UINT8	Information0;
	UINT8	Information1;
	UINT8	Information2;
	UINT8	Information3;
	UINT8	AdditSenseLen;				/* 07H, �������ݵĳ��� */
	UINT8	CmdSpecInfo[4];
	UINT8	AdditSenseCode;				/* 0CH, ���Ӽ��� */
	UINT8	AddSenCodeQual;				/* 0DH, ��ϸ�ĸ��Ӽ��� */
	UINT8	FieldReplaUnit;
	UINT8	SenseKeySpec[3];
} SENSE_DATA, *P_SENSE_DATA;			/* 12H */

#endif

/* ********************************************************************************************************************* */
/* �����ļ�ģʽ�µ��������������ṹ */

#ifndef	MAX_FILE_NAME_LEN

#define MAX_FILE_NAME_LEN		(13+1)		/* �ļ�����󳤶�,��󳤶���1����Ŀ¼��+8�����ļ���+1��С����+3��������+������=14 */

/* ������������ݺ�������� */
typedef union _CH376_CMD_DATA {
	struct {
		UINT8	mBuffer[ MAX_FILE_NAME_LEN ];
	} Default;

	INQUIRY_DATA	DiskMountInq;			/* ����: INQUIRY����ķ������� */
											/* CMD0H_DISK_MOUNT: ��ʼ�����̲����Դ����Ƿ����,�״�ִ��ʱ */

	FAT_DIR_INFO	OpenDirInfo;			/* ����: ö�ٵ����ļ�Ŀ¼��Ϣ */
											/* CMD0H_FILE_OPEN: ö���ļ���Ŀ¼(�ļ���) */

	FAT_DIR_INFO	EnumDirInfo;			/* ����: ö�ٵ����ļ�Ŀ¼��Ϣ */
											/* CMD0H_FILE_ENUM_GO: ����ö���ļ���Ŀ¼(�ļ���) */

	struct {
		UINT8	mUpdateFileSz;				/* �������: �Ƿ���������ļ�����, 0���ֹ���³��� */
	} FileCLose;							/* CMD1H_FILE_CLOSE: �رյ�ǰ�Ѿ��򿪵��ļ� */

	struct {
		UINT8	mDirInfoIndex;				/* �������: ָ����Ҫ��ȡ��Ŀ¼��Ϣ�ṹ�������ڵ�������, 0FFH��Ϊ��ǰ�Ѿ��򿪵��ļ� */
	} DirInfoRead;							/* CMD1H_DIR_INFO_READ: ��ȡ�ļ���Ŀ¼��Ϣ */

	union {
		UINT32	mByteOffset;				/* �������: ƫ���ֽ���,���ֽ�Ϊ��λ��ƫ����(�ܳ���32λ,���ֽ���ǰ) */
		UINT32	mSectorLba;					/* ����: ��ǰ�ļ�ָ���Ӧ�ľ�������������,0FFFFFFFFH���ѵ��ļ�β(�ܳ���32λ,���ֽ���ǰ) */
	} ByteLocate;							/* CMD4H_BYTE_LOCATE: ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */

	struct {
		UINT16	mByteCount;					/* �������: �����ȡ���ֽ���(�ܳ���16λ,���ֽ���ǰ) */
	} ByteRead;								/* CMD2H_BYTE_READ: ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */

	struct {
		UINT16	mByteCount;					/* �������: ����д����ֽ���(�ܳ���16λ,���ֽ���ǰ) */
	} ByteWrite;							/* CMD2H_BYTE_WRITE: ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */

	union {
		UINT32	mSectorOffset;				/* �������: ƫ��������,������Ϊ��λ��ƫ����(�ܳ���32λ,���ֽ���ǰ) */
		UINT32	mSectorLba;					/* ����: ��ǰ�ļ�ָ���Ӧ�ľ�������������,0FFFFFFFFH���ѵ��ļ�β(�ܳ���32λ,���ֽ���ǰ) */
	} SectorLocate;							/* CMD4H_SEC_LOCATE: ������Ϊ��λ�ƶ���ǰ�ļ�ָ�� */

	struct {
		UINT8	mSectorCount;				/* �������: �����ȡ�������� */
											/* ����: �����ȡ�������� */
		UINT8	mReserved1;
		UINT8	mReserved2;
		UINT8	mReserved3;
		UINT32	mStartSector;				/* ����: �����ȡ�����������ʼ��������������(�ܳ���32λ,���ֽ���ǰ) */
	} SectorRead;							/* CMD1H_SEC_READ: ������Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */

	struct {
		UINT8	mSectorCount;				/* �������: ����д��������� */
											/* ����: ����д��������� */
		UINT8	mReserved1;
		UINT8	mReserved2;
		UINT8	mReserved3;
		UINT32	mStartSector;				/* ����: ����д������������ʼ��������������(�ܳ���32λ,���ֽ���ǰ) */
	} SectorWrite;							/* CMD1H_SEC_WRITE: ������Ϊ��λ�ڵ�ǰλ��д�����ݿ� */

	struct {
		UINT32	mDiskSizeSec;				/* ����: ����������̵���������(�ܳ���32λ,���ֽ���ǰ) */
	} DiskCapacity;							/* CMD0H_DISK_CAPACITY: ��ѯ������������ */

	struct {
		UINT32	mTotalSector;				/* ����: ��ǰ�߼��̵���������(�ܳ���32λ,���ֽ���ǰ) */
		UINT32	mFreeSector;				/* ����: ��ǰ�߼��̵�ʣ��������(�ܳ���32λ,���ֽ���ǰ) */
		UINT8	mDiskFat;					/* ����: ��ǰ�߼��̵�FAT����,1-FAT12,2-FAT16,3-FAT32 */
	} DiskQuery;							/* CMD_DiskQuery, ��ѯ������Ϣ */

	BULK_ONLY_CBW	DiskBocCbw;				/* �������: CBW����ṹ */
											/* CMD0H_DISK_BOC_CMD: ��USB�洢��ִ��BulkOnly����Э������� */

	struct {
		UINT8	mMaxLogicUnit;				/* ����: USB�洢��������߼���Ԫ�� */
	} DiskMaxLun;							/* CMD0H_DISK_MAX_LUN: ���ƴ���-��ȡUSB�洢������߼���Ԫ�� */

	INQUIRY_DATA	DiskInitInq;			/* ����: INQUIRY����ķ������� */
											/* CMD0H_DISK_INIT: ��ʼ��USB�洢�� */

	INQUIRY_DATA	DiskInqData;			/* ����: INQUIRY����ķ������� */
											/* CMD0H_DISK_INQUIRY: ��ѯUSB�洢������ */

	SENSE_DATA		ReqSenseData;			/* ����: REQUEST SENSE����ķ������� */
											/* CMD0H_DISK_R_SENSE: ���USB�洢������ */

	struct {
		UINT32	mDiskSizeSec;				/* ����: ����������̵���������(�ܳ���32λ,���ֽ���ǰ) */
	} DiskSize;								/* CMD0H_DISK_SIZE: ��ȡUSB�洢�������� */

	struct {
		UINT32	mStartSector;				/* �������: LBA������ַ(�ܳ���32λ,���ֽ���ǰ) */
		UINT8	mSectorCount;				/* �������: �����ȡ�������� */
	} DiskRead;								/* CMD5H_DISK_READ: ��USB�洢�������ݿ�(������Ϊ��λ) */

	struct {
		UINT32	mStartSector;				/* �������: LBA������ַ(�ܳ���32λ,���ֽ���ǰ) */
		UINT8	mSectorCount;				/* �������: ����д��������� */
	} DiskWrite;							/* CMD5H_DISK_WRITE: ��USB�洢��д���ݿ�(������Ϊ��λ) */
} CH376_CMD_DATA, *P_CH376_CMD_DATA;

#endif

/* ********************************************************************************************************************* */
/* �����ļ�ģʽ�µ��ļ�ϵͳ�����ĵ�ַ */

#ifndef	VAR_FILE_SIZE

/* 8λ/���ֽڱ��� */
#define	VAR_SYS_BASE_INFO	0x20			/* ��ǰϵͳ�Ļ�����Ϣ */
/*           λ6����ָʾUSB�洢�豸�������SubClass-Code, λ6Ϊ0��˵�������Ϊ6, λ6Ϊ1��˵��������Ƿ�6������ֵ */
/*           λ5����ָʾUSB�豸��ʽ�µ�USB����״̬��USB������ʽ�µ�USB�豸����״̬ */
/*                USB�豸��ʽ��, λ5Ϊ1��USB�������, λ5λ0����δ���� */
/*                USB������ʽ��, λ5Ϊ1��USB�˿ڴ���USB�豸, λ5λ0��USB�˿�û��USB�豸 */
/*           λ4����ָʾUSB�豸��ʽ�µĻ���������״̬, λ4Ϊ1��˵��USB��������������״̬, λ6Ϊ1��˵���Ѿ��ͷ� */
/*           ����λ, ����,�����޸� */
#define	VAR_RETRY_TIMES		0x25			/* USB������������Դ��� */
/*           λ7Ϊ0���յ�NAKʱ������, λ7Ϊ1λ6Ϊ0���յ�NAKʱ��������(������CMD_ABORT_NAK�����������), λ7Ϊ1λ6Ϊ1���յ�NAKʱ�������3�� */
/*           λ5~λ0Ϊ��ʱ������Դ��� */
#define	VAR_FILE_BIT_FLAG	0x26			/* �����ļ�ģʽ�µ�λ��־ */
/*           λ1��λ0, �߼��̵�FAT�ļ�ϵͳ��־, 00-FAT12, 01-FAT16, 10-FAT32, 11-�Ƿ� */
/*           λ2, ��ǰ�������е�FAT�������Ƿ��޸ı�־, 0-δ�޸�, 1-���޸� */
/*           λ3, �ļ�������Ҫ�޸ı�־, ��ǰ�ļ���׷������, 0-δ׷�������޸�, 1-��׷����Ҫ�޸� */
/*           ����λ, ����,�����޸� */
#define	VAR_DISK_STATUS		0x2B	   /* �����ļ�ģʽ�µĴ��̼��ļ�״̬ */
#define	VAR_SD_BIT_FLAG		0x30			/* �����ļ�ģʽ��SD����λ��־ */
/*           λ0, SD���汾, 0-ֻ֧��SD��һ��,1-֧��SD�ڶ��� */
/*           λ1, �Զ�ʶ��, 0-SD��, 1-MMC�� */
/*           λ2, �Զ�ʶ��, 0-��׼����SD��, 1-������SD��(HC-SD) */
/*           λ4, ACMD41���ʱ */
/*           λ5, CMD1���ʱ */
/*           λ6, CMD58���ʱ */
/*           ����λ, ����,�����޸� */
#define	VAR_UDISK_TOGGLE	0x31			/* USB�洢�豸��BULK-IN/BULK-OUT�˵��ͬ����־ */
/*           λ7, Bulk-In�˵��ͬ����־ */
/*           λ6, Bulk-In�˵��ͬ����־ */
/*           λ5~λ0, ����Ϊ0 */
#define	VAR_UDISK_LUN		0x34			/* USB�洢�豸���߼���Ԫ�� */
/*           λ7~λ4, USB�洢�豸�ĵ�ǰ�߼���Ԫ��,CH376��ʼ��USB�洢�豸��,Ĭ���Ƿ���0#�߼���Ԫ */
/*           λ3~λ0, USB�洢�豸������߼���Ԫ��,��1������߼���Ԫ�� */
#define	VAR_SEC_PER_CLUS	0x38			/* �߼��̵�ÿ�������� */
#define	VAR_FILE_DIR_INDEX	0x3B			/* ��ǰ�ļ�Ŀ¼��Ϣ�������ڵ������� */
#define	VAR_CLUS_SEC_OFS	0x3C			/* ��ǰ�ļ�ָ���ڴ��ڵ�����ƫ��,Ϊ0xFF��ָ���ļ�ĩβ,�ؽ��� */

/* 32λ/4�ֽڱ��� */
#define	VAR_DISK_ROOT		0x44			/* ����FAT16��Ϊ��Ŀ¼ռ��������,����FAT32��Ϊ��Ŀ¼��ʼ�غ�(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_DSK_TOTAL_CLUS	0x48			/* �߼��̵��ܴ���(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_DSK_START_LBA	0x4C			/* �߼��̵���ʼ����������LBA(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_DSK_DAT_START	0x50			/* �߼��̵������������ʼLBA(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_LBA_BUFFER		0x54			/* ��ǰ�������ݻ����������ݶ�Ӧ��LBA(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_LBA_CURRENT		0x58			/* ��ǰ��д�Ĵ�����ʼLBA��ַ(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_FAT_DIR_LBA		0x5C			/* ��ǰ�ļ�Ŀ¼��Ϣ���ڵ�����LBA��ַ(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_START_CLUSTER	0x60			/* ��ǰ�ļ�����Ŀ¼(�ļ���)����ʼ�غ�(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_CURRENT_CLUST	0x64			/* ��ǰ�ļ��ĵ�ǰ�غ�(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_FILE_SIZE		0x68			/* ��ǰ�ļ��ĳ���(�ܳ���32λ,���ֽ���ǰ) */
#define	VAR_CURRENT_OFFSET	0x6C			/* ��ǰ�ļ�ָ��,��ǰ��дλ�õ��ֽ�ƫ��(�ܳ���32λ,���ֽ���ǰ) */

#endif

/* ********************************************************************************************************************* */
/* ����USB���� */

/* USB�İ���ʶPID, ������ʽ�����õ� */
#ifndef	DEF_USB_PID_SETUP
#define	DEF_USB_PID_NULL	0x00			/* ����PID, δ���� */
#define	DEF_USB_PID_SOF		0x05
#define	DEF_USB_PID_SETUP	0x0D
#define	DEF_USB_PID_IN		0x09
#define	DEF_USB_PID_OUT		0x01
#define	DEF_USB_PID_ACK		0x02
#define	DEF_USB_PID_NAK		0x0A
#define	DEF_USB_PID_STALL	0x0E
#define	DEF_USB_PID_DATA0	0x03
#define	DEF_USB_PID_DATA1	0x0B
#define	DEF_USB_PID_PRE		0x0C
#endif

/* USB��������, ���ù̼�ģʽ�����õ� */
#ifndef	DEF_USB_REQ_TYPE
#define	DEF_USB_REQ_READ	0x80			/* ���ƶ����� */
#define	DEF_USB_REQ_WRITE	0x00			/* ����д���� */
#define	DEF_USB_REQ_TYPE	0x60			/* ������������ */
#define	DEF_USB_REQ_STAND	0x00			/* ��׼���� */
#define	DEF_USB_REQ_CLASS	0x20			/* �豸������ */
#define	DEF_USB_REQ_VENDOR	0x40			/* �������� */
#define	DEF_USB_REQ_RESERVE	0x60			/* �������� */
#endif

/* USB��׼�豸����, RequestType��λ6λ5=00(Standard), ���ù̼�ģʽ�����õ� */
#ifndef	DEF_USB_GET_DESCR
#define	DEF_USB_CLR_FEATURE	0x01
#define	DEF_USB_SET_FEATURE	0x03
#define	DEF_USB_GET_STATUS	0x00
#define	DEF_USB_SET_ADDRESS	0x05
#define	DEF_USB_GET_DESCR	0x06
#define	DEF_USB_SET_DESCR	0x07
#define	DEF_USB_GET_CONFIG	0x08
#define	DEF_USB_SET_CONFIG	0x09
#define	DEF_USB_GET_INTERF	0x0A
#define	DEF_USB_SET_INTERF	0x0B
#define	DEF_USB_SYNC_FRAME	0x0C
#endif

/* *************************************************************************** */

#ifdef __cplusplus
}
#endif

#endif

