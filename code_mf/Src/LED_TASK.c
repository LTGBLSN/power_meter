//
// Created by 21481 on 2025/7/14.
//
#include "main.h"
#include "cmsis_os.h"

void LED_TASK()
{
    while (1)
    {
        HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
        osDelay(300);
        osDelay(1);
    }
}