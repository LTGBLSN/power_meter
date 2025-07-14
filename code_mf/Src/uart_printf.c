#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
extern UART_HandleTypeDef huart1;
void usart1_printf(const char *fmt, ...)
{
    static uint8_t tx_buf[256] = {0};
    static va_list ap;
    static uint16_t len;
    va_start(ap, fmt);
		
    //return length of string 
    //�����ַ�������
    len = vsprintf((char *)tx_buf, fmt, ap);

    va_end(ap);

    HAL_UART_Transmit(&huart1,tx_buf, len,100);//�����޸ķ��͵Ĵ��ڣ���������ġ�extern�������

}

