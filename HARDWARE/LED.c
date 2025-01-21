

#include "user.h"

//LED配置
void Config_Led()
{
	//1配置时钟 - 函数;;;
	//GPIOE  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	//2配置引脚
	//通过填写结构体的方式
	GPIO_InitTypeDef ledstruct;
	//LED灯链接三个引脚
	ledstruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	//配置引脚模式
	ledstruct.GPIO_Mode = GPIO_Mode_OUT;
	//输出类型
	ledstruct.GPIO_OType = GPIO_OType_PP;
	//上拉电阻
	ledstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	ledstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&ledstruct);
	
	//初始化
	GPIO_SetBits(GPIOE,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	
	//配置时钟

	
	
}

//点亮LED


void TurnOn_Led(unsigned int num)
{
	switch(num)
	{
		case LED1 : GPIO_ResetBits(GPIOE,GPIO_Pin_8);break;
		case LED2 : GPIO_ResetBits(GPIOE,GPIO_Pin_9);break;
		case LED3 : GPIO_ResetBits(GPIOE,GPIO_Pin_10);break;
	}
}
//熄灭LED
void TurnOff_Led(unsigned int num)
{
	switch(num)
	{
		case LED1 : GPIO_SetBits(GPIOE,GPIO_Pin_8);break;
		case LED2 : GPIO_SetBits(GPIOE,GPIO_Pin_9);break;
		case LED3 : GPIO_SetBits(GPIOE,GPIO_Pin_10);break;
	}
	
}

//延时函数
void mydelay(unsigned int time)
{
	unsigned int z = time * 100;
	while(z--);
}
//闪烁LED
void Flash_Led(unsigned int num)
{
	TurnOn_Led(num);
	mydelay(100);
	TurnOff_Led(num);
	mydelay(100);
}
//LED流水
void Flow_Led()
{
	TurnOn_Led(LED1);
	mydelay(100);
	TurnOff_Led(LED1);
	TurnOn_Led(LED2);
	mydelay(100);
	TurnOff_Led(LED2);
	TurnOn_Led(LED3);
	mydelay(100);
	TurnOff_Led(LED3);
	
//	mydelay(100);
//	TurnOn_Led(LED2);
//	mydelay(100);
//	TurnOff_Led(LED2);
//	mydelay(100);

}

void my_led()
{
	GPIO_ToggleBits(GPIOE,GPIO_Pin_8);
	delay_ms(50);
	GPIO_ToggleBits(GPIOE,GPIO_Pin_8);
	delay_ms(50);
}


void ToggleLed()
{
	GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
	delay_ms(50);	
	
}


