#include "SPI.h"

uint8_t spi_transfer(uint8_t data) 
{
	SPI_CHECK_ENABLED_RESP(SPI2); //check if spi is enabled
	SPI_WAIT(SPI2);
	SPI2->DR = data;
	SPI_WAIT(SPI2);
	loop_until_bit_is_set(SPI2->SR,SPI_SR_RXNE); //wait to recieve data
	return SPI2->DR;
}

//initialise spi on 
//PB12: SPI2_NSS (optional)
//PB13: SPI2_SCK
//PB14: SPI2_MISO
//PB15: SPI2_MOSI
void spi_init(bool internal_cs)
{
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;		//enable SPI clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//enable PINs clock
	GPIOB->MODER |= GPIO_MODER_MODER13_1  | GPIO_MODER_MODER14_1  | GPIO_MODER_MODER15_1; //set alternate function
	GPIOB->OSPEEDR |= 0x03 << 26 | 0x03 << 28 | 0x03 << 30;	//set pins maximum speed
	GPIOB->AFR[1] |= 0x05 << 20 | 0x05 << 24 | 0x05 << 28 ;	//set pins alternate function to SPI2
	
	//set baudrate <TWEAK IT FOR MORE POWER REZA!>
	
	SPI2->CR1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;
	SPI2->CR1 |= SPI_CR1_CPHA | SPI_CR1_CPOL;
	SPI2->CR1 |= SPI_CR1_MSTR;	//set this controller as host (master)
	if (internal_cs)
	{
		GPIOB->AFR[1] |= 0x05 << 16 ;			//set pins alternate function to SPI2
		GPIOB->MODER |= GPIO_MODER_MODER12_1 ;	//set alternate function
		GPIOB->OSPEEDR |= 0x03 << 24;			//set pins maximum speed
		SPI2->CR1 |= SPI_CR1_SSI | SPI_CR1_SSM;
	}
	else
	{
		SPI2->CR2 |= SPI_CR2_SSOE;				//prevent from enter multimaster mode
	}
	SPI2->CR1 |= SPI_CR1_SPE;	//enable spi unit
}
