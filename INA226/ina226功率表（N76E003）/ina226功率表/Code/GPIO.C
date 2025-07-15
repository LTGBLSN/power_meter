/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 GPIO demo code
//***********************************************************************************************************
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "stdlib.h"
#include "stdio.h"
#include "IIC_INA226.h"
#include "INA226_APP.h"
#include "oled.h"



int time1=0;

//浮点十六进制数转10进制

uint32_t vE=0;

uint16_t Voltage;

uint8_t Current[8];	


void main (void) 
{
	IIC_Init();		//初始化INA226
	write_ina226(0x05,0x00,0x36);
	write_ina226(0x00,0x0B,0x27);
	OLED_Init();			//初始化OLED  
	
//	OLED_ShowCHinese48(0,0,0);	//电
//	OLED_ShowCHinese48(28,0,4);	//压
//	
//	OLED_ShowCHinese48(0,4,0);	//电
//	OLED_ShowCHinese48(28,4,8);	//流
	
//	Timer1_Delay10ms(200);
	
	OLED_Clear();

  while(1)
  {
		Read_INA226();
		//Timer1_Delay10ms(10);
		//电压赋值显示
		//sprintf(Voltage,"%f",INA226_data.Voltage_Data);
		if(INA226_data.Voltage_Data <= 9999)													//一位数
		{
			OLED_ShowChar48(0,0,(uint8_t)(INA226_data.Voltage_Data/1000) * 2);	//个位
			OLED_ShowChar48(16,0,10 * 2);					//小数点
			OLED_ShowChar48(32,0,(uint8_t)(INA226_data.Voltage_Data/100%10) * 2);	//1位
			OLED_ShowChar48(48,0,(uint8_t)(INA226_data.Voltage_Data/10%10) * 2);	//2位
			//OLED_ShowChar48(64,0,(uint8_t)(INA226_data.Voltage_Data/1%10) * 2);	//3位
			OLED_ShowChar48(64,0,12 * 2);					//单位V
		}
		else
		{
			OLED_ShowChar48(0,0,(uint8_t)(INA226_data.Voltage_Data/10000) * 2);	//十位
			OLED_ShowChar48(16,0,(uint8_t)(INA226_data.Voltage_Data/1000%10) * 2);	//个位
			OLED_ShowChar48(32,0,10 * 2);					//小数点
			OLED_ShowChar48(48,0,(uint8_t)(INA226_data.Voltage_Data/1000%10) * 2);	//1位
			//OLED_ShowChar48(64+36,0,(uint8_t)(INA226_data.Voltage_Data/100%10) * 2);	//2位
			//OLED_ShowChar48(64,0,(uint8_t)(INA226_data.Voltage_Data/1%10) * 2);	//3位
			OLED_ShowChar48(64,0,12 * 2);					//单位V
		}
		
		//电流赋值显示
		sprintf(Current,"%f",INA226_data.Current_Data*48.5);//分流电阻为 0.002欧*48.5
		
		if((Current[0] > 0) && (Current[1] == '.'))	//电流为10mA以下，1mA以上
		{
			OLED_ShowChar48(0,4,(Current[0]-0x30) * 2);	//个位
			OLED_ShowChar48(16,4,10 * 2);					//小数点
			OLED_ShowChar48(32,4,(Current[2]-0x30) * 2);	//1位
			OLED_ShowChar48(48,4,(Current[3]-0x30) * 2);	//2位
			OLED_ShowChar48(64,4,(Current[4]-0x30) * 2);	//3位
			OLED_ShowChar48(80,4,13 * 2);					//单位m
			OLED_ShowChar48(96,4,14 * 2);					//单位A
		}
		else if((Current[0] > 0) && (Current[2] == '.'))	//两位整数，电流为100mA以下,10mA以上
		{
			OLED_ShowChar48(0,4,(Current[0]-0x30) * 2);	//十位
			OLED_ShowChar48(16,4,(Current[1]-0x30) * 2);	//个位
			OLED_ShowChar48(32,4,10 * 2);					//小数点
			OLED_ShowChar48(48,4,(Current[3]-0x30) * 2);	//1位
			OLED_ShowChar48(64,4,(Current[4]-0x30) * 2);	//2位
			OLED_ShowChar48(80,4,13 * 2);					//单位m
			OLED_ShowChar48(96,4,14 * 2);					//单位A
		}
		else if((Current[0] > 0) && (Current[3] == '.'))	//三位整数，电流为1000mA以下,100mA以上
		{
			OLED_ShowChar48(0,4,(Current[0]-0x30) * 2);	//百位
			OLED_ShowChar48(16,4,(Current[1]-0x30) * 2);	//十位
			OLED_ShowChar48(32,4,(Current[2]-0x30) * 2);	//个位
			OLED_ShowChar48(48,4,10 * 2);					//小数点
			OLED_ShowChar48(64,4,(Current[4]-0x30) * 2);	//1位
			OLED_ShowChar48(80,4,13 * 2);					//单位m
			OLED_ShowChar48(96,4,14 * 2);					//单位A
		}
		else if((Current[0] > 0) && (Current[4] == '.'))	//四位整数，电流为1000mA以上（切换单位：A）
		{
			OLED_ShowChar48(0,4,(Current[0]-0x30) * 2);	//个位
			OLED_ShowChar48(16,4,10 * 2);					//小数点
			OLED_ShowChar48(32,4,(Current[2]-0x30) * 2);	//1位
			OLED_ShowChar48(48,4,(Current[2]-0x30) * 2);	//2位
			OLED_ShowChar48(64,4,(Current[2]-0x30) * 2);	//3位
			OLED_ShowChar48(80,4,14 * 2);					//单位A
			OLED_ShowString(96,4,"  ");
			
		}
		else if((Current[0] == 0) && (Current[1] == '.'))	//电流为1mA以下，0.1mA以上（切换单位：uA）
		{
			OLED_ShowChar48(0,4,(Current[2]-0x30) * 2);	//百位
			OLED_ShowChar48(16,4,(Current[3]-0x30) * 2);	//十位
			OLED_ShowChar48(32,4,(Current[4]-0x30) * 2);	//个位
			OLED_ShowChar48(48,4,10 * 2);					//小数点
			OLED_ShowChar48(64,4,(Current[6]-0x30) * 2);	//1位
			OLED_ShowChar48(80,4,15 * 2);					//单位u
			OLED_ShowChar48(96,4,14 * 2);					//单位A
		}
		else if((Current[0] == 0) && (Current[1] == '.') && (Current[2] == 0))	//电流为0.1mA以下，10uA以上
		{
			OLED_ShowChar48(0,4,(Current[3]-0x30) * 2);	//十位
			OLED_ShowChar48(16,4,(Current[4]-0x30) * 2);	//个位
			OLED_ShowChar48(32,4,10 * 2);					//小数点
			OLED_ShowChar48(48,4,(Current[6]-0x30) * 2);	//1位
			OLED_ShowChar48(64,4,(Current[7]-0x30) * 2);	//2位
			OLED_ShowChar48(80,4,15 * 2);					//单位u
			OLED_ShowChar48(96,4,14 * 2);					//单位A
		}
		else if((Current[0] == 0) && (Current[1] == '.') && (Current[2] == 0) && (Current[3] == 0))	//电流为10uA以下，1uA以上
		{
			OLED_ShowChar48(0,4,(Current[4]-0x30) * 2);	//个位
			OLED_ShowChar48(16,4,10 * 2);					//小数点
			OLED_ShowChar48(32,4,(Current[6]-0x30) * 2);	//1位
			OLED_ShowChar48(48,4,(Current[7]-0x30) * 2);	//2位
			OLED_ShowChar48(64,4,15 * 2);					//单位u
			OLED_ShowChar48(80,4,14 * 2);					//单位A
		}
		//#endif
  }//while(1)

	

}



