
#include "user.h"
int Stat = 0;
////�ж�����
////GPIOE-6
//void INTERRUPT_KEY3_INIT()
//{
//	//1.ʱ������
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
//	//2.�õ�io�� 	GPIOE-6
//	GPIO_InitTypeDef key_inter_struct;
//	key_inter_struct.GPIO_Pin = GPIO_Pin_6;
//	//��������ģʽ
//	key_inter_struct.GPIO_Mode = GPIO_Mode_IN;
//	//��������
//	key_inter_struct.GPIO_PuPd = GPIO_PuPd_UP;
//	//��Ӧ�ٶ�
//	key_inter_struct.GPIO_Speed = GPIO_Low_Speed;
//	GPIO_Init(GPIOE,&key_inter_struct);
//	
//	
//	//3.��6����������λ�ж� - ���Ÿ�������
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
//	//4.�ж�ѡ������
//	EXTI_InitTypeDef extistruct;
//	//ʹ��
//	extistruct.EXTI_LineCmd = ENABLE;
//	//�ж�ģʽ
//	extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	//����ʱ
//	extistruct.EXTI_Trigger = EXTI_Trigger_Falling;
//	//
//	extistruct.EXTI_Line = EXTI_Line6;
//	EXTI_Init(&extistruct);
//	
//	//5.�жϳ�ʼ������
//	NVIC_InitTypeDef nvicstruct;
//	//�ж����� - �ⲿ�ж�
//	nvicstruct.NVIC_IRQChannel = EXTI9_5_IRQn;
//	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
//	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
//	nvicstruct.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&nvicstruct);
//	
//	//����
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	
//	
//}

////�жϺ��� - �ж�ִ�к���
////ϵͳע�ᣬ���ֲ���д���---- EXTI3XXXX_IRQHandler()
////�ҵ�ע�����ֵ�ѡ��ù�����
//void EXTI9_5_IRQHandler()
//{
//	TurnOn_Beep();
//	EXTI_ClearITPendingBit(EXTI_Line6);
//	
//}

//�ж�����
void  INTERRUPT_KEY2_INIT()
{
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//����io��
	GPIO_InitTypeDef key_inter_struct;
	key_inter_struct.GPIO_Mode = GPIO_Mode_IN;
	key_inter_struct.GPIO_Pin = GPIO_Pin_5;
	key_inter_struct.GPIO_PuPd = GPIO_PuPd_UP;
	key_inter_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&key_inter_struct);
	
	//���������ж�
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	EXTI_InitTypeDef extistruct;
	extistruct.EXTI_Line = EXTI_Line5;
	extistruct.EXTI_LineCmd = ENABLE;
	extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
	extistruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&extistruct);
	
	
	//�жϳ�ʼ������
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

