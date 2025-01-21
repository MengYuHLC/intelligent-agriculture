

#include "user.h"


//DHT11�豸
//PA3����

void DHT11_Config()
{
	//ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//���ų�ʼ��
	GPIO_InitTypeDef dht11struct;
	//PA3
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	//���ģʽ
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	//��©
	dht11struct.GPIO_OType = GPIO_OType_OD;
	//����
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//�ٶ�
	dht11struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&dht11struct);
	
	//����ߵ�ƽ
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	
	
	
}

//���ģʽ����
void DHT11_OUTMODE()
{
	//ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//���ų�ʼ��
	GPIO_InitTypeDef dht11struct;
	//PA3
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	//���ģʽ
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	//��©
	dht11struct.GPIO_OType = GPIO_OType_OD;
	//����
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//�ٶ�
	dht11struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&dht11struct);
	
	//����ߵ�ƽ
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	
}

//����ģʽ����
void DHT11_INMODE()
{
	//ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//���ų�ʼ��
	GPIO_InitTypeDef dht11struct;
	//PA3
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	//����ģʽ
	dht11struct.GPIO_Mode = GPIO_Mode_IN;
	//����
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//�ٶ�
	dht11struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&dht11struct);
	
	
}

//DHT11�����ݺ���
char buff[5] = "";
u8 DHT11_ReadDataByte();
char wendu[2] = "";
char shidu[2] = "";
//����0����������ݣ�����1����ʧ��
u8 DHT11_ReadData(u8 *temp,u8 *humi)
{
	
	//���ģʽ
	DHT11_OUTMODE();
	
	//1.�͵�ƽ20ms+�ߵ�ƽ30us
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(20);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_us(30);
	
	//�������� - �ȴ��ߵ�ƽ  ?
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	
	//2����ģʽ
	DHT11_INMODE();
	
	//�ȴ��͵�ƽ����
	//�������ĵ͵�ƽ Ҳ�������豸�����ĵ͵�ƽ
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	//�ȴ��ߵ�ƽ����
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	
	//�������� - 40bit
	char i = 0;
	//5���ֽ� 
	for(i = 0 ; i<5 ; i++)
	{
		buff[i] = DHT11_ReadDataByte();
	}
	
	DHT11_OUTMODE();
	
	//У��
	if(buff[4] ==  buff[0] + buff[1] + buff[2] + buff[3])
	{
		//У��ͨ��
		shidu[0] = buff[0];
		shidu[1] = buff[1];
		
		wendu[0] = buff[2];
		wendu[1] = buff[3];
		*humi=buff[0];
		*temp=buff[2];
		return 0;
	}
	else
		return 1;
	
}

//DHT11��λ����
u8 DHT11_ReadDataByte()
{
	u8 readbit = 0;
	DHT11_INMODE();
	
	//ѭ����8��
	char i = 0;
	for(i = 0; i< 8 ; i++)
	{
		readbit = readbit << 1;
		//�������� - �ȴ��ߵ�ƽ
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		
		//�͵�ƽ���� - ����Ҫ�͵�ƽ
		while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		
		//�жϸߵ�ƽʱ��
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
			delay_us(30);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
			readbit |= 0x01;
		else
			readbit &= 0xfe;

	}
	DHT11_OUTMODE();
	return readbit;
	
}






