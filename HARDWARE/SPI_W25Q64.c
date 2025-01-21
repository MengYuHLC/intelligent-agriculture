
#include "user.h"


//����ָ����ֵ
#define W25X_ManufactDeviceID	0x90 
//����Ƭѡ����
#define W25X_ChipErase			0x60   //����h������
//��״̬�Ĵ���
#define W25X_ReadStatusReg		0x05
//������
#define W25X_ReadData			0x03
//дʹ��
#define W25X_WriteEnable		0x06
//д��ʹ��
#define W25X_WriteDisable		0x04 
//ҳ��� ����д����
#define W25X_PageProgram		0x02
//�����
#define W25X_BlockErase			0xD8 
//��������  
#define W25X_SectorErase		0x20



//1 �豸��ʼ��
void w25q64_init()
{
	//1 pb2���е�����ʼ��
	//����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef w25struct;
	w25struct.GPIO_Pin = GPIO_Pin_2;
	w25struct.GPIO_Mode = GPIO_Mode_OUT;
	w25struct.GPIO_OType = GPIO_OType_PP;
	w25struct.GPIO_PuPd = GPIO_PuPd_UP;
	w25struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&w25struct);
	//Ƭѡ�͵�ƽ��Ч - ���ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	
	//2 һ����� �ر�lora
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_InitTypeDef LORAstruct;
	LORAstruct.GPIO_Pin = GPIO_Pin_1;
	LORAstruct.GPIO_Mode = GPIO_Mode_OUT;
	LORAstruct.GPIO_OType = GPIO_OType_PP;
	LORAstruct.GPIO_PuPd = GPIO_PuPd_UP;
	LORAstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&LORAstruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
	
	
}

//2.����оƬ��id
u16 w25q64_readid()
{
	u16 id = 0 ;
	//1 Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	
	//2 ����ָ��
	SPI1_ReadWriteByte(W25X_ManufactDeviceID);
	SPI1_ReadWriteByte(0x00);
	SPI1_ReadWriteByte(0x00);
	SPI1_ReadWriteByte(0x00);
	
	//3.����4���ֽ�
	id |= SPI1_ReadWriteByte(0x00);
	id <<= 8 ;
	id |= SPI1_ReadWriteByte(0x00);
	
	//4.ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	return id;
}

//3 дʹ��
void write_enable()
{
	//1 Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//2 ����ָ��
	SPI1_ReadWriteByte(W25X_WriteEnable);
	//3 ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	
}

//4 ����Ƿ�д�� checkbusy
u8 w25q64_check_busy()
{
	//���stat = 1  �Ǿ���æ ��ûִ��������Ķ���
	u8 stat = 0;
	do{
			//1 Ƭѡ
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
			//2 ����ָ�� - Ҫ��ȡ�����״̬�Ĵ��� stm32 �洢��
			SPI1_ReadWriteByte(W25X_ReadStatusReg);
			//����00 ����״̬ ���stat = 1 
			stat = SPI1_ReadWriteByte(0x00);
			//3 ȡ��Ƭѡ
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
	}while(stat & 0x01);
	//���stat��1�Ǿͼ���ѭ��
	return 0;
}

//5 �������� -- ff
u8 w25q64_earse_chip_all()
{
	
	//����
	write_enable();
	w25q64_check_busy();
	//1 Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//2 ����ָ��
	
	SPI1_ReadWriteByte(W25X_ChipErase);
	
	//3 �ر�Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	
	//4 ���������Ǻܳ�ʱ��ġ�
	//����Ƿ�busy
	
	w25q64_check_busy();
	return 0;
	
	
	
}

//6 д����
//6,д����
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pbuffer:Ҫд�������ָ��
//writeaddr:��ʼд��ĵ�ַ 24bit
//numbyte������ֽ��� 256�ֽ�
void w25q64_write_page(unsigned char *pbuffer,unsigned int writeaddr,unsigned short int numbyte)
{
	unsigned int i = 0 ;
	//1.дʹ��
	write_enable();
	//2.Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//3.����дָ��
	SPI1_ReadWriteByte(W25X_PageProgram);
	//4.����24bit��ַ
	SPI1_ReadWriteByte((u8)((writeaddr) >> 16));
	SPI1_ReadWriteByte((u8)((writeaddr) >> 8));
	SPI1_ReadWriteByte((u8)(writeaddr));
	//5.ѭ��д����
	for(i=0;i<numbyte;i++)SPI1_ReadWriteByte(pbuffer[i]);
	//6.ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//7.�ȴ�д��
	w25q64_check_busy();	
}
//8 ������
//��ַ + �ռ� + ���ȡ�
unsigned int w25q64_read_data(uint32_t addr,uint8_t buff[],uint8_t len)
{
			//1.Ƭѡ
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	
			//2.���Ͷ�����ָ��
			SPI1_ReadWriteByte(W25X_ReadData);  //һ������ 4���ֽڡ�24���ֽ���Ѱַ���еĿռ���8M
			//������ŵ��ǵ�ַ  //ȡ����С���֡�
			SPI1_ReadWriteByte((addr >> 16) & 0xff); 
			SPI1_ReadWriteByte((addr >> 8) & 0xff);
			SPI1_ReadWriteByte((addr) & 0xff);
	
			//3.��������
			uint8_t i = 0 ;
			for(i = 0 ; i < len ; i++)
			{
					//��Ҳ���������������
					buff[i] = SPI1_ReadWriteByte(0);
				
			}
			//4.ȡ��Ƭѡ
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			//�ȴ�������
			w25q64_check_busy();
			//����ʵ�ʶ������ֽ���
			return i ;
}

