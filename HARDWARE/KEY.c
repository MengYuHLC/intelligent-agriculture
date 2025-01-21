
#include "user.h"

//配置KEY
void Config_Key()
{
	//配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//
	GPIO_InitTypeDef keystruct;
	//4号引脚
	keystruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	//输入模式
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	//上拉电阻
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&keystruct);
	
}

//按键检测函数

#define KEY_UP 1
#define KEY_DOWN 0
void Scan_Key()
{
	//返回值是读到哪一组的哪一个引脚的电平
	u8 stat = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4);
	if(stat == KEY_DOWN)
	{
		
		delay_ms(2);//延时
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
			//松手检测
			while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5));
			TurnOn_Led(LED3);
		}
		
	}
}




