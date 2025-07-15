#include "HX711.h"
#include "Delay.h"

UINT32 HX711_Buffer;
UINT32 Weight_MaopiAD;
s32 gWeight_Maopi;
UINT32 Weight_ShiwuAD;
s32 Weight_Shiwu;
UINT8 Flag_Error = 0;

//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数
#define GapValue 456.5

UINT8 gDigit = 0;	//位数


void Init_HX711pin(void)
{
	P0M1 &= ~0x02;P0M2 |= 0x02; //P03 TM7711 时钟线
  P0M1 |= 0x01;P0M2 &= ~0x01; //P04 TM7711 数据线
}

void Delay__hx711_us(unsigned char t)
{
	while(t--);
}



//****************************************************
//读取HX711
//****************************************************
UINT32 HX711_Read(void)	//增益128
{
	unsigned long count; 
	unsigned char i; 
	SCL_L; 
	count=0; 
	while(SDA_R); 
	//clr_EA;//禁止所有中断
	for(i=0;i<24;i++)
	{ 
		SCL_H; 
		count=count<<1; 
		//Delay__hx711_us(2);
		SCL_L; 
		if(SDA_R)
		count++; 
	} 
 	SCL_H; 
	count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	SCL_L;
	//set_EA;//使能全部中断
	return(count);
}

//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi(void)
{
	Weight_MaopiAD = HX711_Read();  
	
	//gWeight_Maopi = (unsigned int)((float)Weight_MaopiAD/GapValue); 
} 

//****************************************************
//称重
//****************************************************
void Get_Weight(void)
{
	unsigned int X;
	HX711_Buffer = HX711_Read();
	if(HX711_Buffer > Weight_MaopiAD)			
	{
		Weight_ShiwuAD = HX711_Buffer;
		Weight_ShiwuAD = Weight_ShiwuAD - Weight_MaopiAD;				//获取实物的AD采样数值。
	
		//if(Weight_Shiwu == 0) || (Weight_Shiwu)
		Weight_Shiwu = (unsigned int)((float)Weight_ShiwuAD/GapValue); 	//计算实物的实际重量
																		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
																		//当发现测试出来的重量偏大时，增加该数值。
																		//如果测试出来的重量偏小时，减小改数值。
		
		//P05 = 0x00;
	}
	
	X = Weight_Shiwu;
	gDigit = 0;
	while(X)
	{
		X/=10; 
		gDigit++;
	}
}
