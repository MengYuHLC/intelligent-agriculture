
#include "user.h"

//����������
void Config_Beep()
{
	//����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//��������
	GPIO_InitTypeDef beepstruct;
	beepstruct.GPIO_Pin = GPIO_Pin_10;
	
	//���ģʽ
	beepstruct.GPIO_Mode = GPIO_Mode_OUT;
	
	//����ģʽ
	beepstruct.GPIO_OType = GPIO_OType_PP;
	
	//��������
	beepstruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	//��Ӧ�ٶ�
	beepstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&beepstruct);
	
	//��ʼ������
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	
}

//�򿪷�����
void TurnOn_Beep()
{
	//��ĳ�����е�ĳ�������ϲ�ͬ�ĵ�ƽ
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);

	
}
//�رշ�����
void TurnOff_Beep()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);
}



//������������
void Flash_Beep()
{
	TurnOn_Beep();
	mydelay(200);
	TurnOff_Beep();
	mydelay(200);
}


