#include "stm32f4xx.h"
#include "stm32f4_define.h"
#include "USART.h"
#include "SPI.h"
#define DISCOF4_LED_GREEN	1 << 12		//PD12
#define DISCOF4_LED_ORANGE	1 << 13		//PD13
#define DISCOF4_LED_RED		1 << 14		//PD14
#define DISCOF4_LED_BLUE	1 << 15		//PD15

#define  FATFS_CS_HIGH	GPIOD->ODR |= 1;
#define  FATFS_CS_LOW	GPIOD->ODR &= ~1;

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

void dsco_led_init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0  | GPIO_MODER_MODER14_0  | GPIO_MODER_MODER15_0 ;
}


/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/
// 1:Ready, 0:Timeout
//wt:	 Timeout [ms]
int wait_ready ( unsigned int wt )
{
	uint8_t d;
	
	do 
	{
		d = spi_send(0xFF);
	} while (d != 0xFF);	/* Wait for card goes ready or timeout */
	if (d == 0xFF) {
		DEBUG_SEND_USART("wait_ready: OK");
	} else {
		DEBUG_SEND_USART("wait_ready: timeout");
	}
	return (d == 0xFF) ? 1 : 0;
}


/*-----------------------------------------------------------------------*/
/* Deselect card and release SPI                                         */
/*-----------------------------------------------------------------------*/

void deselect (void)
{
	FATFS_CS_HIGH;			/* CS = H */
	spi_send(0xFF);			/* Dummy clock (force DO hi-z for multiple slave SPI) */
	DEBUG_SEND_USART("deselect: ok");
}



/*-----------------------------------------------------------------------*/
/* Select card and wait for ready                                        */
/*-----------------------------------------------------------------------*/

int select (void)	/* 1:OK, 0:Timeout */
{
	FATFS_CS_LOW;
	spi_send(0xFF);	/* Dummy clock (force DO enabled) */

	if (wait_ready(500)) {
		DEBUG_SEND_USART("select: OK");
		return 1;	/* OK */
	}
	DEBUG_SEND_USART("select: no");
	deselect();
	return 0;	/* Timeout */
}

void main ()
{
	dsco_led_init();
	spi_init();
	usart_init();
	GPIOD->MODER |= GPIO_MODER_MODER0_0; // ENABLE CHIP SELECT (PD0)
	
	printString("Hello World\r\n");
	
	
	uint8_t read_data;
	GPIOD->ODR ^= DISCOF4_LED_GREEN;
	
	ms_delay(400);
	while (TRUE)
	{
		//GPIOD->ODR ^= 1 << 13;
		deselect();
		if (!select())
		{ 
			GPIOD->ODR ^= DISCOF4_LED_RED;
		}
		spi_send(0x00);
		GPIOD->ODR ^= DISCOF4_LED_BLUE;
		DEBUG_BYTE_USART(spi_send( 0x40 | 0x00));	/* Start + command index */
		DEBUG_BYTE_USART(spi_send(0));	 			/* Argument[31..24] */
		DEBUG_BYTE_USART(spi_send(0));				/* Argument[23..16] */
		DEBUG_BYTE_USART(spi_send(0));				/* Argument[15..8] */
		DEBUG_BYTE_USART(spi_send(0));				/* Argument[7..0] */
		DEBUG_BYTE_USART(spi_send(0x95));			/* CRC */

		/* Receive command resp */
		uint8_t res;
		int n = 10;								/* Wait for response (10 bytes max) */
		do 
		{
			res = spi_send(0xFF);
			DEBUG_BYTE_USART(res);
		} while ((res & 0x80) && --n);
		ms_delay(1000);
		//DEBUG_BYTE_USART(n);
		//printString("\r\n");
			//GPIOD->ODR ^= 1 << 12;
	}
}
