

#include "user.h"

//at24c04 �洢�豸
//�ײ�����iic�ӿ�
#define AT24C02_WRITE_ADDR 0xA0 //1010 0000 
#define AT24C02_READ_ADDR 0xA1 //1010 0001 

//1.�豸��ʼ��
//����豸�Ƿ����
//���� 0 �����豸����
//���� 1 �����豸������
u8 AT24C02_INIT()
{
	//iic�ӿڳ�ʼ��
	iic_init();
	//��ʼ�ź�
	iic_start();
	//�����豸��ַ
	iic_send_byte_data(AT24C02_WRITE_ADDR);
	//��ȡack
	if(iic_getack())
	{
		iic_stop();
		return 1 ;
	}
	else
		return 0;
}

//2. ���д
//����Ҫ��
//1 �豸��ַ
//2 �ֽڵ�ַ
//3 ���ݱ���//һ���ֽڵ�����
u8 AT24C02_WRITE_BYTE(u8 wordaddr,u8 data)
{
	//1.��ʼ�ź�
	iic_start();
	//2.�����豸��ַ + w
	iic_send_byte_data(AT24C02_WRITE_ADDR);
	//3.��ȡack�ź� - 0 
	if(iic_getack())
	{
		iic_stop();
		return 1 ;
	}
	//4.�����ֽڵ�ַ
	iic_send_byte_data(wordaddr);
	//5.��ȡack�ź�
	if(iic_getack())
	{
		iic_stop();
		return 1 ;
	}
	//6.�������ݱ���
	iic_send_byte_data(data);
	//7.��ȡack�ź�
	if(iic_getack())
	{
		iic_stop();
		return 1 ;
	}
	//8.ֹͣ�ź�
	iic_stop();
	return 0;
}
//3. �����
//��ȡ�ɹ����� 0
//��ȡʧ�� ���� 1
//������������ô��
unsigned char AT24C02_READ_BYTE(unsigned char word_addr,char * readbuf)
{
	u8 res = 0 ;
	//1 ��ʼ�ź�
	iic_start();
	//2.�����豸��ַ - д��ַ ����
	iic_send_byte_data(AT24C02_WRITE_ADDR);
	//3.��ȡack�ź�
	if(iic_getack())
	{
		iic_stop();
		return 1 ;
	}
	//4 �����ֽڵ�ַ 
	iic_send_byte_data(word_addr);
	if(iic_getack())
	{
		iic_stop();
		return 1 ;
	}
	
	//5 ��ʼ�ź�
	iic_start();
	//6 �����豸��ַ
	iic_send_byte_data(AT24C02_READ_ADDR);
	if(iic_getack())
	{
		iic_stop();
		return 1 ;
	}
	
	//7.��ȡ�Է�������
	*readbuf = iic_get_byte_data();
	
	//5.���� NACK�ź�
	iic_send_ack(NACK);
	//6.ֹͣ�ź�
	iic_stop();

	return 0;
}





















