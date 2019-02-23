
#include "flash.h"

//FLASH写入数据
void FLASH_W(u32 add,u16 dat)       //参数1：32位FLASH地址。参数2：16位数据
{ 
   //RCC_HSICmd(ENABLE); //打开HSI时钟
	 FLASH_Unlock();                  //解锁FLASH编程擦除控制器
   FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
   FLASH_ErasePage(add);            //擦除指定地址页
   FLASH_ProgramHalfWord(add,dat);  //从指定页的addr地址开始写
   FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
   FLASH_Lock();                    //锁定FLASH编程擦除控制器
}

//FLASH读出数据
u16 FLASH_R(u32 add)        //参数1：32位读出FLASH地址。返回值：16位数据
{ 
	u16 a;
    a = *(u16*)(add);       //从指定页的addr地址开始读
return a;
}





























