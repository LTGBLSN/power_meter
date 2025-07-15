#include "IIC_INA226.h"
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#include "Delay.h"



#define SCLK_Clr() SCL=0
#define SCLK_Set() SCL=1
#define SDIN_Clr() SDA=0
#define SDIN_Set() SDA=1


#define SYS_CLK_EN              0
#define SYS_SEL                 2
#define SYS_DIV_EN              0                   //0: Fsys=Fosc, 1: Fsys = Fosc/(2*CKDIV)
#define SYS_DIV                 1
#define I2C_CLOCK               2
#define TEST_OK                 0x00
bit I2C_Reset_Flag;

#define OLED_CMD  0	//???
#define OLED_DATA 1	//???
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	



void SomeNOP7()
{
	unsigned char del=20;	
	while(del--);
}

 
//IIC初始化
void IIC_Init(void)
{
	P13_PushPull_Mode;					// Modify SCL pin to Open drain mode. don't forget the pull high resister in circuit
	P14_PushPull_Mode;					// Modify SDA pin to Open drain mode. don't forget the pull high resister in circuit

	/* Set I2C clock rate */
	I2CLK = I2C_CLOCK; 

	/* Enable I2C */
	set_I2CEN;   
	SDIN_Set();
	SCLK_Set();
}
 
//产生IIC起始信号
bit I2CStart()
{
	SDA=1; SomeNOP7();
	if(!SDA) SomeNOP7();
	if(!SDA) SomeNOP7();
	if(!SDA) SomeNOP7();
	SCL=1; SomeNOP7();
	if(!SDA) return 0;
	SDA=0; SomeNOP7();
	while(SDA) return 0;
	SCL=0;
	return 1;
}	  
//产生IIC停止信号
void I2CStop(void)
{
SDA=0;SomeNOP7();
SCL=0;SomeNOP7();
SCL=1;SomeNOP7();
SDA=1;
if(!SDA) 	{	SCL=0;SomeNOP7();	SCL=1;SomeNOP7(); }
if(!SDA) 	{	SCL=0;SomeNOP7();	SCL=1;SomeNOP7(); }
if(!SDA) 	{	SCL=0;SomeNOP7();	SCL=1;SomeNOP7(); }		
}


void I2CAck(void)
{	SDA=0;SomeNOP7(); SCL=0;SomeNOP7(); SCL=1;SomeNOP7(); SCL=0;SomeNOP7(); }

void I2CNoAck(void)
{	SDA=1;SomeNOP7(); SCL=0;SomeNOP7();	SCL=1;SomeNOP7(); SCL=0;SomeNOP7(); }


bit I2CWaitAck(void) 	
{	
	SCL=0;SomeNOP7(); SDA=1;SomeNOP7();	
	SCL=1;SomeNOP7();
	while(SDA)	 { SCL=0; return 0; }
	SCL=0;
	return 1;
}


//IIC发送一个字节	  
void I2CSendByte(unsigned char demand) //数据从高位到低位//
{     
	unsigned char i=8;
	while(i--)
	{ SCL=0;	 SomeNOP7();
	 SDA=(bit)(demand&0x80);
	 demand<<=1; SomeNOP7();
	 SCL=1;	 SomeNOP7();
	}
	SCL=0;
} 	    


unsigned char I2CReceiveByte(void)  
{
	unsigned char i=8,ddata=0;
	SDA=1;	 
	while(i--)	{ ddata<<=1;      
		SCL=0;	 SomeNOP7();
		SCL=1;	 SomeNOP7(); 
	if(SDA)	 {	ddata|=0x01; }
	}
	SCL=0;
	return ddata;
}
