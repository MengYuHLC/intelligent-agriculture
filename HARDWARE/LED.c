

#include "user.h"

//LED����
void Config_Led()
{
	//1����ʱ�� - ����;;;
	//GPIOE  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	//2��������
	//ͨ����д�ṹ��ķ�ʽ
	GPIO_InitTypeDef ledstruct;
	//LED��������������
	ledstruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	//��������ģʽ
	ledstruct.GPIO_Mode = GPIO_Mode_OUT;
	//�������
	ledstruct.GPIO_OType = GPIO_OType_PP;
	//��������
	ledstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	ledstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&ledstruct);
	
	//��ʼ��
	GPIO_SetBits(GPIOE,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	
	//����ʱ��

	
	
}

//����LED


void TurnOn_Led(unsigned int num)
{
	switch(num)
	{
		case LED1 : GPIO_ResetBits(GPIOE,GPIO_Pin_8);break;
		case LED2 : GPIO_ResetBits(GPIOE,GPIO_Pin_9);break;
		case LED3 : GPIO_ResetBits(GPIOE,GPIO_Pin_10);break;
	}
}
//Ϩ��LED
void TurnOff_Led(unsigned int num)
{
	switch(num)
	{
		case LED1 : GPIO_SetBits(GPIOE,GPIO_Pin_8);break;
		case LED2 : GPIO_SetBits(GPIOE,GPIO_Pin_9);break;
		case LED3 : GPIO_SetBits(GPIOE,GPIO_Pin_10);break;
	}
	
}

//��ʱ����
void mydelay(unsigned int time)
{
	unsigned int z = time * 100;
	while(z--);
}
//��˸LED
void Flash_Led(unsigned int num)
{
	TurnOn_Led(num);
	mydelay(100);
	TurnOff_Led(num);
	mydelay(100);
}
//LED��ˮ
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


