#include "INA226_APP.h"
#include "IIC_INA226.h"
#include "Delay.h"




/************************************************************
新版
*************************************************************/
unsigned int iread(unsigned char sla,unsigned char suba)
{ 
	pdata unsigned int out;
  I2CStart();               /*启动总线*/
  I2CSendByte(sla);            /*发送器件地址*/
  if(!(I2CWaitAck()))return 0;  
  I2CSendByte(suba);            /*发送器件子地址*/
  if(!(I2CWaitAck()))return 0; 
  I2CStart();               /*启动总线*/
  I2CSendByte(sla+1);
  if(!(I2CWaitAck()))return 0; 
  out=I2CReceiveByte();/*发送数据*/
  out*=256;
  I2CAck();  /*发送就答位*/   
  out+=I2CReceiveByte();
  I2CNoAck();
  I2CStop();                  /*结束总线*/ 
  return out;
}



INA226 INA226_data = {0,0,0,0,0.9875};



bit high_flag = 0;

bit write_ina226(uint8_t address, uint8_t con1, uint8_t con2)	  //写0H   0x0927
{ 
  I2CStart();             
  I2CSendByte(INA226_ADDR1);
  if(!(I2CWaitAck()))return 0; 
  I2CSendByte(address);               /*发送数据*/
  if(!(I2CWaitAck()))return 0;
  I2CSendByte(con1);               /*发送数据*/
  if(!(I2CWaitAck()))return 0;
  I2CSendByte(con2);               /*发送数据*/
  if(!(I2CWaitAck()))return 0;
  I2CStop(); /*结束总线*/        
  return 1;
}
void Read_INA226()			 //读电流，电压，温度
{
	INA226_data.Read_Data[0]=iread(0x80,4);
	INA226_data.Read_Data[1]=iread(0x80,2)*1.25;
	
	
	//读电流的数值
	if(!high_flag)
	{
		INA226_data.Current_Data = INA226_data.Read_Data[0] * INA226_data.Var_Iref;
		INA226_data.Voltage_Data = INA226_data.Read_Data[1];// * INA226_data.Current_Data / 1000000;
		//buff3 = (double)Ireal;	
	}
  else
	{
		INA226_data.Current_Data = INA226_data.Read_Data[0] * INA226_data.Var_Iref;
		INA226_data.Voltage_Data = INA226_data.Read_Data[1];// * INA226_data.Current_Data / 10000000;	
		//buff3 = (double)Ireal / 10;
	}
}

