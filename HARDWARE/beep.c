
#include "user.h"

//蜂鸣器配置
void Config_Beep()
{
	//配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//配置引脚
	GPIO_InitTypeDef beepstruct;
	beepstruct.GPIO_Pin = GPIO_Pin_10;
	
	//输出模式
	beepstruct.GPIO_Mode = GPIO_Mode_OUT;
	
	//推挽模式
	beepstruct.GPIO_OType = GPIO_OType_PP;
	
	//上拉电阻
	beepstruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	//响应速度
	beepstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&beepstruct);
	
	//初始化引脚
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	
}

//打开蜂鸣器
void TurnOn_Beep()
{
	//向某个组中的某个引脚上不同的电平
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);

	
}
//关闭蜂鸣器
void TurnOff_Beep()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);
}



//蜂鸣器警报音
void Flash_Beep()
{
	TurnOn_Beep();
	mydelay(200);
	TurnOff_Beep();
	mydelay(200);
}


