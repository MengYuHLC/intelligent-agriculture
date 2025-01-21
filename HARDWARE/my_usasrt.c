

#include "user.h"
extern u8 sendbuf[SEND_BUFF_SIZE];//DMAʹ��
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{     
        while((USART1->SR&0X40)==0);//ѭ�����ͣ�ֱ���������
        USART1->DR = (u8) ch;      
        return ch;
	

}
// �ض���fgetc������scanf������
int fgetc(FILE *f)
{
    while((USART1->SR & USART_SR_RXNE) == 0);  // �ȴ�ֱ�����յ�����
    return USART1->DR;  // �����ݼĴ�����ȡ�ַ�
}
//1 6���������÷���һ����ֻ�����Ų�һ��
//���ô���һ
void my_usart1_config()
{
	//1 ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2 GPIOA 9 10 �ӿ�
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//����GPIOA��ز���
	GPIO_InitTypeDef gpio_uart_struct;
	gpio_uart_struct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	//3 ����ģʽ
	gpio_uart_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_struct.GPIO_OType = GPIO_OType_PP;
	gpio_uart_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_uart_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&gpio_uart_struct);
	//4 GPIOA�� 9 10 ���óɴ��ڹ���
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//5 ���ڳ�ʼ��
	USART_InitTypeDef usart1struct;
	//������
	usart1struct.USART_BaudRate = 115200;
	//����ҪӲ������
	usart1struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//�������
	usart1struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//����У��
	usart1struct.USART_Parity = USART_Parity_No;
	//1λֹͣλ
	usart1struct.USART_StopBits = USART_StopBits_1;
	//����λ
	usart1struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&usart1struct);
	//6 �жϿ��Ƶ�����
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannel = USART1_IRQn;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
	//7 cmd��
	USART_Cmd(USART1,ENABLE);
	//�ж�ʹ�ܺ���
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	
}
//�����жϺ���

char res[32] = "";
char i = 0;
int flag = 0;         
int exitFlag = 0; // ����һ��ȫ�ֻ�ֲ���־����
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
			printf("������һ���ַ�����\r\n");

			
			char dmaStr[128] = "";//��һ������������������
			int index = 0;

			// �ȴ��û��������ݲ��洢�� dmaStr ��
			while (index < sizeof(dmaStr) - 1)  // ȷ�����ᳬ��������
			{
					if (USART_GetITStatus(USART1, USART_IT_RXNE))  // ����Ƿ���յ�����
					{
							char received_char = USART_ReceiveData(USART1);  // ����һ���ַ�
							if (received_char == '\n' || received_char == '\r')  // ����ǻ��з�����������,���뷽ʽ��hello world\n
							{
									break;
							}
							dmaStr[index++] = received_char;  // �洢�ַ�
					}
			}
			
			dmaStr[index] = '\0';  // �ַ���������
			printf("���յ��ַ�����%s\r\n", dmaStr);
			delay_ms(10);
			// DMA���ô�������
			MYDMA_CONFIG(DMA2_Stream7, DMA_Channel_4, (u32)(&USART1->DR), (u32)sendbuf, SEND_BUFF_SIZE);

			for (int i = 0; i < sizeof(dmaStr); i++)
			{
					sendbuf[i] = dmaStr[i];  // ��������ַ������ݿ����� sendbuf
			}

			printf("DMA��ʼ����\r\n");

			// ����DMA����
			USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
			// ����DMA����
			DMA_ENABLE(DMA2_Stream7, SEND_BUFF_SIZE);
			delay_ms(500);

			// �ȴ�DMA�������
			while (!DMA_GetFlagStatus(DMA2_Stream7, DMA_FLAG_TCIF7));

			DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);

			printf("DMA�������\r\n");
		}

		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		
	}	
	
	
	
	
	
	
	
}

//���ò���;
void uart2init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//1 ����ʱ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//2 D��ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	//3���Ź�������
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	//4.GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//������Ͳ�Ҫ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//5.//���ڳ�ʼ��
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	
	//6����2ʹ��
	USART_Cmd(USART2,ENABLE);
	//7�����ж�ʹ��
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	//8�ж�����
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);		
}
//�жϷ�����
void USART2_IRQHandler(void)
{
	unsigned char  res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{	
		res=USART_ReceiveData(USART2);
		switch(res)
		{
			//��LED1
			case 1:TurnOn_Led(LED1);break;
			//�ر�LED1
			case 2:TurnOff_Led(LED1);break;
			
		}
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}





