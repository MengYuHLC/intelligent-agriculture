

#include "user.h"



//1 光敏电阻
//2 模拟电压
//3 气体传感器
//4 酒精传感器
//5 人体红外传感器

//1 adc 的配置 - PA0
void ADC1_LIGHT_SENSOR_Config()
{
	//1 时钟配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//2 GPIOA组使能
	GPIO_InitTypeDef lightstruct;
	lightstruct.GPIO_Pin = GPIO_Pin_0;
	//模拟模式
	lightstruct.GPIO_Mode = GPIO_Mode_AN;
	lightstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	lightstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&lightstruct);
	
	//3 ADC1参数配置
	ADC_CommonInitTypeDef adc1struct;
	//独立模式
	adc1struct.ADC_Mode = ADC_Mode_Independent;
	//间隔时间 第一次采集完成后 等待时间
	adc1struct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	//DMA功能 采集完后，直接把数据从记过寄存器中拷贝出来放到缓冲区中
	adc1struct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//adc的采样频率不能超过36mhz
	//adc电路 apb2 = 84 /4 = 21mhz;
	adc1struct.ADC_Prescaler = ADC_Prescaler_Div4;
	
	ADC_CommonInit(&adc1struct);
	
	//4 ADC2参数配置
	ADC_InitTypeDef adc2struct;
	//是否扫描
	adc2struct.ADC_ScanConvMode = DISABLE;
	//采集精度
	adc2struct.ADC_Resolution = ADC_Resolution_12b;
	//连续转换 - 一次一结束
	adc2struct.ADC_ContinuousConvMode = DISABLE;
	//触发检测 - 软件触发
	adc2struct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//采集完的数据 存储到16位的寄存器当中并且 右对齐
	adc2struct.ADC_DataAlign = ADC_DataAlign_Right;
	//规则组 while还是注入组 interupt
	adc2struct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&adc2struct);
	
	ADC_Cmd(ADC1,ENABLE);
	
}

//2 开始采集函数
u16 ADC1_get_light_value()
{
	//1. 设置规则通道组
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);
	//2. 开始采集的开关
	ADC_SoftwareStartConv(ADC1);
	//3. 采样时间到 flag =1；没有采集完成，flag =0;
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	//4.转换完成
	return ADC_GetConversionValue(ADC1);

}

//3 取平均值函数
u16 ADC1_get_light_Average_value()
{
	//累计五次取平均数值
	u16 average =0,light_sum=0;
	u16 times = 5;
	for(int i=0;i<times;i++)
	{
		light_sum += ADC1_get_light_value();
	}
	
	return average = light_sum/times;
	
}


// 判断是否接收到光敏电阻数据
u8 Check_LightSensor_Data() {
    uint16_t lightValue = ADC1_get_light_Average_value();

    if (lightValue >= 0 && lightValue <= 4095) 
		{
			return 0;//接收到数据返回0
    } else 
		{
       return 1;
    }
}

//电压传感器 PC0
void ADC1_voltage_SENSOR_Config()
{
	//1 时钟配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//2 GPIOA组使能
	GPIO_InitTypeDef voltagestruct;
	voltagestruct.GPIO_Pin = GPIO_Pin_0;
	//模拟模式
	voltagestruct.GPIO_Mode = GPIO_Mode_AN;
	voltagestruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	voltagestruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOC,&voltagestruct);
	
	//3 ADC1参数配置
	ADC_CommonInitTypeDef adc1struct;
	//独立模式
	adc1struct.ADC_Mode = ADC_Mode_Independent;
	//间隔时间 第一次采集完成后 等待时间
	adc1struct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	//DMA功能 采集完后，直接把数据从记过寄存器中拷贝出来放到缓冲区中
	adc1struct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//adc的采样频率不能超过36mhz
	//adc电路 apb2 = 84 /4 = 21mhz;
	adc1struct.ADC_Prescaler = ADC_Prescaler_Div4;
	
	ADC_CommonInit(&adc1struct);
	
	//4 ADC2参数配置
	ADC_InitTypeDef adc2struct;
	//是否扫描
	adc2struct.ADC_ScanConvMode = DISABLE;
	//采集精度
	adc2struct.ADC_Resolution = ADC_Resolution_12b;
	//连续转换 - 一次一结束
	adc2struct.ADC_ContinuousConvMode = DISABLE;
	//触发检测 - 软件触发
	adc2struct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//采集完的数据 存储到16位的寄存器当中并且 右对齐
	adc2struct.ADC_DataAlign = ADC_DataAlign_Right;
	//规则组 while还是注入组 interupt
	adc2struct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&adc2struct);
	
	ADC_Cmd(ADC1,ENABLE);
	
}

//2 开始采集函数
u16 ADC1_get_voltage_value()
{
	//1. 设置规则通道组
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);
	//2. 开始采集的开关
	ADC_SoftwareStartConv(ADC1);
	//3. 采样时间到 flag =1；没有采集完成，flag =0;
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	//4.转换完成
	return ADC_GetConversionValue(ADC1);

}

//3 取平均值函数
u16 ADC1_get_voltage_Average_value()
{
	//累计五次取平均数值
	u16 average =0,light_sum=0;
	u16 times = 5;
	for(int i=0;i<times;i++)
	{
		light_sum += ADC1_get_light_value();
	}
	
	return average = light_sum/times;
	
}


// 判断是否接收到光敏电阻数据
u8 Check_VoltageSensor_Data() 
{
    uint16_t VoltageValue = ADC1_get_voltage_Average_value();

    if (VoltageValue >= 0 && VoltageValue <= 4095) 
		{
			return 0;//接收到数据返回0
    } else 
		{
       return 1;
    }
}