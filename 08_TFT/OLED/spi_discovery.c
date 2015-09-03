
#include "stm32f4xx.h"
//#include <libopencm3/stm32/f4/spi.h>
//#include <libopencm3/stm32/f4/rcc.h>
//#include <libopencm3/stm32/f4/gpio.h>
#define 	_BV(bit)   (1 << (bit))
#define 	bit_is_set(sfr, bit)   (sfr == _BV(bit))
#define 	bit_is_clear(sfr, bit)   (!(sfr == _BV(bit)))
#define 	loop_until_bit_is_set(sfr, bit)   do { } while (bit_is_clear(sfr, bit))
#define 	loop_until_bit_is_clear(sfr, bit)   do { } while (bit_is_set(sfr, bit))
#define		TRUE	1 
#define		FALSE	0 
#define SPI_CHECK_ENABLED_RESP(SPIx)   if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return ;}
#define SPI_IS_BUSY(SPIx) (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || ((SPIx)->SR & SPI_SR_BSY))
#define SPI_WAIT(SPIx)            while (SPI_IS_BUSY(SPIx))


void Delay(__IO uint32_t nCount) 
{
  while(nCount--) {
  }
}
 
void ms_delay(int ms)
{
   while (ms-- > 0) 
   {
      volatile int x=5971;
      while (x-- > 0)
        asm("nop");
   }
}

void spi_send(uint8_t data) 
{
	SPI_CHECK_ENABLED_RESP(SPI2);
	SPI_WAIT(SPI2);
	SPI2->DR = data;
	SPI_WAIT(SPI2);
}

void rcc_wait_for_osc_ready()
{
	while ((RCC->CR & RCC_CR_HSIRDY) == 0);
	{
		;
	}
}

void spi_init()
{
	//RCC->CR |= RCC_CR_HSEON;
	//uint32_t reg32;

	//reg32 = RCC->CFGR;
	//reg32 &= ~((1 << 1) | (1 << 0));
	//RCC->CFGR = reg32 ;
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= 1 << 27 | 1 << 29 | 1 << 31;
	GPIOB->OSPEEDR |= 0x03 << 26 | 0x03 << 28 | 0x03 << 30;
	GPIOB->AFR[1] |= 0x05 << 20 | 0x05 << 24 | 0x05 << 28 ;
	SPI2->CR1 &= 0x7 << SPI_CR1_BR;	
	SPI2->CR1 |= SPI_CR1_MSTR;
	SPI2->CR1 |= SPI_CR1_SSI | SPI_CR1_SSM;
	SPI2->CR1 |= SPI_CR1_SPE;
	//RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	//GPIOB->MODER |= 1 << 27 | 1 << 29 | 1 << 31;
	//GPIOB->OSPEEDR |= 0x03 << 26 | 0x03 << 28 | 0x03 << 30;
	//SPI2->CR1 = SPI_CR1_
}

uint8_t spi_read()
{
	loop_until_bit_is_set(SPI2->SR,SPI_SR_RXNE);
	return SPI2->DR;
}



/*
4. Configure the LSBFIRST bit in the SPI_CR1 register to define the frame format. This
step is not required when the TI mode is selected.
5. If the NSS pin is required in input mode, in hardware mode, connect the NSS pin to a
high-level signal during the complete byte transmit sequence. In NSS software mode,
set the SSM and SSI bits in the SPI_CR1 register. If the NSS pin is required in output
mode, the SSOE bit only should be set. This step is not required when the TI mode is
selected.
6. Set the FRF bit in SPI_CR2 to select the TI protocol for serial communications.
7. The MSTR and SPE bits must be set (they remain set only if the NSS pin is connected
to a high-level signal).
*/

void main ()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= 1 << 24 | 1 << 26 | 1 << 28 | 1 << 30;
	spi_init();
	uint8_t read_data;
	GPIOD->ODR ^= 1 << 12;
	while (TRUE)
	{
		//GPIOD->ODR ^= 1 << 13;
		spi_send(0x05);
		//GPIOD->ODR ^= 1 << 14;
		//read_data = spi_read();
		//GPIOD->ODR ^= 1 << 15;
		if ( read_data != 0x05 )
		{
			;
		}
		//GPIOD->ODR ^= 1 << 12;
	}
}
