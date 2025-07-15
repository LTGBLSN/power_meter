#ifndef __KEY_H
#define __KEY_H	 

#include "Common.h"
#include "N76E003.h"
#include "Delay.h"


#define KEY2_PRES	1		//KEY0按下
#define KEY3_PRES	2		//KEY1按下
#define KEY4_PRES	3		//WK_UP按下
#define KEY5_PRES	4		//WK_UP按下

#define KEY2  P10   	//
#define KEY3  P11   	//
#define KEY4  P12   	//
#define KEY5  P17   	//

u8 KEY_Scan(u8 mode);

#endif