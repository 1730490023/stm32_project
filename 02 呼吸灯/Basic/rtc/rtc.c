
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
1-201708091539 �޸��˵�2���ϵ�����ʱ��Ῠ�������⣨��д������д��֮ǰ���ó�ʼ����������


*/


/* 
	//ʱ���д������˵��//
1����mani������ͷ����RTC_Config();�Ϳ���ʹ��ʱ���ˡ�
��RTC_Config();�������Դ��ж��ǲ����״�ʹ��RTC
2��ʹ�� RTC_Get();����ʱ�䡣���������ݴ���ڣ�
�� ryear ��16λ��
�� rmon	 �����¶���8λ��
�� rday
ʱ rhour
�� rmin
�� rsec
�� rweek

3��ʹ�� RTC_Set(4λ��,2λ��,2λ��,2λʱ,2λ��,2λ��); д��ʱ�䡣���磺RTC_Get(2017,08,06,21,34,00);

�����������ǰ�������3�������ģ�����Ҫ���á� 
ע��Ҫʹ��RTC_Get��RTC_Set�ķ���ֵ��Ϊ0ʱ��ʾ��д��ȷ��

*/


#include "sys.h"
#include "rtc.h"


//����2��ȫ�ֱ���--����RTCʱ��Ķ�ȡ
u16 ryear; //4λ��
u8 rmon,rday,rhour,rmin,rsec,rweek;//2λ����ʱ������



void RTC_First_Config(void){ //�״�����RTC������
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//����PWR��BKP��ʱ�ӣ�from APB1��
    PWR_BackupAccessCmd(ENABLE);//�������
    BKP_DeInit();//���ݼĴ���ģ�鸴λ
    RCC_LSEConfig(RCC_LSE_ON);//�ⲿ32.768KHZ������   
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);//�ȴ��ȶ�    
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//RTCʱ��Դ���ó�LSE���ⲿ���پ���32.768KHZ��    
    RCC_RTCCLKCmd(ENABLE);//RTC����    
    RTC_WaitForSynchro();//��������Ҫ�ȴ�APB1ʱ����RTCʱ��ͬ�������ܶ�д�Ĵ���    
    RTC_WaitForLastTask();//��д�Ĵ���ǰ��Ҫȷ����һ�������Ѿ�����
    RTC_SetPrescaler(32767);//����RTC��Ƶ����ʹRTCʱ��Ϊ1Hz,RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)   
    RTC_WaitForLastTask();//�ȴ��Ĵ���д�����	
    //����ʹ��RTC���жϣ�������������2��
//    RTC_ITConfig(RTC_IT_SEC, ENABLE);//ʹ�����ж�   
//    RTC_WaitForLastTask();//�ȴ�д�����
}

void RTC_Config(void){ //ʵʱʱ�ӳ�ʼ��
    //��BKP�ĺ󱸼Ĵ���1�У�����һ�������ַ�0xA5A5
    //��һ���ϵ��󱸵�Դ����󣬸üĴ������ݶ�ʧ������RTC���ݶ�ʧ����Ҫ��������
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5){//�жϼĴ������Ƿ�ʧ       
        RTC_First_Config();//��������RTC        
        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);//������ɺ���󱸼Ĵ�����д�����ַ�0xA5A5
    }else{
		//���󱸼Ĵ���û�е��磬��������������RTC
        //�������ǿ�������RCC_GetFlagStatus()�����鿴���θ�λ����
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET){
            //�����ϵ縴λ
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET){
            //�����ⲿRST�ܽŸ�λ
        }       
        RCC_ClearFlag();//���RCC�и�λ��־

        //��ȻRTCģ�鲻��Ҫ�������ã��ҵ���������󱸵����Ȼ����
        //����ÿ���ϵ�󣬻���Ҫʹ��RTCCLK
        RCC_RTCCLKCmd(ENABLE);//ʹ��RTCCLK        
        RTC_WaitForSynchro();//�ȴ�RTCʱ����APB1ʱ��ͬ��

        //����ʹ��RTC���жϣ�������������2��
//        RTC_ITConfig(RTC_IT_SEC, ENABLE);//ʹ�����ж�        
//        RTC_WaitForLastTask();//�ȴ��������
    }
	#ifdef RTCClockOutput_Enable   
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	    PWR_BackupAccessCmd(ENABLE);   
	    BKP_TamperPinCmd(DISABLE);   
	    BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
	#endif
}

