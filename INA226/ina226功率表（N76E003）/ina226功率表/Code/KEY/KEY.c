
#include "key.h"



//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY0_PRES，KEY0按下
//KEY1_PRES，KEY1按下
//WKUP_PRES，WK_UP按下 
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY2==0||KEY3==0||KEY4==0||KEY5==0))
	{
		Timer1_Delay10ms(5);//去抖动 
		key_up=0;
		if(KEY2==0)
			return KEY2_PRES;
		else if(KEY3==0)
			return KEY3_PRES;
		else if(KEY4==0)
			return KEY4_PRES;
		else if(KEY5==0)
			return KEY5_PRES;
	}
	else if(KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1)
	key_up=1; 	     
	return 0;// 无按键按下
}


