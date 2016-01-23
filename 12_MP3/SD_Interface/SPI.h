/* Functions to initialize, send, receive over USART

   initUSART requires BAUD to be defined in order to calculate
     the bit-rate multiplier.
 */

#ifndef _SPI_STM32_H_                   /* if not defined in Makefile... */
#define _SPI_STM32_H_

#include "stm32f4xx.h"
#include "stm32f4_define.h"

#define SPI_CHECK_ENABLED_RESP(SPIx)   if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return 0;}
#define SPI_IS_BUSY(SPIx) (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || ((SPIx)->SR & SPI_SR_BSY))
#define SPI_WAIT(SPIx)            while (SPI_IS_BUSY(SPIx))

uint8_t spi_send(uint8_t data);

void rcc_wait_for_osc_ready();

void spi_init();
#endif

