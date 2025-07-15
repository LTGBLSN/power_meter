
#include "ADC.h"



uint16_t gVot_BAT;												//��ص�ѹֵ
uint32_t gVCC_voltage = 0;

bit gVCC_Flag = 0;	//����־λ

void READ_BANDGAP()
{/*
		unsigned int i;
		UINT8 BandgapHigh,BandgapLow,BandgapMark;
		double Bandgap_Value,Bandgap_Voltage_Temp;
	
		set_IAPEN;
		IAPCN = READ_UID;
		IAPAL = 0x0d;
    IAPAH = 0x00;
    set_IAPGO;
		BandgapLow = IAPFD;
		BandgapMark = BandgapLow&0xF0;
			
		if (BandgapMark==0x80)
		{
				BandgapLow = BandgapLow&0x0F;
				IAPAL = 0x0C;
				IAPAH = 0x00;
				set_IAPGO;
				BandgapHigh = IAPFD;
				Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
				Bandgap_Voltage_Temp = Bandgap_Value*3/4;
				Bandgap_Voltage = Bandgap_Voltage_Temp - 33;			//the actually banggap voltage value is similar this value.
		}
		if (BandgapMark==0x00)
		{
				BandgapLow = BandgapLow&0x0F;
				IAPAL = 0x0C;
				IAPAH = 0x00;
				set_IAPGO;
				BandgapHigh = IAPFD;
				Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
				Bandgap_Voltage= Bandgap_Value*3/4;
		}
		if (BandgapMark==0x90)
		{
				IAPAL = 0x0E;
				IAPAH = 0x00;
				set_IAPGO;
				BandgapHigh = IAPFD;
				IAPAL = 0x0F;
				IAPAH = 0x00;
				set_IAPGO;
				BandgapLow = IAPFD;
				BandgapLow = BandgapLow&0x0F;
				Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
				Bandgap_Voltage= Bandgap_Value*3/4;
		}
		clr_IAPEN;
		
		*/
		
	
	
}


xdata uint32_t voltage=0;

xdata u8 Num=0;
xdata uint16_t gAve_BATVot = 0;

xdata uint16_t BandGap_H, BandGap_L;
xdata uint16_t BandGap_v;
void ADC_ISR()
{
	xdata uint16_t  AIN3_H, AIN3_L/*,BandGap_v*/;	
  xdata uint32_t AIN3_v = 0;

	Enable_ADC_BandGap;		
	clr_ADCF;
	set_ADCS;				// Each time ADC start trig signal
	while(ADCF == 0);
		clr_ADCF;
	set_ADCS;				// Each time ADC start trig signal
	while(ADCF == 0);
		clr_ADCF;
	set_ADCS;				// Each time ADC start trig signal
	while(ADCF == 0);
	BandGap_H = ADCRH;
	BandGap_L = ADCRL;
	BandGap_v = BandGap_H << 4 | BandGap_L;

	
	Enable_ADC_AIN6;
	
	clr_ADCF;
	set_ADCS;//ʹ��ADCS������ADC����
	
	
	while(ADCF == 0);
	clr_ADCF;//���ADCת����ɱ�־��������һ��ת��
	set_ADCS;//������ת����ɺ�ADCS��Ӳ����0����Ҫ����ʹ��
	AIN3_H = ADCRH;
	AIN3_L = ADCRL;
	AIN3_v = AIN3_H << 4 | AIN3_L;

	voltage = (uint16_t)((uint32_t)AIN3_v * 1220 / BandGap_v );		
	
	gVot_BAT = (uint32_t) (voltage * ((RES_PAR + RES_SER) / 100) / RES_PAR );
	
	Num ++;	
	
	gAve_BATVot += gVot_BAT;
	
	gVot_BAT = gAve_BATVot / Num;
	
	if(Num >= 50)
	{
		Num = 0;
		gAve_BATVot = 0;
	}
	
	
	Enable_ADC_AIN5;
	
	clr_ADCF;
	set_ADCS;//ʹ��ADCS������ADC����
	
	while(ADCF == 0);
	clr_ADCF;//���ADCת����ɱ�־��������һ��ת��
	set_ADCS;//������ת����ɺ�ADCS��Ӳ����0����Ҫ����ʹ��
	
	AIN3_H = ADCRH;
	AIN3_L = ADCRL;
	AIN3_v = AIN3_H << 4 | AIN3_L;

	gVCC_voltage = (uint16_t)((uint32_t)AIN3_v * 1220 / BandGap_v );	
}





