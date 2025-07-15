#ifndef __DS18B20_H
#define __DS18B20_H 
//#include "sys.h"   

#include "Common.h"
#include "N76E003.h"
#include "Function_define.h"
#include "SFR_Macro.h"


							   
#define	DQ P30 //

   	
bit Init_DS18B20();			//≥ı ºªØDS18B20
uint8_t Read_tem(void);
#endif

