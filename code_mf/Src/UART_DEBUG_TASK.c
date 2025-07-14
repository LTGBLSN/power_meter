//
// Created by 21481 on 2025/7/14.
//
#include "main.h"
#include "cmsis_os.h"
#include "uart_printf.h"

void UART_DEBUG_TASK()
{
    while (1)
    {
        usart1_printf("helloword \r\n");
        osDelay(5);
        osDelay(1);
    }
}