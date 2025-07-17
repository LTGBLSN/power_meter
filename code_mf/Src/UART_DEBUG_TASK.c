//
// Created by 21481 on 2025/7/14.
//
#include "main.h"
#include "cmsis_os.h"
#include "uart_printf.h"
#include "bsp_ina226.h"

void UART_DEBUG_TASK()
{
    osDelay(1000);
    //初始化
    /*
	* 设置转换时间8.244ms,求平均值次数16，设置模式为分流和总线连续模式
	* 总数据转换时间 = 8.244*16 = 131.9ms
	*/
    INA226_SetConfig(0x45FF);

    /*
	* 分流电阻最大电压 = 32768 * 0.0000025V = 0.08192V
	* 设置分流电压转电流转换参数:电阻0.01R，分辨率0.2mA
	* 公式1
	* Current_LSB = 预期最大电流 / 2^15
	* Current_LSB = 5 / 32768 = 0.000152A ,选0.2ma
	* 公式2
	* CAL = 0.00512/(Current_LSB*R)
	* CAL = 0.00512/(0.0002*0.01)=2560 = 0x0a00
	*/
    INA226_SetCalibrationReg(0x0a00);
    while (1)
    {
        fVoltage = INA226_GetBusV();
        fCurrent = INA226_GetCurrent();
        fPower = INA226_GetPower();
        usart1_printf("%f,%f,%f \r\n",fCurrent,fPower,fVoltage);

//        osDelay(5);
        osDelay(1);
    }
}