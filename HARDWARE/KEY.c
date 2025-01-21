
#include "user.h"

//����KEY
void Config_Key()
{
	//����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//
	GPIO_InitTypeDef keystruct;
	//4������
	keystruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	//����ģʽ
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	//��������
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&keystruct);
	
}

//������⺯��

#define KEY_UP 1
#define KEY_DOWN 0
void Scan_Key()
{
	//����ֵ�Ƕ�����һ�����һ�����ŵĵ�ƽ
	u8 stat = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4);
	if(stat == KEY_DOWN)
	{
		
		delay_ms(2);//��ʱ
		if(stat == KEY_DOWN)
		{
			while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4));
			TurnOff_Led(LED3);
		}
		
		
	}
	
	u8 stat1 = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5);
	if(stat1 == KEY_DOWN)
	{
		
		delay_ms(2);
		if(stat1 == KEY_DOWN)
		{
			//���ּ��
			while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5));
			TurnOn_Led(LED3);
		}
		
	}
}