void RTC_IRQHandler(void){ //RTCʱ��1�봥���жϺ��������ƹ̶������޸ģ�
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET){

	}
	RTC_ClearITPendingBit(RTC_IT_SEC); 
	RTC_WaitForLastTask();
}

void RTCAlarm_IRQHandler(void){	//�����жϴ�������ʱ������������ȼ���
	if(RTC_GetITStatus(RTC_IT_ALR) != RESET){
	
	}
	RTC_ClearITPendingBit(RTC_IT_ALR);
	RTC_WaitForLastTask();
}

//�ж��Ƿ������꺯��
//�·�   1  2  3  4  5  6  7  8  9  10 11 12
//����   31 29 31 30 31 30 31 31 30 31 30 31
//������ 31 28 31 30 31 30 31 31 30 31 30 31
//����:���
//���:������ǲ�������.1,��.0,����
u8 Is_Leap_Year(u16 year){                    
	if(year%4==0){ //�����ܱ�4����
		if(year%100==0){		
			if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400����          
			else return 0;  
		}else return 1;  
	}else return 0;
}                           
//����ʱ��
//�������ʱ��ת��Ϊ����
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����

//�·����ݱ�                                                                       
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�  
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};//ƽ����·����ڱ�

//д��ʱ��
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec){ //д�뵱ǰʱ�䣨1970~2099����Ч����
	u16 t;
	u32 seccount=0;
	if(syear<2000||syear>2099)return 1;//syear��Χ1970-2099���˴����÷�ΧΪ2000-2099       
	for(t=1970;t<syear;t++){ //��������ݵ��������
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;                    //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++){         //��ǰ���·ݵ����������
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������        
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ����������
	seccount+=(u32)hour*3600;//Сʱ������
	seccount+=(u32)min*60;      //����������
	seccount+=sec;//�������Ӽ���ȥ
	RTC_First_Config(); //���³�ʼ��ʱ��
	BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);//������ɺ���󱸼Ĵ�����д�����ַ�0xA5A5
	RTC_SetCounter(seccount);//�ѻ���õļ�����ֵд��
	RTC_WaitForLastTask(); //�ȴ�д�����
	return 0; //����ֵ:0,�ɹ�;����:�������.    
}

//����ʱ��
u8 RTC_Get(void){//������ǰʱ��ֵ //����ֵ:0,�ɹ�;����:�������.
	static u16 daycnt=0;
	u32 timecount=0;
	u32 temp=0;
	u16 temp1=0;
	timecount=RTC_GetCounter();		
	temp=timecount/86400;   //�õ�����(��������Ӧ��)
	if(daycnt!=temp){//����һ����
		daycnt=temp;
		temp1=1970;  //��1970�꿪ʼ
		while(temp>=365){
		     if(Is_Leap_Year(temp1)){//������
			     if(temp>=366)temp-=366;//�����������
			     else {temp1++;break;} 
		     }
		     else temp-=365;       //ƽ��
		     temp1++; 
		}  
		ryear=temp1;//�õ����
		temp1=0;
		while(temp>=28){//������һ����
			if(Is_Leap_Year(ryear)&&temp1==1){//�����ǲ�������/2�·�
				if(temp>=29)temp-=29;//�����������
				else break;
			}else{
	            if(temp>=mon_table[temp1])temp-=mon_table[temp1];//ƽ��
	            else break;
			}
			temp1++; 
		}
		rmon=temp1+1;//�õ��·�
		rday=temp+1;  //�õ�����
	}
	temp=timecount%86400;     //�õ�������      
	rhour=temp/3600;     //Сʱ
	rmin=(temp%3600)/60; //����     
	rsec=(temp%3600)%60; //����
	rweek=RTC_Get_Week(ryear,rmon,rday);//��ȡ����  
	return 0;
}    

u8 RTC_Get_Week(u16 year,u8 month,u8 day){ //�������ռ�������(ֻ����1901-2099��)//����RTC_Get����    
	u16 temp2;
	u8 yearH,yearL;
	yearH=year/100;     
	yearL=year%100;
	// ���Ϊ21����,�������100 
	if (yearH>19)yearL+=100;
	// ����������ֻ��1900��֮��� 
	temp2=yearL+yearL/4;
	temp2=temp2%7;
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7); //��������ֵ
}

/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/




