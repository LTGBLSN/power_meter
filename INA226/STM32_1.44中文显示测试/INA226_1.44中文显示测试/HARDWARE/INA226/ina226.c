#include "ina226.h"
//#include "usart.h"
#include "delay.h"
/*
	不确定具体电阻大小
*/
INA226 INA226_data;

void INA226_Init(void)
{	
	IIC_Init();
	delay_ms(10);
	INA226_SendData(INA226_ADDR1,CFG_REG,0x484f);//设置转换时间204us,求平均值次数128，采样时间为204*128，设置模式为分流和总线连续模式
	INA226_SendData(INA226_ADDR1,CAL_REG,0x0012);//设置分流电压转电流转换参数
}
void INA226_SetRegPointer(u8 addr,u8 reg)
{
	IIC_Start();

	IIC_Send_Byte(addr);
	IIC_Wait_Ack();

	IIC_Send_Byte(reg);
	IIC_Wait_Ack();

	IIC_Stop();
}

//发送,写入
void INA226_SendData(u8 addr,u8 reg,u16 data)
{
	u8 temp=0;
	IIC_Start();

	IIC_Send_Byte(addr);
	IIC_Wait_Ack();

	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	
	temp = (u8)(data>>8);
	IIC_Send_Byte(temp);
	IIC_Wait_Ack();

	temp = (u8)(data&0x00FF);
	IIC_Send_Byte(temp);
	IIC_Wait_Ack();
	
	IIC_Stop();
}

//读取
u16 INA226_ReadData(u8 addr)
{
	u16 temp=0;
	IIC_Start();

	IIC_Send_Byte(addr+1);
	IIC_Wait_Ack();
	
	temp = IIC_Read_Byte(1);
	temp<<=8;	
	temp |= IIC_Read_Byte(0);
	
	IIC_Stop();
	return temp;
}
/*
u8 INA226_AlertAddr()
{
	u8 temp;
	IIC_Start();

	IIC_Send_Byte(INA226_GETALADDR);
	IIC_Wait_Ack();
	
	temp = IIC_Read_Byte(1);
	
	IIC_Stop();
	return temp;
}
*/

//1mA/bit
u16 INA226_GetShunt_Current(u8 addr)
{
	u16 temp=0;	
	INA226_SetRegPointer(addr,CUR_REG);
	temp = INA226_ReadData(addr);
	if(temp&0x8000)	temp = ~(temp - 1);	
	return temp;
}

//获取 id
u16  INA226_Get_ID(u8 addr)
{
	u32 temp=0;
	INA226_SetRegPointer(addr,INA226_GET_ADDR);
	temp = INA226_ReadData(addr);
	return (u16)temp;
}

//获取校准值
u16 INA226_GET_CAL_REG(u8 addr)
{	
	u32 temp=0;
	INA226_SetRegPointer(addr,CAL_REG);
	temp = INA226_ReadData(addr);
	return (u16)temp;
}

//1.25mV/bit
u16 INA226_GetVoltage(u8 addr)
{
	u32 temp=0;
	INA226_SetRegPointer(addr,BV_REG);
	temp = INA226_ReadData(addr);
	return (u16)temp;	
}



//2.5uV/bit,感觉这个值是测不准的，所以下面改成2.2了
u16 INA226_GetShuntVoltage(u8 addr)
{
	int16_t temp=0;
	INA226_SetRegPointer(addr,SV_REG);
	temp = INA226_ReadData(addr);
	if(temp&0x8000)	temp = ~(temp - 1);	
	return (u16)temp;	
}


u16 INA226_Get_Power(u8 addr)
{
	int16_t temp=0;
	INA226_SetRegPointer(addr,PWR_REG);
	temp = INA226_ReadData(addr);
	return (u16)temp;
}


void GetVoltage(float *Voltage)//mV
{
	Voltage[0] = INA226_GetVoltage(INA226_ADDR1)*1.25f;
}


void Get_Shunt_voltage(float *Voltage)//uV
{
	Voltage[0] = (INA226_GetShuntVoltage(INA226_ADDR1)*2.2);//这里原来乘的系数是2.5
}


void Get_Shunt_Current(float *Current)//mA
{
	Current[0] = (INA226_GetShunt_Current(INA226_ADDR1)* 2.5f);
}


void GetPower()//W
{
	GetVoltage(&INA226_data.voltageVal);			//mV
	Get_Shunt_voltage(&INA226_data.Shunt_voltage);	//uV
	Get_Shunt_Current(&INA226_data.Shunt_Current);	//mA
	INA226_data.powerVal=INA226_data.voltageVal*0.001f * INA226_data.Shunt_Current*0.001f;
}

/*
void Get_Power(float *Current)//W
{
	Current[0] = (INA226_Get_Power(INA226_ADDR1)*50);
}
*/
