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


void main ()
{
	dsco_led_init();
	spi_init(FALSE); //no hardware chip select
	usart_init();
	//initialise chip select on PD0
	//GPIOD->OTYPER |= GPIO_OTYPER_OT_0; //Open Drain : 0 : 0 , 1: Z

	GPIOD->MODER |= GPIO_MODER_MODER0_0 ;
	
	SPI_CS_HIGH
	
	uint8_t response;
	GPIOD->ODR ^= DISCOF4_LED_GREEN; //Lights on green LED
	
	ms_delay(500);

	uint8_t isReset = 1;
	SPI_CS_LOW
	spi_transfer(0x6B);
	SPI_CS_HIGH
	ms_delay(100); 
	spi_transfer(0x80);
	ms_delay(100);
	printString("Hello World\r\n");
	while ( isReset )
	{
		SPI_CS_LOW
		spi_transfer( 0x6B | 0x80 );
		//ms_delay(100);
		isReset = spi_transfer(0xFF) & 0x80;
		//ms_delay(100);
	}
	printString("Module resets\r\n");
	spi_transfer(0x6A);
	ms_delay(100);
	spi_transfer(0x10);
	ms_delay(100);
	spi_transfer(0x68);
	ms_delay(100);
	spi_transfer(0x07);
	ms_delay(100);
	spi_transfer( 0x75 | 0x80) ;
	ms_delay(100);
	response = spi_transfer(0xFF);
	ms_delay(100);
	printString("ID: ");
 	printWord(response);
	printString("\r\n");
	/*spi_transfer(0x6B); 
	spi_transfer(0x6B); 
	spi_transfer(0x6B); 
	spi_transfer(0x6B); 
	spi_transfer(0x6B); 
	spi_transfer(0x6B); 
	spi_transfer(0x6B);*/
	while (TRUE)
	{
		//
		//Put Your Magic Here
		//
		
		//DEBUG_SEND_USART("we are inside the loop!\r\n");

		SPI_CS_HIGH
		ms_delay(1000);
		SPI_CS_LOW
		spi_transfer( 0x75 | 0x80) ;
		ms_delay(100);
		response = spi_transfer(0xFF);
		printString("Response: ");
		printWord(response);
		printString("\r\n");

		
		ms_delay(1);
		ms_delay(1);
		//ms_delay(100000); //wait for end of world
		
		//finish tutorial
		//lets fly
	}
}
