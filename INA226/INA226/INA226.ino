//INA226库: https://github.com/RobTillaart/INA226
// 测量电压范围：0~36V
// INA226最大采集稳定分流电压：81.92mV
// 测量电流范围取决于分压电阻的阻值和最大分压电压。一般来说，分压电阻越小，测量电流范围越大。例如，使用0.1R的分压电阻时，最大测量电流为817.2mA
// 默认分流电阻5mΩ，可采集的最大电流：81.92mV/10mΩ = 8.192A
// 芯片工作电压：2.7V~5.5V
// 默认IIC地址：0x40
//
#include "INA226.h"
#include "Wire.h"

INA226 INA(0x40);                             //I2C地址


//电压电流采样
void VA(){
  float V = INA.getBusVoltage();              //VBUS电压V
  float mA = INA.getCurrent_mA();             //采样电阻电流mA
  float mW = INA.getPower_mW();               //功率
  float mV = INA.getShuntVoltage_mV();        //采样电阻分压             
  Serial.print( V);  Serial.print(" V  \t");
  Serial.print(mA);  Serial.print(" mA \t");
  Serial.print(mW);  Serial.print(" mW \t");
  Serial.print(mV);  Serial.print(" mV \t");
  Serial.println();  
}

//电压电流采样2
void VA2(){
  float V = INA.getBusVoltage();              //VBUS电压V
  float mV = INA.getShuntVoltage_mV();        //采样电阻分压 
  float A = mV/10;                             //采样电阻分压/采样电阻值 = 电流
  Serial.print( V);  Serial.print(" V  \t");
  Serial.print(mV);  Serial.print(" mV \t");
  Serial.print( A, 4);  Serial.print(" A  \t");
  Serial.println();  
}


void setup(){
  Serial.begin(115200);
  Wire.begin();
  INA.setMaxCurrentShunt(8, 0.01);  //最大电流A,分流电阻值R
}

void loop(){
  //VA();
  VA2();

  delay(1000);
}

