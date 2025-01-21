
#include "user.h"

//1 iic��·�����ú���
// //PB6  ʱ�� SCKL
//pb7 :  ����  SDA
void iic_init()
{

	//1 ʱ���������ú�
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//2 �ӿ��������ú�
	GPIO_InitTypeDef iicstruct;
	//��������
	iicstruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	//��Ҫ���
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	//��������� ��©
	iicstruct.GPIO_OType = GPIO_OType_OD;
	//оƬ�ڲ� ����������������
	//оƬ�ⲿ�Ѿ�������������
	iicstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//��Ӧ�ٶ�
	iicstruct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOB,&iicstruct);
	//3 ��ʼ�� - �������� �ߵ�ƽ
//	GPIO_WriteBit(GPIOB,GPIO_Pin_7,Bit_SET);
//	//��Ч��ƽ - ʱ����λ�͵�ƽ��ʱ�� �������ϵ����� ���ᱻ�ɼ�
//	GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_RESET);
}

//2 ��ʼ�ź�
void iic_start()
{
	//1 ʱ����Ϊ�ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	
	//2.����������
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//3 ���豸�ӵ�����ź��Ժ�ͻ���Ϊ  ���俪ʼ
	// ��������֮ǰ����ʱ���� ���ɵ͵�ƽ  �������ϵ����� ��Ч
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}


//3 ��ֹ�ź�
void iic_stop()
{	
	//1 �������ǵ͵�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	
	//2.ʱ���߸ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	//3 ������  �����ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//4 end�Ժ� ˫�ߣ������źš�
}

//4.iicЭ�鷢��һ���ֽڡ�
void iic_send_byte_data(unsigned char data)
{
	//1.����һλ�ķ��� ѭ��8��
	unsigned char i = 0 ; 
	for(i = 0 ; i < 8 ; i++)
	{
		//ʱ����Ϊ�͵�ƽ  �������ϵ����ݿ��Ա仯
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		//����λ��
		//�ȴ����λ - ��ʱ��Ҫ�� ������
		if((data >> (7 - i))& 0x01)  //Ҫ���͵��������λ��1 �ͷ��͸ߵ�ƽ
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
		else			//����ͷ��͵͵�ƽ
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		//ʱ���߱�ɸߵ�ƽ �����߾ͻᱻʶ��
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
	}
	
	//2 ȫ�����֮��  ʱ����Ϊ�͵�ƽ ��Чʱ�ӵ�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
}
//5 �ھŸ�ʱ������ ���豸 ϣ���������߶��� �͵�ƽ  = ACK ;
//������ֵ 0
//������ֵ 1
u8 iic_getack()
{
	//1.ʱ����Ϊ�͵�ƽ - ���������ݿ��Ա仯 - ��Чʱ��
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	
	//2 Ŀ���Ǵ������߶�����ƽ  �ȸ��ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(1);
	
	//3.ʱ����Ϊ�͵�ƽ �������ϵ����� ��Ч��ƽ
	//ʱ����Ϊ�ߵ�ƽ  �������ϵ������ǿ����εġ�
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	
	//4 ���������ϵ�����
	if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
	{
		//������ʼִ�е�ʱ��  ʱ���� �͵�ƽ 
		//��������������ʱ��  ʱ���߻��ǵ͵�ƽ
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		//����0��������ĵ�ƽ�� �͵�ƽ
		return 0;
	}
	else
		//����1��������ĵ�ƽ��ƽ�Ǹߵ�ƽ
		return 1;
}

//6.���淢�����ݡ�����д��cpu�Ĵ��롣
//������
u8 iic_get_byte_data()
{
	u8 resdata = 0 ; 
    // 1000 0000 	
	//1�ӷ������ݹ��� һ���ֽ�
	//ʱ��������
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	
#if 1
	//2.����������
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(1);
#endif
	
	//3.��һ���ֽ� ѭ��8�ζ�λ���ݹ���
	char i = 0 ; 
	for(i = 0 ; i < 8;i++)
	{
		//������ƶ�һλ
		//Ϊʲô�����ƶ�����������ƶ�
		resdata <<= 1;
		//iic�����ݵ�ԭ���� ʱ����Ϊ�ߵ�ƽ�Ŷ�
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		
		//�жϵ�ƽ�ķ�ʽ
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
			resdata |=  0x01;  //��1
		else
			resdata &= 0xfe;   //��0
		delay_us(1);
		//ʱ��������
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
	}
	//���� ���ɹ�������
	return resdata;
}

//7 ����һ������λ��ȥ
u8 iic_send_ack(unsigned char ack)
{
	//1 ʱ����Ϊ�͵�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	//2.�ж�Ҫ���͵ĵ�ƽ�� �ߵ�
	if(ack == NACK)
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
	else
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	//3. ������ ��ʱ�������� ����ͻ�������ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	
	//4.����������ʱ�� ����һ��
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
}
