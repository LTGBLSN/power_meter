#ifndef __ADC__H
#define __ADC__H


#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"


#define RES_PAR 1500		//并联电阻
#define RES_SER 20000	  //串联电阻


//void ADC_Init();

void READ_BANDGAP();

void ADC_ISR();

extern uint16_t gVot_BAT;

extern uint32_t gVCC_voltage;

extern bit gVCC_Flag;	//充电标志位

#endif
