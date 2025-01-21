
#include "user.h"

extern int Stat;
extern char wendu[2];//存储温度，wendu[0]代表整数wendu[1]代表小数
extern char shidu[2];//存储湿度
extern u8 sendbuf[SEND_BUFF_SIZE];//DMA使用
#define READ_DHT11_OK 0
#define READ_DHT11_NOT_OK 1
#define READ_ADC_LIGHT_OK 0
#define READ_ADC_LIGHT_NOT_OK 1
#define humidity 40//湿度阈值，超过这个值则触发后面的动作
u8 temp;
u8 humi;
int main()
{
	delay_init(168);//初始化内核
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//进行优先级分组
	Config_Led();//初始化LED
	Config_Beep();//初始化BEEP
	Config_Key();//初始化KEY
	my_usart1_config();//初始化串口1 跳线帽连接上面两根，使用串口调试助手进行信息发送
	iic_init();//初始化i2c
	InitOLed();//初始化oled
	TIM1_PWM_CH1_LED_CONFIG();//初始化LED——pwm	
	ADC1_LIGHT_SENSOR_Config();//adc 的配置
	TIM2_PWM_CH3_BEEP_CONFIG();//定时器2的通道3驱动蜂鸣器
	INTERRUPT_KEY2_INIT();//初始化中断器,使用中断进行模式的切换，按键二按下切换模式


char tempStr[16]; // 存储温度字符串
char humiStr[16]; // 存储湿度字符串
char errorStr[16] = "error:no data";
char lightStr[16];
char voltageStr[16];

TIM_Cmd(TIM1, ENABLE);
TurnOff_Led(LED3);//默认为按键一按下状态	                                                  
int index = 1;
	while(1)
	{
		if(Stat == 0)
		{
			if(index)
			{
				OLed_Fill(0x00);
			}
			DHT11_Config();//初始化DHT11和串口1一起使用
			TIM_Cmd(TIM1, ENABLE);

			
			DHT11_ReadData(&temp,&humi);	//温湿度传感器
			sprintf(wendu,"%d",temp);
			sprintf(shidu,"%d",humi);	
			sprintf(tempStr, "Temp: %d C", temp);// 格式化温度和湿度为字符串
			sprintf(humiStr, "Humi: %d %%", humi);

			
			OLED_ShowString(0, 0, tempStr); // 在第 1 行显示温度
			OLED_ShowString(0, 2, humiStr); // 在第 2 行显示湿度

			u16 light = ADC1_get_light_value();
			if(Check_LightSensor_Data() == READ_ADC_LIGHT_OK)
			{
				sprintf(lightStr, "light: %d",light);
				OLED_ShowString(0, 4, lightStr);
			}
			
			u16 voltage = ADC1_get_voltage_Average_value();
			if(Check_VoltageSensor_Data() == READ_ADC_LIGHT_OK)
			{
				sprintf(voltageStr, "voltage: %d",voltage);
				OLED_ShowString(0, 6, voltageStr);
			}
			
			if(humi >= humidity)//
			{
				ledtestpwm();//与LED的pwm配置一起使用，呼吸灯
			}
			
			if(index)
			{
				printf("|     Temp: %d C         |\r\n",temp);
				printf("|     Humi: %d %%         |\r\n",humi);
				printf("|     light: %d        |\r\n",light);
				printf("|     voltage: %d      |\r\n",voltage);
			}
			index = 0;
			
		}
		
		if(Stat == 1)
		{
			if(!index)
			{
				OLed_Fill(0x00);// 将整个 OLED 屏幕填充为空白
				printf("可输入以下指令\r\n");
				printf("|       1.TurnOnLed(LED1)        |\r\n");
				printf("|       2.TurnOffLed(LED1)       |\r\n");
				printf("|       3.Beep_Pwm()             |\r\n");
				printf("|       4.TurnOff_Beep()         |\r\n");
				printf("|       5.DMA()                  |\r\n");
			}
			index = 1;
			delay_ms(100);   // 延迟以确保清空操作生效
			TIM_Cmd(TIM1, DISABLE);
			delay_ms(100);
			SSD1306_DrawBMP(0,0,128,8,paint);
			
		}
		
	}
}






