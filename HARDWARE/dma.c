
#include "user.h"



u8 sendbuf[SEND_BUFF_SIZE];
//1 从内存中输出大量的数据到串口中 使用DMA功能

//1 数据流
//2 通道 4号通道 2号数据流 2号电路
//3 外设的地址
//4 源头地址
//5 数据大小
void MYDMA_CONFIG(DMA_Stream_TypeDef *DMA_Stream,u32 channel,u32 des,u32 sedbuf,u16 size)
{
	//1 配置2号dma电路
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	//2 重启dma电路 刷新2号流
	DMA_DeInit(DMA_Stream);
	//3 等待dma流状态可用的时候才能重新配置
	//flag 为 1 的时候才能向下运行
	while(DMA_GetCmdStatus(DMA_Stream) != DISABLE){}
	//4 配置DMA所有参数
	DMA_InitTypeDef dmastruct;
	//4号通道
	dmastruct.DMA_Channel = DMA_Channel_4;
	//外设地址
	dmastruct.DMA_PeripheralBaseAddr = des;
	//数据次哪来
	dmastruct.DMA_Memory0BaseAddr = sedbuf;
	//数据传输模式
	dmastruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	//数据传输的大小
  dmastruct.DMA_BufferSize = size;
	//外设非增量模式
	dmastruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//存储器增量模式
	dmastruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//外部设备的数据长度
	dmastruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	//存储器的数据长度
	dmastruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	//传输模式 单词模式
	dmastruct.DMA_Mode = DMA_Mode_Normal;
	//中等优先级
	dmastruct.DMA_Priority = DMA_Priority_Medium;
	//先入先出的模式
	dmastruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dmastruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	//存储器突发单次传输
	dmastruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	//外部设备突发单次传输
	dmastruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	
	DMA_Init(DMA_Stream,&dmastruct);
}

//DMA开启传输函数
void DMA_ENABLE(DMA_Stream_TypeDef *DMA_Stream,u16 size)
{
	//1 关闭传输
	DMA_Cmd(DMA_Stream,DISABLE);
	
	//2 确保状态为可以被设置
	while(DMA_GetCmdStatus(DMA_Stream) != DISABLE){}
	
	//3 数据传输量控制
	DMA_SetCurrDataCounter(DMA_Stream,size);
	//4 开启DMA传输
	DMA_Cmd(DMA_Stream,ENABLE);
	
	
	
	
}





























