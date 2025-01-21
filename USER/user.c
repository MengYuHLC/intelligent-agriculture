
#include "user.h"

extern int Stat;
extern char wendu[2];//�洢�¶ȣ�wendu[0]��������wendu[1]����С��
extern char shidu[2];//�洢ʪ��
extern u8 sendbuf[SEND_BUFF_SIZE];//DMAʹ��
#define READ_DHT11_OK 0
#define READ_DHT11_NOT_OK 1
#define READ_ADC_LIGHT_OK 0
#define READ_ADC_LIGHT_NOT_OK 1
#define humidity 40//ʪ����ֵ���������ֵ�򴥷�����Ķ���
u8 temp;
u8 humi;
int main()
{
	delay_init(168);//��ʼ���ں�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�������ȼ�����
	Config_Led();//��ʼ��LED
	Config_Beep();//��ʼ��BEEP
	Config_Key();//��ʼ��KEY
	my_usart1_config();//��ʼ������1 ����ñ��������������ʹ�ô��ڵ������ֽ�����Ϣ����
	iic_init();//��ʼ��i2c
	InitOLed();//��ʼ��oled
	TIM1_PWM_CH1_LED_CONFIG();//��ʼ��LED����pwm	
	ADC1_LIGHT_SENSOR_Config();//adc ������
	TIM2_PWM_CH3_BEEP_CONFIG();//��ʱ��2��ͨ��3����������
	INTERRUPT_KEY2_INIT();//��ʼ���ж���,ʹ���жϽ���ģʽ���л��������������л�ģʽ


char tempStr[16]; // �洢�¶��ַ���
char humiStr[16]; // �洢ʪ���ַ���
char errorStr[16] = "error:no data";
char lightStr[16];
char voltageStr[16];

TIM_Cmd(TIM1, ENABLE);
TurnOff_Led(LED3);//Ĭ��Ϊ����һ����״̬	                                                  
int index = 1;
	while(1)
	{
		if(Stat == 0)
		{
			if(index)
			{
				OLed_Fill(0x00);
			}
			DHT11_Config();//��ʼ��DHT11�ʹ���1һ��ʹ��
			TIM_Cmd(TIM1, ENABLE);

			
			DHT11_ReadData(&temp,&humi);	//��ʪ�ȴ�����
			sprintf(wendu,"%d",temp);
			sprintf(shidu,"%d",humi);	
			sprintf(tempStr, "Temp: %d C", temp);// ��ʽ���¶Ⱥ�ʪ��Ϊ�ַ���
			sprintf(humiStr, "Humi: %d %%", humi);

			
			OLED_ShowString(0, 0, tempStr); // �ڵ� 1 ����ʾ�¶�
			OLED_ShowString(0, 2, humiStr); // �ڵ� 2 ����ʾʪ��

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
				ledtestpwm();//��LED��pwm����һ��ʹ�ã�������
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
				OLed_Fill(0x00);// ������ OLED ��Ļ���Ϊ�հ�
				printf("����������ָ��\r\n");
				printf("|       1.TurnOnLed(LED1)        |\r\n");
				printf("|       2.TurnOffLed(LED1)       |\r\n");
				printf("|       3.Beep_Pwm()             |\r\n");
				printf("|       4.TurnOff_Beep()         |\r\n");
				printf("|       5.DMA()                  |\r\n");
			}
			index = 1;
			delay_ms(100);   // �ӳ���ȷ����ղ�����Ч
			TIM_Cmd(TIM1, DISABLE);
			delay_ms(100);
			SSD1306_DrawBMP(0,0,128,8,paint);
			
		}
		
	}
}






