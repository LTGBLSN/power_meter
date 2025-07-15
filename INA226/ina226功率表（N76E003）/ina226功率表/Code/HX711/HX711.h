#ifndef __HX711_H
#define __HX711_H

#include "Common.h"
#include "N76E003.h"
#include "Function_define.h"
#include "SFR_Macro.h"

#define     SCL_H      P01=1;
#define     SCL_L      P01=0;
#define     SDA_R      P00


extern void Init_HX711pin(void);
extern UINT32 HX711_Read(void);
extern void Get_Maopi(void);
extern void Get_Weight(void);

extern UINT32 HX711_Buffer;
extern UINT32 Weight_MaopiAD;
extern s32 gWeight_Maopi;
extern s32 Weight_Shiwu;
extern UINT8 Flag_Error;

extern UINT8 gDigit;	//Î»Êý

#endif

