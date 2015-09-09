#include "ADC.h"

#define 	bit_is_set(sfr, bit)   (sfr & bit)
#define 	bit_is_clear(sfr, bit)   (!(sfr & (bit)))
#define 	loop_until_bit_is_set(sfr,bit)   do { } while (bit_is_clear(sfr, bit))
#define 	loop_until_bit_is_clear(sfr, bit)   do { } while (bit_is_set(sfr, bit))
#define		TRUE	1 
#define		FALSE	0 

void initADC(void)
{                                /* requires BAUD*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // enable the clock to GPIOA
	RCC->APB2ENR |= RRCC_APB2ENR_ADC2EN;  //enable the clock to ADC2
    asm("dsb");                           // stall instruction pipeline, until instruction completes, as

	GPIOA->MODER |= GPIO_MODER_MODER0_1;  //set alternative function for gpioA (1:0) pins
	GPIOA->AFR[0] = 0x88 ;				//set for uart4..6 for pin A0 and A1 (AF8)
	UART4->CR1 |= USART_CR1_UE;			//enable uart
	//UART4->CR1 |= USART_CR1_M;			//program to define word length
	//UART4->CR2 |= USART_CR2_STOP;
	UART4->BRR = 0x00000682;           //set baudrate to 9600
	UART4->CR1 |= USART_CR1_TE; 		//enable uart receiver
	UART4->CR1 |= USART_CR1_RE;		//enable uart transmiter
}


void ADC_DataSend()
{
  /* Wait for empty transmit buffer */
  loop_until_bit_is_set(UART4->SR,USART_SR_TXE);
  UART4->DR |= data;                                            /* send data */
  UART4->DR = (uint16_t)(data & 0x01FF);
}
