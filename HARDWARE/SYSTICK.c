#include "user.h"

//�����ں˶�ʱ��
void my_systick_config()
{
		//ѡ��ʱ��Դ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	
	//��ʼֵ��д
	if(SysTick_Config(SystemCoreClock/1000))
	{
		//���Եƣ�����˵��ʧ����
		TurnOn_Led(LED3);
	}
	
	
}

//��ʱ����
unsigned int timedelay = 0;

void SysTick_Handler()
{
	if(timedelay != 0 )
	timedelay--;
}


//�Զ���
void my_delay_ms(unsigned int num)
{
	timedelay = num;
	while(timedelay != 0);
	
	
}

