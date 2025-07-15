#include "ds18b20.h"


void Delay_OneWire(unsigned int t)
{
 int i;
        while(t--)
 {
       for(i=0;i<12;i++);
 }
}

bit Init_DS18B20(void)
{
	bit initflag = 0; 
	DQ = 1;      //首先将数据线置高
	Delay_OneWire(12);  //短暂延时
	DQ = 0;      //将数据线拉到低电平
	Delay_OneWire(80);    //延时在480~960US之间
	DQ = 1;                     //数据线拉回高电平
	Delay_OneWire(10);  // 延时等待
	initflag = DQ;     // initflag等于1初始化失败
	Delay_OneWire(5);     //最后一个延时
	return initflag;
}



//向DS18B20写一个字节

void Write_DS18B20(unsigned char dat)
{
 unsigned char i;
 for(i=0;i<8;i++)    //重复直到发送完整个字节
 {
 DQ = 0;  //数据线首先拉低
 DQ = dat&0x01;
 Delay_OneWire(5);  //延时45us
 DQ = 1;    //将数据线拉回高电平1
 dat >>= 1;
 }
 Delay_OneWire(5);

}


//从DS18B20读取一个字节

unsigned char Read_DS18B20(void)
{
 int i;
 unsigned char dat; 
 for(i=0;i<8;i++)    //重复接收直到读完整个字节
 {
 DQ = 0;   //数据线拉低
 dat >>= 1;
 DQ = 1;   //数据线拉高
 if(DQ)
 {
 dat |= 0x80;
 }     
 Delay_OneWire(5);
 }
 return dat;
}


uint8_t Read_tem(void)
{
   unsigned char low,high;
	uint16_t temp;
   Init_DS18B20();       
   Write_DS18B20(0xCC);  //忽略64位ROM地址，直接向DS18B20发送温度变换命令，适用于一个从机工作
   Write_DS18B20(0x44);   //温度转换
   Delay_OneWire(200);


   Init_DS18B20();
   Write_DS18B20(0xCC);   
   Write_DS18B20(0xBE);   //读取温度数据


   low = Read_DS18B20();    //低八位
   high = Read_DS18B20();   //高八位
  
   temp = high<<4;           //整合成一个字节
   temp |= (low>>4);
  
   return temp;
}








