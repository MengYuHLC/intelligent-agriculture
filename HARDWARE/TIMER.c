
#include "user.h"


//1.��ʱ���� - ��ʱ��Ȼʱ�� + ����-�����������  
//2.���pwm����
//Ƭ�϶�ʱ��
//��ʱ�� 1 + 8 ���߼���ʱ��
//������ʱ�� 6 7 �� DAC �������ź�ת����ģ���ź����
//ͨ�ö�ʱ�� �� �㹻����
// 2 3 4 5 9 10 11 12 13 14;
//��̷���ȫһ��
//λ����һ��
//ִ���жϺ��� �� ��ʱ��Ҳ���жϺ���
//1 Ԥ��Ƶϵ�� - 
//2 �Զ�װ����ֵ �� ������ʱ���ٸ���������

void TIMER4_Config(u16 psc , u16 arr)
{
	//1 ���� ʱ��
	//APB1 >>>> 42MHZ
	//��ʱ���ڴ˴� ����Ϊ2�� ���� 84MHZ
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//2�� -- 42  4��---21MHZ
	//1 ������ʱ�ӣ�����ʱ��/��Ƶϵ�� = ������ʱ��
	//2 1/������ʱ�� = ��������
	//��������*�Զ�װ����ֵ = ��ʱʱ��
	
	//2 ����ʱ�ӵ�Ԫ
	TIM_TimeBaseInitTypeDef tim4struct;
	//��ʱ����װ���� - ��д�ṹ��ķ�ʽ
	//�Զ�װ����ֵ 5000-1
	tim4struct.TIM_Period = arr;
	//Ԥ��Ƶϵ��
	tim4struct.TIM_Prescaler = psc;
	//ʱ�ӷָ�
	tim4struct.TIM_ClockDivision = TIM_CKD_DIV1;
	//���ϼ���ģʽ
	tim4struct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&tim4struct);
	
	//3.����ʱ��ִ���жϺ���
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	//4 ��ʱ��ʹ��
	TIM_Cmd(TIM4,ENABLE);
	
	//5 �����жϵȼ�����
	NVIC_InitTypeDef nvicstruct;
	//��ʱ���ж����� �� stm32f4xx.h �в���
	nvicstruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	// 0 1 2 3 
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0 ;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
	
}

u8 flg = 0;
void TIM4_IRQHandler()
{
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	if(flg % 2 == 0)
	{
		TurnOn_Led(LED2);
		flg++;
	}
	else if(flg % 2 == 1)
	{
		TurnOff_Led(LED2);
		flg++;
	}
//	if(flg > 10000)
//		flg = 0;
}

