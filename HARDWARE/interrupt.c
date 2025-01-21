
#include "user.h"
int Stat = 0;
////中断配置
////GPIOE-6
//void INTERRUPT_KEY3_INIT()
//{
//	//1.时钟问题
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
//	//2.用到io口 	GPIOE-6
//	GPIO_InitTypeDef key_inter_struct;
//	key_inter_struct.GPIO_Pin = GPIO_Pin_6;
//	//配置引脚模式
//	key_inter_struct.GPIO_Mode = GPIO_Mode_IN;
//	//上拉电阻
//	key_inter_struct.GPIO_PuPd = GPIO_PuPd_UP;
//	//响应速度
//	key_inter_struct.GPIO_Speed = GPIO_Low_Speed;
//	GPIO_Init(GPIOE,&key_inter_struct);
//	
//	
//	//3.把6号引脚设置位中断 - 引脚复用问题
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
//	//4.中断选项问题
//	EXTI_InitTypeDef extistruct;
//	//使能
//	extistruct.EXTI_LineCmd = ENABLE;
//	//中断模式
//	extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	//按下时
//	extistruct.EXTI_Trigger = EXTI_Trigger_Falling;
//	//
//	extistruct.EXTI_Line = EXTI_Line6;
//	EXTI_Init(&extistruct);
//	
//	//5.中断初始化问题
//	NVIC_InitTypeDef nvicstruct;
//	//中断类型 - 外部中断
//	nvicstruct.NVIC_IRQChannel = EXTI9_5_IRQn;
//	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
//	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
//	nvicstruct.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&nvicstruct);
//	
//	//分组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	
//	
//}

////中断函数 - 中断执行函数
////系统注册，名字不能写别的---- EXTI3XXXX_IRQHandler()
////找到注册名字的选项，拿过来用
//void EXTI9_5_IRQHandler()
//{
//	TurnOn_Beep();
//	EXTI_ClearITPendingBit(EXTI_Line6);
//	
//}

//中断配置
void  INTERRUPT_KEY2_INIT()
{
	//配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//配置io口
	GPIO_InitTypeDef key_inter_struct;
	key_inter_struct.GPIO_Mode = GPIO_Mode_IN;
	key_inter_struct.GPIO_Pin = GPIO_Pin_5;
	key_inter_struct.GPIO_PuPd = GPIO_PuPd_UP;
	key_inter_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&key_inter_struct);
	
	//配置引脚中断
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	EXTI_InitTypeDef extistruct;
	extistruct.EXTI_Line = EXTI_Line5;
	extistruct.EXTI_LineCmd = ENABLE;
	extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
	extistruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&extistruct);
	
	
	//中断初始化问题
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	
}
void EXTI9_5_IRQHandler()
{
	
	GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
	Stat = (Stat + 1)%2;
	
	EXTI_ClearITPendingBit(EXTI_Line5);
}

