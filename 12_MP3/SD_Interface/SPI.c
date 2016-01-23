#include "SPI.h"

uint8_t spi_send(uint8_t data) 
{
	SPI_CHECK_ENABLED_RESP(SPI2);
	SPI_WAIT(SPI2);
	SPI2->DR = data;
	SPI_WAIT(SPI2);
	loop_until_bit_is_set(SPI2->SR,SPI_SR_RXNE);
	return SPI2->DR;
}

void rcc_wait_for_osc_ready()
{
	while ((RCC->CR & RCC_CR_HSIRDY) == 0);
	{
		;
	}
}


//initialise spi on 
//PB13: SPI2_SCK
//PB14: SPI2_MISO
//PB15: SPI2_MOSI
void spi_init()
{
	//RCC->CR |= RCC_CR_HSEON;
	//uint32_t reg32;

	//reg32 = RCC->CFGR;
	//reg32 &= ~((1 << 1) | (1 << 0));
	//RCC->CFGR = reg32 ;
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER13_1  | GPIO_MODER_MODER14_1  | GPIO_MODER_MODER15_1; //set alternate function
	GPIOB->OSPEEDR |= 0x03 << 26 | 0x03 << 28 | 0x03 << 30;
	GPIOB->AFR[1] |= 0x05 << 20 | 0x05 << 24 | 0x05 << 28 ;
	SPI2->CR1 = SPI_CR1_BR_1 | SPI_CR1_BR_2;	
	SPI2->CR1 |= SPI_CR1_MSTR;
	SPI2->CR1 |= SPI_CR1_SSI | SPI_CR1_SSM;
	SPI2->CR1 |= SPI_CR1_SPE;
	//RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	//GPIOB->MODER |= 1 << 27 | 1 << 29 | 1 << 31;
	//GPIOB->OSPEEDR |= 0x03 << 26 | 0x03 << 28 | 0x03 << 30;
}
