#include "Common.h"
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0


#define OLED_CS_Clr()  P15=0	//片选
#define OLED_CS_Set()  P15=1

#define OLED_RST_Clr() P03=0	//复位
#define OLED_RST_Set() P03=1

#define OLED_DC_Clr() P01=0	//数据/命令控制
#define OLED_DC_Set() P01=1

#define OLED_SCLK_Clr() P10=0	//时钟 D0（SCLK?
#define OLED_SCLK_Set() P10=1

#define OLED_SDIN_Clr() P00=0	//D1（MOSI） 数据
#define OLED_SDIN_Set() P00=1;





//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   

	     

//OLED控制用函数
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size2);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);


//大号字-中文-自添加
void OLED_ShowCHinese48(unsigned char x,unsigned char y,unsigned char no);
//大号字-字符数字-自添加
void OLED_ShowChar48(unsigned char x,unsigned char y,unsigned char no);
#endif  
	 



