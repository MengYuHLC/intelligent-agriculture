
#include "user.h"


//1.��ʱ��-pwm���ú���
//beep������ - �豸���ӵ����ĸ����ţ�
//motoģ�� - �豸���ӵ����ĸ����ţ�
//��ʱ��2��ͨ��3����������
void TIM2_PWM_CH3_BEEP_CONFIG()
{
	//1.ʱ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//GPIOB ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//2.�������� ����ģʽ
	GPIO_InitTypeDef beeppwmstruct;
	beeppwmstruct.GPIO_Pin = GPIO_Pin_10;
	//pwm�Ǹ���ģʽ
	beeppwmstruct.GPIO_Mode = GPIO_Mode_AF;
	//����ģʽ ��� 0  1 ��
	beeppwmstruct.GPIO_OType = GPIO_OType_PP;
	//��������
	beeppwmstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//������Ӧ
	beeppwmstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&beeppwmstruct);
	
	//�������� pb10 - ���ó� ��ʱ��2�Ĺ���
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2);
	
	//2.��ʱ����������
	TIM_TimeBaseInitTypeDef timstruct;
	//�����̵� ��ֵ ������  Ԥ��Ƶϵ��
	timstruct.TIM_Prescaler = 84 - 1;
	//װ����ֵ
	timstruct.TIM_Period = 1000 - 1;
	//���ϼ�����ʽ
	timstruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&timstruct);
	
	//3.pwm ����ͨ��
	TIM_OCInitTypeDef oc3struct;
	//ģʽ
	oc3struct.TIM_OCMode = TIM_OCMode_PWM1;
	//�Ƚ�ʹ��
	oc3struct.TIM_OutputState = TIM_OutputState_Enable;
	//���� - ��Ч��ƽ
	oc3struct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2,&oc3struct);
	 
	//4. ��ʱ��ʹ�� 
	TIM_Cmd(TIM2,ENABLE); 
	//5.�Ƚϲ���Ĵ���ʹ�� 
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); 
	//6.�Զ�װ����ֵʹ�� 
	TIM_ARRPreloadConfig(TIM2,ENABLE); 
}

//beep pwm��������
void BEEP_PWM_DRIVER()
{
	unsigned int value = 0 ,flg = 1 ;
	//value 0 - 60 - 0 
	int num = 200;
	while(num--)
	{
		if(flg == 1)
			value++;
		else
			value--;
		
		//�жϷ�Χ
		if(value > 60)
			flg = 0 ; 
		if(value == 0 )
			flg = 1;
		//�޸Ĳ���ȽϼĴ�������ֵ
		TIM_SetCompare3(TIM2,value);
		delay_ms(10);
	}
}


//2.���ģ��
//��ʱ������20ms>>> ����ʱ��/Ԥ��Ƶ  + ׳����ֵ---׼��һ��������ֵ
//�ߵ�ƽʱ��     0.5ms- 1ms - 1.5m - 2ms - 2.5ms֮��
//���ת���Ƕ��� 0�� - 45---90---135-- 180�ȣ�
void TIM4_PWM_CH1_MOTOR_CONFIG()
{
	//1.����ʱ�� - timer + GPIO 
	//84MHZ  GPIOD 12 ; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	//2.GPIOD - 12 ; 
	GPIO_InitTypeDef motostruct;
	//����
	motostruct.GPIO_Pin = GPIO_Pin_12;
	//����ģʽ
	motostruct.GPIO_Mode = GPIO_Mode_AF;
	//��������
	motostruct.GPIO_PuPd = GPIO_PuPd_UP;
	//����
	motostruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOD,&motostruct);
	
	//3.���Ÿ���ӳ��  PD12 - TIM2
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	
	//4.���ö�ʱ��
	TIM_TimeBaseInitTypeDef timstruct;
	//�Զ�װ����ֵ - ��ʱ����ȷ��
	timstruct.TIM_Period = 20000 - 1; //��ʱ����20ms
	//��Ƶϵ��
	//84M / 84 = 1 M
	//1000000hz  ����/��
	//һ������: 1us
	//��ʱʱ�� 20ms = 20000us / 1 = 20000 ����ֵ��
	timstruct.TIM_Prescaler = 84 -1; 
	timstruct.TIM_CounterMode = TIM_CounterMode_Up;
	timstruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4,&timstruct);
	
	//5 ����ͨ��
	TIM_OCInitTypeDef oc1struct;
	//cntС�� ccr3 - ����Ч��ƽ
	oc1struct.TIM_OCMode = TIM_OCMode_PWM1;
	//�ߵ�ƽ����Ч��ƽ
	oc1struct.TIM_OCPolarity = TIM_OCPolarity_High;
	//ʹ��
	oc1struct.TIM_OutputState = TIM_OutputState_Enable;
	//��ʼ����ȽϼĴ�������ֵ
	oc1struct.TIM_Pulse = 0 ; 
	TIM_OC1Init(TIM4,&oc1struct);

	//6 �Ƚϲ���Ĵ���ʹ��
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	//7 �Զ�װ����ֵ�Ĵ�����ʹ��
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	
	//8 ��ʱ�������ʹ��
	TIM_Cmd(TIM4,ENABLE);
}

//
void MOTO_LEFT()
{
	//500 * 1us = 0.5ms
	TIM_SetCompare1(TIM4,500);
	delay_ms(1000);
}

void MOTO_RIGHT()
{
	TIM_SetCompare1(TIM4,2500);
	delay_ms(1000);
}
	
//3.ֱ�����ģ��
void TIM12_PWM_CH2_FAN_CONFIG()
{
	
	

}
//4.LEDģ�飻
void TIM1_PWM_CH1_LED_CONFIG()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//1TIM1ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); 
	//2E��ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	
	//3��������ʱ��1
	TIM_DeInit(TIM1);
	
	//4E���9�����Ÿ���Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 
	
	//5����E����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;   
	//���ù���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
	//���츴�����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   
	//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	//5��ʼ������
	GPIO_Init(GPIOE,&GPIO_InitStructure);  
	
	//6�߼���ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler=400;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=100;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 1; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
		
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 	        
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	//7����Tָ���Ĳ�����ʼ������TIM1 4OC1
//	TIM_OCInitStructure.TIM_Pulse = 100;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
	//8.ʹ�ܶ�ʱ��
	TIM_Cmd(TIM1, ENABLE);  	
	//9�������ģʽʹ��
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
//������
void ledtestpwm()
{
	int num =200;
	u16 led0pwmval=0;    
	u8 dir=1; 
	while(num --) 
	{
 		delay_ms(10);
		//dir==1 led0pwmval����
		if(dir)
			led0pwmval++;
		else     //dir==0 led0pwmval�ݼ� 
			led0pwmval--;
		//led0pwmval����300�󣬷���Ϊ�ݼ�
 		if(led0pwmval>100)
			dir=0;
		//led0pwmval�ݼ���0�󣬷����Ϊ����
		if(led0pwmval==0)
			dir=1;	
		//�޸ıȽ�ֵ���޸�ռ�ձ�	
		TIM_SetCompare1(TIM1,led0pwmval);	
	}
}
