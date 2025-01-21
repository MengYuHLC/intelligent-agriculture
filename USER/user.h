
#ifndef __MAIN
#define __MAIN


#include "stm32f4xx.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "delay.h"

#define LED1 1
#define LED2 2
#define LED3 3
#define SEND_BUFF_SIZE 8200
//函数声明
//LED
void Config_Led();
void TurnOn_Led(unsigned int num);
void TurnOff_Led(unsigned int num);
void Flash_Led(unsigned int num);
void Flow_Led();
void mydelay(unsigned int time);
void my_led();
void ToggleLed();


//蜂鸣器
void Config_Beep();
void TurnOn_Beep();
void TurnOff_Beep();
void Flash_Beep();


//按键
void Config_Key();
void Scan_Key();


//systick
void my_delay_ms(unsigned int num);
void my_systick_config();

//中断
void INTERRUPT_KEY2_INIT();

//定时器
void TIMER4_Config(u16 psc , u16 arr);

//pwm
void TIM2_PWM_CH3_BEEP_CONFIG();
void BEEP_PWM_DRIVER();
//代码移植-提高效率
void TIM1_PWM_CH1_LED_CONFIG();
void TIM4_PWM_CH1_MOTOR_CONFIG();
void ledtestpwm();
void MOTO_LEFT();
void MOTO_RIGHT();

//串口调试
void my_usart1_config();
void uart2init();

//DHT11
void DHT11_Config();
void DHT11_OUTMODE();
void DHT11_INMODE();
u8 DHT11_ReadData();
u8 DHT11_ReadDataByte();


//iic的驱动函数
void iic_init();
void iic_start();
void iic_stop();
void iic_send_byte_data(unsigned char data);
u8 iic_getack();
u8 iic_get_byte_data();
u8 iic_send_ack(unsigned char ack);
#define ACK 0
#define NACK 1


//iic_AT24C02
u8 AT24C02_INIT();
u8 AT24C02_WRITE_BYTE(u8 wordaddr, u8 data);
unsigned char AT24C02_READ_BYTE(unsigned char word_addr,char * readbuff);

//oled
void WriteOLedCmd(uint8_t cmd);
void WriteOLedData(uint8_t data);
void OLed_Fill(unsigned char bmp_data);
void OLed_SetPos(unsigned char x, unsigned char y);
void InitOLed(void);
void Oled_print(uint8_t x, uint8_t y,char *str);
void OLed_ShowChina(uint8_t x,uint8_t y,uint8_t *buf);
void SSD1306_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);
void OLED_ShowString(uint8_t x, uint8_t y, char *str);

extern u8 paint[];
extern u8 aix[];
extern u8 mou[];

//SPI
void SPI1_Init();
u8 SPI1_ReadWriteByte(u8 data);
void w25q64_init();
u16 w25q64_readid();

u8 w25q64_earse_chip_all();
void w25q64_write_page(unsigned char *pbuffer,unsigned int writeaddr,unsigned short int numbyte);
unsigned int w25q64_read_data(uint32_t addr,uint8_t buff[],uint8_t len);

//传感器
void ADC1_LIGHT_SENSOR_Config();
u16 ADC1_get_light_value();
u16 ADC1_get_light_Average_value();
u8 Check_LightSensor_Data();

void ADC1_voltage_SENSOR_Config();
u16 ADC1_get_voltage_value();
u16 ADC1_get_voltage_Average_value();
u8 Check_VoltageSensor_Data(); 

//DMA
void MYDMA_CONFIG(DMA_Stream_TypeDef *DMA_Stream,u32 channel,u32 des,u32 sedbuf,u16 size);
void DMA_ENABLE(DMA_Stream_TypeDef *DMA_Stream,u16 size);




#endif












