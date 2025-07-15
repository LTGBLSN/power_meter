//////////////////////////////////////////////////////////////////////////////////	 
//              ----------------------------------------------------------------
//              GND  电源地
//              VCC  3.3v电源
//              D0   PA7
//              D1   PA6 SDA
//              RES  PA5
//              DC   PA4
//              CS   PA3 
//              ----------------------------------------------------------------
//
//******************************************************************************/
#include "stm32f10x.h"
#include <stdio.h>
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "bsp_iic.h"
#include "bsp_ina226.h"
#include "led.h" 
#include "TIME.h"
#include "key.h"

int main(void)
{
	
	//u8 i=0;
	//u8 ack=0;
	//int count=0;
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	mx_iic_init();     //初始化IIC
	mx_ina226_init();  //初始化ina226
	//led_init();
	Init_ssd1327();    //初始化屏幕
	OLED_Clear(0,0,128,128,0x00);  //清屏
	KEY_Init();
	
	TIM2_Getsample_Int(1999,7199);	//200ms任务定时
	
	/*
	//IIC地址扫描
	for(i=0x00;i<0xFF;i++)
	 {
		IIC_Start();
		IIC_Send_Byte(i);
		 ack = IIC_Wait_Ack();
		if(ack==0) 
		{
			printf("%x\r\n",i);
			OLED_ShowNum(16, 4, i, 6,16);
			
			count=1;
		}
		IIC_Stop();
		delay_ms(1);
	 }
	 if(count==0) printf("No IIC device found!\r\n");
	 count=0;
	delay_ms(1000);
	*/
	
	/*
	OLED_ShowChinese(8,8,0,16);   //电压
	OLED_ShowChinese(24,8,1,16);
	OLED_ShowString(40,8,":",16);
	OLED_ShowChinese(8,26,0,16);  //电流
	OLED_ShowChinese(24,26,2,16);
	OLED_ShowString(40,26,":",16);
	OLED_ShowChinese(8,44,3,16);  //功率
	OLED_ShowChinese(24,44,4,16);
	OLED_ShowString(40,44,":",16);
	*/
	while(1)
	{

		
	}
	
	
}


