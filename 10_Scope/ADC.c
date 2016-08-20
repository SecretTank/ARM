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
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;  //enable the clock to ADC2
		asm("dsb");                           // stall instruction pipeline, until instruction completes, as

		GPIOA->MODER |= GPIO_MODER_MODER2;//set alternative function for gpioA (1:0) pins
		ADC2->CR1 |= USART_CR1_UE;			  //enable uart
		ADC2->CR2 |= ADC_CR2_ADON;				//enable ADC
		ADC2->SQR3 |= ADC_SQR3_SQ1_1;			// setting channell
}

void initADC_Cont(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // enable the clock to GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;  //enable the clock to ADC2
    asm("dsb");                           // stall instruction pipeline, until instruction completes, as

	GPIOA->MODER |= GPIO_MODER_MODER2;//set alternative function for gpioA (1:0) pins
	ADC2->CR1 |= USART_CR1_UE;			  //enable uart
	ADC2->CR2 |= ADC_CR2_ADON;				//enable ADC
	ADC2->SQR3 |= ADC_SQR3_SQ1_1;			// setting channell
	ADC2->CR1 |=ADC_CR1_EOCIE;
	//ADC->CR2 |=ADC_CR2_CONT;
	ADC2->CR2 |=ADC_CR2_SWSTART;
}

void ADC_DataSend(void)
{
  /* Wait for empty transmit buffer */
	uint16_t data;
	uint8_t data8_bit; 
	ADC2->CR2 |= ADC_CR2_SWSTART;               			//enable uart
	loop_until_bit_is_set(ADC2->SR,ADC_SR_EOC);				//wait till adc conversion
	data=ADC2->DR&0xfff;
	data8_bit=data%0x100;						//send LSB									
  transmitByte(data8_bit);
  data8_bit=data/0x100;						//send MSB
	transmitByte(data8_bit);
	transmitByte('\r');             /* send data */
}

void ADC_IRQHandler(void)
{
	printString("hi\r\n");
}


