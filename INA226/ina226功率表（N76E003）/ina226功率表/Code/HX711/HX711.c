#include "HX711.h"
#include "Delay.h"

UINT32 HX711_Buffer;
UINT32 Weight_MaopiAD;
s32 gWeight_Maopi;
UINT32 Weight_ShiwuAD;
s32 Weight_Shiwu;
UINT8 Flag_Error = 0;

//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
#define GapValue 456.5

UINT8 gDigit = 0;	//λ��


void Init_HX711pin(void)
{
	P0M1 &= ~0x02;P0M2 |= 0x02; //P03 TM7711 ʱ����
  P0M1 |= 0x01;P0M2 &= ~0x01; //P04 TM7711 ������
}

void Delay__hx711_us(unsigned char t)
{
	while(t--);
}



//****************************************************
//��ȡHX711
//****************************************************
UINT32 HX711_Read(void)	//����128
{
	unsigned long count; 
	unsigned char i; 
	SCL_L; 
	count=0; 
	while(SDA_R); 
	//clr_EA;//��ֹ�����ж�
	for(i=0;i<24;i++)
	{ 
		SCL_H; 
		count=count<<1; 
		//Delay__hx711_us(2);
		SCL_L; 
		if(SDA_R)
		count++; 
	} 
 	SCL_H; 
	count=count^0x800000;//��25�������½�����ʱ��ת������
	SCL_L;
	//set_EA;//ʹ��ȫ���ж�
	return(count);
}

//****************************************************
//��ȡëƤ����
//****************************************************
void Get_Maopi(void)
{
	Weight_MaopiAD = HX711_Read();  
	
	//gWeight_Maopi = (unsigned int)((float)Weight_MaopiAD/GapValue); 
} 

//****************************************************
//����
//****************************************************
void Get_Weight(void)
{
	unsigned int X;
	HX711_Buffer = HX711_Read();
	if(HX711_Buffer > Weight_MaopiAD)			
	{
		Weight_ShiwuAD = HX711_Buffer;
		Weight_ShiwuAD = Weight_ShiwuAD - Weight_MaopiAD;				//��ȡʵ���AD������ֵ��
	
		//if(Weight_Shiwu == 0) || (Weight_Shiwu)
		Weight_Shiwu = (unsigned int)((float)Weight_ShiwuAD/GapValue); 	//����ʵ���ʵ������
																		//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
																		//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
																		//������Գ���������ƫСʱ����С����ֵ��
		
		//P05 = 0x00;
	}
	
	X = Weight_Shiwu;
	gDigit = 0;
	while(X)
	{
		X/=10; 
		gDigit++;
	}
}
