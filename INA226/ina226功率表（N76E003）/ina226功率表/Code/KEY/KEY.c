
#include "key.h"



//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY0_PRES��KEY0����
//KEY1_PRES��KEY1����
//WKUP_PRES��WK_UP���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY2==0||KEY3==0||KEY4==0||KEY5==0))
	{
		Timer1_Delay10ms(5);//ȥ���� 
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
	return 0;// �ް�������
}


