

/*
//杜洋工作室出品
//洋桃系列开发板应用程序
//关注微信公众号：洋桃电子
//洋桃开发板资料下载 www.DoYoung.net/YT 
//即可免费看所有教学视频，下载技术资料，技术疑难提问
//更多内容尽在 杜洋工作室主页 www.doyoung.net
*/

/*
《修改日志》
1-201708202309 创建。


*/



#include "dht11.h"


void DHT11_IO_OUT (void){ //端口变为输出
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    GPIO_InitStructure.GPIO_Pin = DHT11_IO; //选择端口号（0~15或all）                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择IO接口工作方式       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(DHT11PORT, &GPIO_InitStructure);
}

void DHT11_IO_IN (void){ //端口变为输入
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    GPIO_InitStructure.GPIO_Pin = DHT11_IO; //选择端口号（0~15或all）                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式       
	GPIO_Init(DHT11PORT, &GPIO_InitStructure);
}

void DHT11_RST (void){ //DHT11端口复位，发出起始信号（IO发送）
	DHT11_IO_OUT();
	GPIO_ResetBits(DHT11PORT,DHT11_IO); //	
	delay_ms(20); //拉低至少18ms						
	GPIO_SetBits(DHT11PORT,DHT11_IO); //							
	delay_us(30); //主机拉高20~40us
}

u8 Dht11_Check(void){ //等待DHT11回应，返回1:未检测到DHT11，返回0:成功（IO接收）	   
    u8 retry=0;
    DHT11_IO_IN();//IO到输入状态	 
    while (GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO)&&retry<100){//DHT11会拉低40~80us
        retry++;
        delay_us(1);
    }	 
    if(retry>=100)return 1; else retry=0;
    while (!GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO)&&retry<100){//DHT11拉低后会再次拉高40~80us
        retry++;
        delay_us(1);
    }
    if(retry>=100)return 1;	    
    return 0;
}

u8 Dht11_ReadBit(void){ //从DHT11读取一个位 返回值：1/0
    u8 retry=0;
    while(GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO)&&retry<100){//等待变为低电平
        retry++;
        delay_us(1);
    }
    retry=0;
    while(!GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO)&&retry<100){//等待变高电平
        retry++;
        delay_us(1);
    }
    delay_us(40);//等待40us	//用于判断高低电平，即数据1或0
    if(GPIO_ReadInputDataBit(DHT11PORT,DHT11_IO))return 1; else return 0;		   
}

u8 Dht11_ReadByte(void){  //从DHT11读取一个字节  返回值：读到的数据
    u8 i,dat;
    dat=0;
    for (i=0;i<8;i++){ 
        dat<<=1; 
        dat|=Dht11_ReadBit();
    }						    
    return dat;
}

u8 DHT11_Init (void){	//DHT11初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE); //APB2外设时钟使能      
	DHT11_RST();//DHT11端口复位，发出起始信号
	return Dht11_Check(); //等待DHT11回应
}

u8 DHT11_ReadData(u8 *h){ //读取一次数据//湿度值(十进制，范围:20%~90%) ，温度值(十进制，范围:0~50°)，返回值：0,正常;1,失败 
    u8 buf[5];
    u8 i;
    DHT11_RST();//DHT11端口复位，发出起始信号
    if(Dht11_Check()==0){ //等待DHT11回应
        for(i=0;i<5;i++){//读取5位数据
            buf[i]=Dht11_ReadByte(); //读出数据
        }
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4]){	//数据校验
            *h=buf[0]; //将湿度值放入指针1
			h++;
            *h=buf[2]; //将温度值放入指针2
        }
    }else return 1;
    return 0;	    
}
 
/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/
