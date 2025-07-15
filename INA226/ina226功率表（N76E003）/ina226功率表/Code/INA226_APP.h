#ifndef __INA226_APP__H
#define __INA226_APP__H

#include "Common.h"

#define 	CFG_REG	 		0x00		//采样时间
#define 	SV_REG 			0x01	//分流电压， 此处分流电阻为 0.1欧
#define 	BV_REG 			0x02		//总线电压
#define 	PWR_REG 		0x03		//电源功率
#define 	CUR_REG 		0x04		//电流
#define 	CAL_REG 		0x05		//校准，设定满量程范围以及电流和功率测数的 
#define 	ONFF_REG 		0x06		//屏蔽 使能 警报配置和转换准备就绪
#define 	AL_REG 			0x07		//包含与所选警报功能相比较的限定值
#define 	INA226_GET_ADDR 0XFF		//包含唯一的芯片标识号
#define   	INA226_ADDR1	0x80
 
//#define   	INA226_GETALADDR	0x14 
/*
typedef struct
{
	float voltageVal;			//mV
	float Shunt_voltage;		//uV
	float Shunt_Current;		//mA
	float powerVal;
}INA226;
*/

typedef struct
{
	double Current_Data;   	//显示电流
	int Voltage_Data;   			//显示电压
	int Read_Data[2]; 				//[0]:电流AD (-32768-32767)  [1]:电压mv
	double Var_Iref;
	//double Var_Iref2;
}INA226;

extern INA226 INA226_data;


void INA226_Init(void);
void INA226_SetRegPointer(uint8_t addr,uint8_t reg);
void INA226_SendData(uint8_t addr,uint8_t reg,uint16_t str);
 
uint16_t INA226_ReadData(uint8_t addr);
//uint8_t	INA226_AlertAddr(void);
uint16_t INA226_Get_ID(uint8_t addr);				//获取 id
uint16_t INA226_GetVoltage( uint8_t addr);		//获取总线电压
uint16_t INA226_GetShunt_Current(uint8_t addr);	//获取分流电流
uint16_t INA226_GetShuntVoltage(uint8_t addr);	//分流电压
uint16_t INA226_Get_Power(uint8_t addr);			//获取功率
 
uint16_t INA226_GET_CAL_REG(uint8_t addr);
void GetVoltage(float *Voltage);		
void Get_Shunt_voltage(float *Current);
void Get_Shunt_Current(float *Current);
//void Get_Power(float *Current);
void GetPower();//W
 



unsigned int iread(unsigned char sla,unsigned char suba);
bit write_ina226(uint8_t address, uint8_t con1, uint8_t con2);	  //写0H   0x0927
void Read_INA226();			 //读电流，电压，温度

#endif
