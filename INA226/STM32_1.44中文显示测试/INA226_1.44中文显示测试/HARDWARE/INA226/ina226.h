#ifndef __INA226_H
#define __INA226_H
#include "sys.h"
#include "myiic.h"


#define 	CFG_REG	 		0x00		//
#define 	SV_REG 			0x01		//������ѹ�� �˴���������Ϊ 0.1ŷ
#define 	BV_REG 			0x02		//���ߵ�ѹ
#define 	PWR_REG 		0x03		//��Դ����
#define 	CUR_REG 		0x04		//����
#define 	CAL_REG 		0x05		//У׼���趨�����̷�Χ�Լ������͹��ʲ����� 
#define 	ONFF_REG 		0x06		//���� ʹ�� �������ú�ת��׼������
#define 	AL_REG 			0x07		//��������ѡ����������Ƚϵ��޶�ֵ
#define 	INA226_GET_ADDR 0XFF		//����Ψһ��оƬ��ʶ��
#define   	INA226_ADDR1	0x80 

//#define   	INA226_GETALADDR	0x14 
typedef struct
{
	float voltageVal;			//mV
	float Shunt_voltage;		//uV
	float Shunt_Current;		//mA
	float powerVal;

}INA226;


void INA226_Init(void);
void INA226_SetRegPointer(u8 addr,u8 reg);
void INA226_SendData(u8 addr,u8 reg,u16 data);

u16 INA226_ReadData(u8 addr);
//u8	INA226_AlertAddr(void);
u16 INA226_Get_ID(u8 addr);				//��ȡ id
u16 INA226_GetVoltage( u8 addr);		//��ȡ���ߵ�ѹ
u16 INA226_GetShunt_Current(u8 addr);	//��ȡ��������
u16 INA226_GetShuntVoltage(u8 addr);	//������ѹ
u16 INA226_Get_Power(u8 addr);			//��ȡ����

u16 INA226_GET_CAL_REG(u8 addr);
void GetVoltage(float *Voltage);		
void Get_Shunt_voltage(float *Current);
void Get_Shunt_Current(float *Current);
//void Get_Power(float *Current);
//void GetPower();//W

extern INA226 INA226_data;
#endif

