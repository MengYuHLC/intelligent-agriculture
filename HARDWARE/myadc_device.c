

#include "user.h"



//1 ��������
//2 ģ���ѹ
//3 ���崫����
//4 �ƾ�������
//5 ������⴫����

//1 adc ������ - PA0
void ADC1_LIGHT_SENSOR_Config()
{
	//1 ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//2 GPIOA��ʹ��
	GPIO_InitTypeDef lightstruct;
	lightstruct.GPIO_Pin = GPIO_Pin_0;
	//ģ��ģʽ
	lightstruct.GPIO_Mode = GPIO_Mode_AN;
	lightstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	lightstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&lightstruct);
	
	//3 ADC1��������
	ADC_CommonInitTypeDef adc1struct;
	//����ģʽ
	adc1struct.ADC_Mode = ADC_Mode_Independent;
	//���ʱ�� ��һ�βɼ���ɺ� �ȴ�ʱ��
	adc1struct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	//DMA���� �ɼ����ֱ�Ӱ����ݴӼǹ��Ĵ����п��������ŵ���������
	adc1struct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//adc�Ĳ���Ƶ�ʲ��ܳ���36mhz
	//adc��· apb2 = 84 /4 = 21mhz;
	adc1struct.ADC_Prescaler = ADC_Prescaler_Div4;
	
	ADC_CommonInit(&adc1struct);
	
	//4 ADC2��������
	ADC_InitTypeDef adc2struct;
	//�Ƿ�ɨ��
	adc2struct.ADC_ScanConvMode = DISABLE;
	//�ɼ�����
	adc2struct.ADC_Resolution = ADC_Resolution_12b;
	//����ת�� - һ��һ����
	adc2struct.ADC_ContinuousConvMode = DISABLE;
	//������� - �������
	adc2struct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//�ɼ�������� �洢��16λ�ļĴ������в��� �Ҷ���
	adc2struct.ADC_DataAlign = ADC_DataAlign_Right;
	//������ while����ע���� interupt
	adc2struct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&adc2struct);
	
	ADC_Cmd(ADC1,ENABLE);
	
}

//2 ��ʼ�ɼ�����
u16 ADC1_get_light_value()
{
	//1. ���ù���ͨ����
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);
	//2. ��ʼ�ɼ��Ŀ���
	ADC_SoftwareStartConv(ADC1);
	//3. ����ʱ�䵽 flag =1��û�вɼ���ɣ�flag =0;
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	//4.ת�����
	return ADC_GetConversionValue(ADC1);

}

//3 ȡƽ��ֵ����
u16 ADC1_get_light_Average_value()
{
	//�ۼ����ȡƽ����ֵ
	u16 average =0,light_sum=0;
	u16 times = 5;
	for(int i=0;i<times;i++)
	{
		light_sum += ADC1_get_light_value();
	}
	
	return average = light_sum/times;
	
}


// �ж��Ƿ���յ�������������
u8 Check_LightSensor_Data() {
    uint16_t lightValue = ADC1_get_light_Average_value();

    if (lightValue >= 0 && lightValue <= 4095) 
		{
			return 0;//���յ����ݷ���0
    } else 
		{
       return 1;
    }
}

//��ѹ������ PC0
void ADC1_voltage_SENSOR_Config()
{
	//1 ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//2 GPIOA��ʹ��
	GPIO_InitTypeDef voltagestruct;
	voltagestruct.GPIO_Pin = GPIO_Pin_0;
	//ģ��ģʽ
	voltagestruct.GPIO_Mode = GPIO_Mode_AN;
	voltagestruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	voltagestruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOC,&voltagestruct);
	
	//3 ADC1��������
	ADC_CommonInitTypeDef adc1struct;
	//����ģʽ
	adc1struct.ADC_Mode = ADC_Mode_Independent;
	//���ʱ�� ��һ�βɼ���ɺ� �ȴ�ʱ��
	adc1struct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	//DMA���� �ɼ����ֱ�Ӱ����ݴӼǹ��Ĵ����п��������ŵ���������
	adc1struct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//adc�Ĳ���Ƶ�ʲ��ܳ���36mhz
	//adc��· apb2 = 84 /4 = 21mhz;
	adc1struct.ADC_Prescaler = ADC_Prescaler_Div4;
	
	ADC_CommonInit(&adc1struct);
	
	//4 ADC2��������
	ADC_InitTypeDef adc2struct;
	//�Ƿ�ɨ��
	adc2struct.ADC_ScanConvMode = DISABLE;
	//�ɼ�����
	adc2struct.ADC_Resolution = ADC_Resolution_12b;
	//����ת�� - һ��һ����
	adc2struct.ADC_ContinuousConvMode = DISABLE;
	//������� - �������
	adc2struct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//�ɼ�������� �洢��16λ�ļĴ������в��� �Ҷ���
	adc2struct.ADC_DataAlign = ADC_DataAlign_Right;
	//������ while����ע���� interupt
	adc2struct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&adc2struct);
	
	ADC_Cmd(ADC1,ENABLE);
	
}

//2 ��ʼ�ɼ�����
u16 ADC1_get_voltage_value()
{
	//1. ���ù���ͨ����
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);
	//2. ��ʼ�ɼ��Ŀ���
	ADC_SoftwareStartConv(ADC1);
	//3. ����ʱ�䵽 flag =1��û�вɼ���ɣ�flag =0;
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	//4.ת�����
	return ADC_GetConversionValue(ADC1);

}

//3 ȡƽ��ֵ����
u16 ADC1_get_voltage_Average_value()
{
	//�ۼ����ȡƽ����ֵ
	u16 average =0,light_sum=0;
	u16 times = 5;
	for(int i=0;i<times;i++)
	{
		light_sum += ADC1_get_light_value();
	}
	
	return average = light_sum/times;
	
}


// �ж��Ƿ���յ�������������
u8 Check_VoltageSensor_Data() 
{
    uint16_t VoltageValue = ADC1_get_voltage_Average_value();

    if (VoltageValue >= 0 && VoltageValue <= 4095) 
		{
			return 0;//���յ����ݷ���0
    } else 
		{
       return 1;
    }
}