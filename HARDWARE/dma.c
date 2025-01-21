
#include "user.h"



u8 sendbuf[SEND_BUFF_SIZE];
//1 ���ڴ���������������ݵ������� ʹ��DMA����

//1 ������
//2 ͨ�� 4��ͨ�� 2�������� 2�ŵ�·
//3 ����ĵ�ַ
//4 Դͷ��ַ
//5 ���ݴ�С
void MYDMA_CONFIG(DMA_Stream_TypeDef *DMA_Stream,u32 channel,u32 des,u32 sedbuf,u16 size)
{
	//1 ����2��dma��·
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	//2 ����dma��· ˢ��2����
	DMA_DeInit(DMA_Stream);
	//3 �ȴ�dma��״̬���õ�ʱ�������������
	//flag Ϊ 1 ��ʱ�������������
	while(DMA_GetCmdStatus(DMA_Stream) != DISABLE){}
	//4 ����DMA���в���
	DMA_InitTypeDef dmastruct;
	//4��ͨ��
	dmastruct.DMA_Channel = DMA_Channel_4;
	//�����ַ
	dmastruct.DMA_PeripheralBaseAddr = des;
	//���ݴ�����
	dmastruct.DMA_Memory0BaseAddr = sedbuf;
	//���ݴ���ģʽ
	dmastruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	//���ݴ���Ĵ�С
  dmastruct.DMA_BufferSize = size;
	//���������ģʽ
	dmastruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//�洢������ģʽ
	dmastruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//�ⲿ�豸�����ݳ���
	dmastruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	//�洢�������ݳ���
	dmastruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	//����ģʽ ����ģʽ
	dmastruct.DMA_Mode = DMA_Mode_Normal;
	//�е����ȼ�
	dmastruct.DMA_Priority = DMA_Priority_Medium;
	//�����ȳ���ģʽ
	dmastruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dmastruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	//�洢��ͻ�����δ���
	dmastruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	//�ⲿ�豸ͻ�����δ���
	dmastruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	
	DMA_Init(DMA_Stream,&dmastruct);
}

//DMA�������亯��
void DMA_ENABLE(DMA_Stream_TypeDef *DMA_Stream,u16 size)
{
	//1 �رմ���
	DMA_Cmd(DMA_Stream,DISABLE);
	
	//2 ȷ��״̬Ϊ���Ա�����
	while(DMA_GetCmdStatus(DMA_Stream) != DISABLE){}
	
	//3 ���ݴ���������
	DMA_SetCurrDataCounter(DMA_Stream,size);
	//4 ����DMA����
	DMA_Cmd(DMA_Stream,ENABLE);
	
	
	
	
}





























