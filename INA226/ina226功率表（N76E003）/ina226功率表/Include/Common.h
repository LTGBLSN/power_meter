#ifndef __COMMON__H
#define __COMMON__H

typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;

typedef bit                   BIT;
typedef unsigned char         UINT8;
typedef unsigned int          UINT16;
typedef unsigned long         UINT32;

typedef unsigned char         uint8_t;
typedef unsigned int          uint16_t;
typedef unsigned long         uint32_t;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;
 
typedef uint32_t  u32; 
typedef uint16_t u16;
typedef uint8_t  u8;




#define     CID_READ				0x0B
#define     DID_READ				0x0C

#define     ERASE_APROM				0x22
#define     READ_APROM				0x00
#define     PROGRAM_APROM			0x21
#define     ERASE_LDROM				
#define     READ_LDROM				
#define     PROGRAM_LDROM			
#define     READ_CFG					0xC0
#define     PROGRAM_CFG				0xE1
#define			READ_UID					0x04


void  InitialUART0_Timer1(UINT32 u32Baudrate); //T1M = 1, SMOD = 1
void  InitialUART0_Timer3(UINT32 u32Baudrate); //Timer3 as Baudrate, SMOD=1, Prescale=0
void  InitialUART1_Timer3(UINT32 u32Baudrate);
void  Send_Data_To_UART0(UINT8 c);
UINT8 Receive_Data_From_UART0(void);
void  Send_Data_To_UART1(UINT8 c);
UINT8 Receive_Data_From_UART1(void);
void  InitialUART1(UINT32 u32Baudrate);

extern bit BIT_TMP;

#endif
