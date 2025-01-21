#include "user.h"

//配置内核定时器
void my_systick_config()
{
		//选择时钟源
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	
	//初始值填写
	if(SysTick_Config(SystemCoreClock/1000))
	{
		//调试灯，亮了说明失败了
		TurnOn_Led(LED3);
	}
	
	
}

//延时函数
unsigned int timedelay = 0;

void SysTick_Handler()
{
	if(timedelay != 0 )
	timedelay--;
}


//自定义
void my_delay_ms(unsigned int num)
{
	timedelay = num;
	while(timedelay != 0);
	
	
}

