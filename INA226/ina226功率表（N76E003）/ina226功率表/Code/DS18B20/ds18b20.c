#include "ds18b20.h"


void Delay_OneWire(unsigned int t)
{
 int i;
        while(t--)
 {
       for(i=0;i<12;i++);
 }
}

bit Init_DS18B20(void)
{
	bit initflag = 0; 
	DQ = 1;      //���Ƚ��������ø�
	Delay_OneWire(12);  //������ʱ
	DQ = 0;      //�������������͵�ƽ
	Delay_OneWire(80);    //��ʱ��480~960US֮��
	DQ = 1;                     //���������ظߵ�ƽ
	Delay_OneWire(10);  // ��ʱ�ȴ�
	initflag = DQ;     // initflag����1��ʼ��ʧ��
	Delay_OneWire(5);     //���һ����ʱ
	return initflag;
}



//��DS18B20дһ���ֽ�

void Write_DS18B20(unsigned char dat)
{
 unsigned char i;
 for(i=0;i<8;i++)    //�ظ�ֱ�������������ֽ�
 {
 DQ = 0;  //��������������
 DQ = dat&0x01;
 Delay_OneWire(5);  //��ʱ45us
 DQ = 1;    //�����������ظߵ�ƽ1
 dat >>= 1;
 }
 Delay_OneWire(5);

}


//��DS18B20��ȡһ���ֽ�

unsigned char Read_DS18B20(void)
{
 int i;
 unsigned char dat; 
 for(i=0;i<8;i++)    //�ظ�����ֱ�����������ֽ�
 {
 DQ = 0;   //����������
 dat >>= 1;
 DQ = 1;   //����������
 if(DQ)
 {
 dat |= 0x80;
 }     
 Delay_OneWire(5);
 }
 return dat;
}


uint8_t Read_tem(void)
{
   unsigned char low,high;
	uint16_t temp;
   Init_DS18B20();       
   Write_DS18B20(0xCC);  //����64λROM��ַ��ֱ����DS18B20�����¶ȱ任���������һ���ӻ�����
   Write_DS18B20(0x44);   //�¶�ת��
   Delay_OneWire(200);


   Init_DS18B20();
   Write_DS18B20(0xCC);   
   Write_DS18B20(0xBE);   //��ȡ�¶�����


   low = Read_DS18B20();    //�Ͱ�λ
   high = Read_DS18B20();   //�߰�λ
  
   temp = high<<4;           //���ϳ�һ���ֽ�
   temp |= (low>>4);
  
   return temp;
}








