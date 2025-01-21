

#include "user.h"

//PB2 - CS
//PB3 - CLK
//PB4 - MISO
//PB5 - MOSI GPIO ����ģʽ

//1 SPI�豸�ӿڳ�ʼ������
void SPI1_Init()
{
//1��ʱ������ - SPI��·��·
	// 84mhz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//GPIO ��·Ҳ��������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//2 gpio ����
	//ͨ����д�ṹ��ķ�ʽ ������üĴ���������
	GPIO_InitTypeDef spistruct;
	//led�� ��������  ����
	spistruct.GPIO_Pin = GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5 ;	
	//��������ģʽ - ���� ��� ģ��ģʽ ����ģʽ
	spistruct.GPIO_Mode = GPIO_Mode_AF;
	//�������  ����ģʽ�� 0 1 ��  ��©��0 - ����̬��-�ߵ�ƽ���ⲿ��������
	//00 ����ģʽ;;; 
	spistruct.GPIO_OType = GPIO_OType_PP;
	//�������� - ����Ĭ�ϵ�ƽ
	spistruct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	spistruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&spistruct);
	
	//3 ����ָ�� io�ڸ��ó���ʲô��·����
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	
	//4. ����SPI��·
	SPI_InitTypeDef spiaaatruct;
	//ȫ˫�� - 
	spiaaatruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//stm32 - ��������
	spiaaatruct.SPI_Mode = SPI_Mode_Master;
	//���ݴ��� һ��8λ
	spiaaatruct.SPI_DataSize = SPI_DataSize_8b;
	//ʱ�Ӽ��� + ʱ����λ
	//���е�ƽ�͵�ƽ ����λ�� ��һ������
	spiaaatruct.SPI_CPOL = SPI_CPOL_Low;
	spiaaatruct.SPI_CPHA = SPI_CPHA_1Edge;
	//�������� - �ȴ������ݵĸ�λ
	spiaaatruct.SPI_FirstBit = SPI_FirstBit_MSB;
	//���Ƭѡ
	spiaaatruct.SPI_NSS = SPI_NSS_Soft;
	//���������� - 2��֮һ 42mmhz
	spiaaatruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	//����У�� - ��֤���ݴ����׼ȷ��
	 /* Initialize the SPI_CRCPolynomial member */
	spiaaatruct.SPI_CRCPolynomial = 7;
	//SPI��·�ĳ�ʼ��
	SPI_Init(SPI1,&spiaaatruct);

	//SPIʹ��
	SPI_Cmd(SPI1,ENABLE);
	
	
	
}




//2 SPI�豸��д���� - ��· - ��λ�Ĵ���
//������Ҫд������
//�����Ƕ�������
u8 SPI1_ReadWriteByte(u8 data)
{
	//�������ݼĴ���
	//�������� flag = 1 ��û������ flag = 0��
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)== RESET);  
		SPI_I2S_SendData(SPI1,data);
	
	//�������ݼĴ���
	//�������� flag =1 ��û������ flag = 0 ��
	//
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
		return SPI_I2S_ReceiveData(SPI1);
}


