#include "stm32f4xx.h"
#include "stm32f4_define.h"
#include "USART.h"
#include "SPI.h"
#define DISCOF4_LED_GREEN	1 << 12		//PD12
#define DISCOF4_LED_ORANGE	1 << 13		//PD13
#define DISCOF4_LED_RED		1 << 14		//PD14
#define DISCOF4_LED_BLUE	1 << 15		//PD15

#define  SPI_CS_HIGH	GPIOD->ODR |= 1;
#define  SPI_CS_LOW		GPIOD->ODR &= ~1;

#define DEBUG_SEND_USART printDebug
#define DEBUG_BYTE_USART printByteDebug

void ms_delay(int ms)
{
	while (ms-- > 0) 
	{
		volatile int x=5971;
		while (x-- > 0)
			asm("nop");
	}
}

//set LED pins on discovery board to output mode
void dsco_led_init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0  | GPIO_MODER_MODER14_0  | GPIO_MODER_MODER15_0 ;
}

//call on avalible data on usart line
void UART4_IRQHandler(void) {
  uint8_t data;
	GPIOD->ODR ^= DISCOF4_LED_RED;
  if ( UART4->SR & USART_SR_RXNE ) 
  {
		UART4->SR &= ~USART_SR_RXNE;
  	data = UART4->DR;
    transmitByte(data);
  }
}

uint8_t spi_read_auto(uint8_t address) 
{
	uint8_t response;
	SPI_CS_LOW
	spi_transfer(address | 0x80);
	response = spi_transfer(0xFF);
	SPI_CS_HIGH
	return response;
}

uint8_t spi_write_auto(uint8_t address,uint8_t data) 
{
	uint8_t response;
	SPI_CS_LOW
	spi_transfer(address);
	response = spi_transfer(data);
	SPI_CS_HIGH
	return response;
}


void main ()
{
	dsco_led_init();
	spi_init(FALSE); //no hardware chip select
	usart_init();
	
	//initialise chip select on PD0 ( Open Drain not work for this module )
	GPIOD->MODER |= GPIO_MODER_MODER0_0 ;SPI_CS_HIGH
	
	uint8_t response, i;
	GPIOD->ODR ^= DISCOF4_LED_GREEN; //Lights on green LED
	uint8_t inReset = 1;
	spi_write_auto(0x6B,0x80);
	printString("Reset command sent\r\n");
	i = 0;
	while ( inReset )
	{
		i++;
		response = spi_read_auto( 0x6B );
		inReset = response & 0x80;
		if ( i > 500 )
		{
			printString("Reset Error, Response: ");
			printWord(response);
			printString("\r\n");
			i = 0;
		}
	}
	response = spi_read_auto( 0x6B );
	printString("Module resets, Power MGT: ");printWord(response);printString("\r\n");
	response = spi_read_auto( 0x75 );
	printString("ID: ");printWord(response);printString("\r\n");
	uint8_t gyro_xl, gyro_xh, gyro_yl, gyro_yh, gyro_zl, gyro_zh;
	uint8_t accel_xl, accel_xh, accel_yl, accel_yh, accel_zl, accel_zh;
	while (TRUE)
	{
		gyro_xh = spi_read_auto( 67 ) ;
		gyro_xl = spi_read_auto( 68 ) ;
		gyro_yh = spi_read_auto( 69 ) ;
		gyro_yl = spi_read_auto( 70 ) ;
		gyro_zh = spi_read_auto( 71 ) ;
		gyro_zl = spi_read_auto( 72 ) ;
		printString("Gyro : {");printWord((gyro_xh << 8) + gyro_xl);
		printString(", ");printWord((gyro_yh << 8) + gyro_yl);
		printString(", ");printWord((gyro_zh << 8) + gyro_zl);
		accel_xh = spi_read_auto( 59 ) ;
		accel_xl = spi_read_auto( 60 ) ;
		accel_yh = spi_read_auto( 61 ) ;
		accel_yl = spi_read_auto( 62 ) ;
		accel_zh = spi_read_auto( 63 ) ;
		accel_zl = spi_read_auto( 64 ) ;
		printString("}     Accel : {");printWord((accel_xh << 8) + accel_xl);
		printString(", ");printWord((accel_yh << 8) + accel_yl);
		printString(", ");printWord((accel_zh << 8) + accel_zl);printString("}\r");
		ms_delay(20);
	}
}
