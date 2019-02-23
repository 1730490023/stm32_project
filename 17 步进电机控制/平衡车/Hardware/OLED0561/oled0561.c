

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
1-201709021721 ������


*/




#include "oled0561.h"
#include "ASCII_8x16.h" //�������� ASCII

#include "CHS_16x16.h" //���뺺������ 
#include "PIC1.h" //����ͼƬ


void OLED0561_Init (void){//OLED������ʾ��ʼ��
	OLED_DISPLAY_OFF(); //OLED����ʾ
	OLED_DISPLAY_CLEAR(); //�����Ļ����
	OLED_DISPLAY_ON(); //OLED����ʼֵ���ò�����ʾ
}
void OLED_DISPLAY_ON (void){//OLED����ʼֵ���ò�����ʾ
	u8 buf[28]={
	0xae,//0xae:����ʾ��0xaf:����ʾ
    0x00,0x10,//��ʼ��ַ��˫�ֽڣ�       
	0xd5,0x80,//��ʾʱ��Ƶ�ʣ�
	0xa8,0x3f,//�����ʣ�
	0xd3,0x00,//��ʾƫ�ƣ�
	0XB0,//д��ҳλ�ã�0xB0~7��
	0x40,//��ʾ��ʼ��
	0x8d,0x14,//VCC��Դ
	0xa1,//���ö�����ӳ�䣿
	0xc8,//COM�����ʽ��
	0xda,0x12,//COM�����ʽ��
	0x81,0xff,//�Աȶȣ�ָ�0x81�����ݣ�0~255��255��ߣ�
	0xd9,0xf1,//������ڣ�
	0xdb,0x30,//VCC��ѹ���
	0x20,0x00,//ˮƽѰַ����
	0xa4,//0xa4:������ʾ��0xa5:�������
	0xa6,//0xa6:������ʾ��0xa7:��ɫ��ʾ
	0xaf//0xae:����ʾ��0xaf:����ʾ
	}; //
	I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,28);
}
void OLED_DISPLAY_OFF (void){//OLED������ʾ
	u8 buf[3]={
		0xae,//0xae:����ʾ��0xaf:����ʾ
		0x8d,0x10,//VCC��Դ
	}; //
	I2C_SAND_BUFFER(OLED0561_ADD,COM,buf,3);
}
void OLED_DISPLAY_LIT (u8 x){//OLED���������ã�0~255��
	I2C_SAND_BYTE(OLED0561_ADD,COM,0x81);
	I2C_SAND_BYTE(OLED0561_ADD,COM,x);//����ֵ
}
void OLED_DISPLAY_CLEAR(void){//��������
	u8 j,t;
	for(t=0xB0;t<0xB8;t++){	//������ʼҳ��ַΪ0xB0
		I2C_SAND_BYTE(OLED0561_ADD,COM,t); 	//ҳ��ַ����0xB0��0xB7��
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x10); //��ʼ�е�ַ�ĸ�4λ
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x00);	//��ʼ�е�ַ�ĵ�4λ
		for(j=0;j<132;j++){	//��ҳ�������
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,0x00);
 		}
	}
}

//��ʾӢ��������8*16��ASCII��
//ȡģ��СΪ8*16��ȡģ��ʽΪ�������Ҵ��ϵ��¡�������8���¸�λ��
void OLED_DISPLAY_8x16(u8 x, //��ʾ���ֵ�ҳ���꣨��0��7�����˴������޸ģ�
						u8 y, //��ʾ���ֵ������꣨��0��128��
						u16 w){ //Ҫ��ʾ���ֵı��
	u8 j,t,c=0;
	y=y+2; //��OLED������������оƬ�Ǵ�0x02����Ϊ��������һ�У�����Ҫ����ƫ����
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); //ҳ��ַ����0xB0��0xB7��
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); //��ʼ�е�ַ�ĸ�4λ
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);	//��ʼ�е�ַ�ĵ�4λ
		for(j=0;j<8;j++){ //��ҳ�������
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,ASCII_8x16[(w*16)+c-512]);//Ϊ�˺�ASII���ӦҪ��512
			c++;}x++; //ҳ��ַ��1
	}
}
//��LCM����һ���ַ���,����64�ַ�֮�ڡ�
//Ӧ�ã�OLED_DISPLAY_8_16_BUFFER(0," DoYoung Studio"); 
void OLED_DISPLAY_8x16_BUFFER(u8 row,u8 *str){
	u8 r=0;
	while(*str != '\0'){
		OLED_DISPLAY_8x16(row,r*8,*str++);
		r++;
    }	
}

//----- ���ں�����ʾ�ĳ��� ------//

//��ʾ����16*16
//ȡģ��СΪ16*16��ȡģ��ʽΪ�������Ҵ��ϵ��¡�������8���¸�λ��
void OLED_DISPLAY_16x16(u8 x, //��ʾ���ֵ�ҳ���꣨��0xB0��0xB7��
			u8 y, //��ʾ���ֵ������꣨��0��63��
			u16 w){ //Ҫ��ʾ���ֵı��
	u8 j,t,c=0;
	for(t=0;t<2;t++){
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+x); //ҳ��ַ����0xB0��0xB7��
		I2C_SAND_BYTE(OLED0561_ADD,COM,y/16+0x10); //��ʼ�е�ַ�ĸ�4λ
		I2C_SAND_BYTE(OLED0561_ADD,COM,y%16);	//��ʼ�е�ַ�ĵ�4λ
		for(j=0;j<16;j++){ //��ҳ�������
 			I2C_SAND_BYTE(OLED0561_ADD,DAT,GB_16[(w*32)+c]);
			c++;}x++; //ҳ��ַ��1
	}
	I2C_SAND_BYTE(OLED0561_ADD,COM,0xAF); //����ʾ 
}

void OLED_DISPLAY_PIC1(void){ //��ʾȫ��ͼƬ
	u8 m,i;
	for(m=0;m<8;m++){//
		I2C_SAND_BYTE(OLED0561_ADD,COM,0xb0+m);
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x10); //��ʼ�е�ַ�ĸ�4λ
		I2C_SAND_BYTE(OLED0561_ADD,COM,0x02);	//��ʼ�е�ַ�ĵ�4λ
		for(i=0;i<128;i++){//����128��ͼƬ��ʾ����
			I2C_SAND_BYTE(OLED0561_ADD,DAT,PIC1[i+m*128]);}
	}
}
 
/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/




