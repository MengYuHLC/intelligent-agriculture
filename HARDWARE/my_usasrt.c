

#include "user.h"
extern u8 sendbuf[SEND_BUFF_SIZE];//DMA使用
//重定义fputc函数 
int fputc(int ch, FILE *f)
{     
        while((USART1->SR&0X40)==0);//循环发送，直到发送完毕
        USART1->DR = (u8) ch;      
        return ch;
	

}
// 重定向fgetc，用于scanf的输入
int fgetc(FILE *f)
{
    while((USART1->SR & USART_SR_RXNE) == 0);  // 等待直到接收到数据
    return USART1->DR;  // 从数据寄存器读取字符
}
//1 6个串口配置方法一样，只有引脚不一样
//配置串口一
void my_usart1_config()
{
	//1 时钟问题
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2 GPIOA 9 10 接口
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//配置GPIOA相关参数
	GPIO_InitTypeDef gpio_uart_struct;
	gpio_uart_struct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	//3 复用模式
	gpio_uart_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_struct.GPIO_OType = GPIO_OType_PP;
	gpio_uart_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_uart_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&gpio_uart_struct);
	//4 GPIOA组 9 10 复用成串口功能
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//5 串口初始化
	USART_InitTypeDef usart1struct;
	//波特率
	usart1struct.USART_BaudRate = 115200;
	//不需要硬件配置
	usart1struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//输入输出
	usart1struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//不用校验
	usart1struct.USART_Parity = USART_Parity_No;
	//1位停止位
	usart1struct.USART_StopBits = USART_StopBits_1;
	//数据位
	usart1struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&usart1struct);
	//6 中断控制的配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannel = USART1_IRQn;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
	//7 cmd打开
	USART_Cmd(USART1,ENABLE);
	//中断使能函数
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	
}
//串口中断函数

char res[32] = "";
char i = 0;
int flag = 0;         
int exitFlag = 0; // 定义一个全局或局部标志变量
void USART1_IRQHandler()
{

//	u16 res = USART_ReceiveData(USART1);
//	
//	if(res == 1)
//	{
//		TurnOn_Led(LED1);
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	}
//	if(res == 's')
//	{
//		TurnOff_Led(LED1);
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	}
//	
//	if(USART_GetITStatus(USART1,USART_IT_RXNE))
//	{
//		res[i] = USART_ReceiveData(USART1);
//		i++;
//		if(i > 16)
//			i = 0;
//		delay_us(50);
//		if(!strncmp(res,"1",sizeof("1")-1))
//		{
//			printf("res:%s\n",res);
//			
//			delay_ms(10);
//			if(!strncmp(res,"openled1",sizeof("openled1")))
//			{
//				TurnOn_Led(LED1);
//				i = 0;
//				memset(res,0,sizeof(res));
//				
//				delay_us(10);
//				USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//			}
//			else
//			{
//				printf("res:%s\n",res);
//			}
//			
//		}
//		
//	}
//	if(!strncmp(res,"openled1",sizeof("openled1")))
//	{
//		TurnOn_Led(LED1);
//		i = 0;
//		memset(res,0,sizeof(res));
//		
//		delay_us(10);
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	}
//	if(!strncmp(res,"closeled1",sizeof("closeled1")))
//	{
//		TurnOff_Led(LED1);
//		i = 0;
//		memset(res,0,sizeof(res));
//		
//		delay_us(10);
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	}	
		
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		res[i] = USART_ReceiveData(USART1);
		i++;
		if(i > 16)
			i = 0;
		delay_us(50);
		
		if(!strncmp(res,"1",sizeof("1")))
		{
			TurnOn_Led(LED1);
			i = 0;
			memset(res,0,sizeof(res));
			delay_ms(10);		
		}
	  if(!strncmp(res,"2",sizeof("2")))
		{
			TurnOff_Led(LED1);
			i = 0;
			memset(res,0,sizeof(res));
			delay_us(10);
			
		}

		if(!strncmp(res,"3",sizeof("3")))
		{
			TIM_Cmd(TIM2,ENABLE); 
			BEEP_PWM_DRIVER();
			i = 0;
			memset(res,0,sizeof(res));
			delay_us(10);
			
		}
		if(!strncmp(res,"4",sizeof("4")))
		{
			
			TIM_Cmd(TIM2,DISABLE);
			i = 0;
			memset(res,0,sizeof(res));
			delay_us(10);
			
		}
		if (!strncmp(res, "5", sizeof("5")))
		{
			
			i = 0;
			memset(res, 0, sizeof(res));
			delay_ms(10);
			printf("请输入一个字符串：\r\n");

			
			char dmaStr[128] = "";//用一个缓冲区来接收数据
			int index = 0;

			// 等待用户输入数据并存储到 dmaStr 中
			while (index < sizeof(dmaStr) - 1)  // 确保不会超出缓冲区
			{
					if (USART_GetITStatus(USART1, USART_IT_RXNE))  // 检查是否接收到数据
					{
							char received_char = USART_ReceiveData(USART1);  // 接收一个字符
							if (received_char == '\n' || received_char == '\r')  // 如果是换行符，结束输入,输入方式：hello world\n
							{
									break;
							}
							dmaStr[index++] = received_char;  // 存储字符
					}
			}
			
			dmaStr[index] = '\0';  // 字符串结束符
			printf("接收到字符串：%s\r\n", dmaStr);
			delay_ms(10);
			// DMA配置传输数据
			MYDMA_CONFIG(DMA2_Stream7, DMA_Channel_4, (u32)(&USART1->DR), (u32)sendbuf, SEND_BUFF_SIZE);

			for (int i = 0; i < sizeof(dmaStr); i++)
			{
					sendbuf[i] = dmaStr[i];  // 将输入的字符串数据拷贝到 sendbuf
			}

			printf("DMA开始传输\r\n");

			// 允许DMA传输
			USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
			// 进行DMA传输
			DMA_ENABLE(DMA2_Stream7, SEND_BUFF_SIZE);
			delay_ms(500);

			// 等待DMA传输完成
			while (!DMA_GetFlagStatus(DMA2_Stream7, DMA_FLAG_TCIF7));

			DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);

			printf("DMA传输完成\r\n");
		}

		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		
	}	
	
	
	
	
	
	
	
}

//配置部分;
void uart2init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//1 串口时钟配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//2 D组时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	//3引脚功能配置
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	//4.GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//输出类型不要配置
	GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//5.//串口初始化
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	
	//6串口2使能
	USART_Cmd(USART2,ENABLE);
	//7串口中断使能
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	//8中断配置
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);		
}
//中断服务函数
void USART2_IRQHandler(void)
{
	unsigned char  res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{	
		res=USART_ReceiveData(USART2);
		switch(res)
		{
			//打开LED1
			case 1:TurnOn_Led(LED1);break;
			//关闭LED1
			case 2:TurnOff_Led(LED1);break;
			
		}
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}





