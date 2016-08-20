#include "USART.h"

#define 	bit_is_set(sfr, bit)   (sfr & bit)
#define 	bit_is_clear(sfr, bit)   (!(sfr & (bit)))
#define 	loop_until_bit_is_set(sfr,bit)   do { } while (bit_is_clear(sfr, bit))
#define 	loop_until_bit_is_clear(sfr, bit)   do { } while (bit_is_set(sfr, bit))
#define		TRUE	1 
#define		FALSE	0 

/*
	BAUD 9600   : 0x682
	BAUD 115200 : 0x88
*/

void initUSART(void)
{                                /* requires BAUD*/
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // enable the clock to GPIOA
		RCC->APB1ENR |= RCC_APB1ENR_UART4EN;			//enable the clock to UART4
		asm("dsb");                         // stall instruction pipeline, until instruction completes, as

		GPIOA->MODER |= GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1;  //set alternative function for gpioA (1:0) pins
		GPIOA->AFR[0] = 0x88 ;				//set for uart4..6 for pin A0 and A1 (AF8)
		UART4->CR1 |= USART_CR1_UE;			//enable uart
		//UART4->CR1 |= USART_CR1_M;			//program to define word length
		//UART4->CR2 |= USART_CR2_STOP;
		UART4->BRR = 0x00000088;           //set baudrate to 115200
		UART4->CR1 |= USART_CR1_TE; 		//enable uart receiver
		UART4->CR1 |= USART_CR1_RE;		//enable uart transmiter
		UART4->SR &= ~USART_SR_RXNE;
}


void transmitByte(uint8_t data)
{
		/* Wait for empty transmit buffer */
		loop_until_bit_is_set(UART4->SR,USART_SR_TXE);
		UART4->DR |= data;                                            /* send data */
		UART4->DR = (uint8_t)(data);
		loop_until_bit_is_set(UART4->SR,USART_SR_TC);
}

uint8_t receiveByte(void) {
		loop_until_bit_is_set(UART4->SR,USART_SR_RXNE);       /* Wait for incoming data */
		if(UART4->SR |= USART_SR_ORE)
		{
				GPIOD->ODR ^= (1 << 12);				
		}
		UART4->SR &= ~USART_SR_RXNE;
		return UART4->DR;                                /* return register value */
}


/* Here are a bunch of useful printing commands */

void printString(const char myString[]) {
		int8_t i = 0;
		while (myString[i]) {
				transmitByte(myString[i]);
				i++;
		}
}

void readString(char myString[], uint8_t maxLength) {
		char response;
		uint8_t i;
		i = 0;
		while (i < (maxLength - 1)) {                   /* prevent over-runs */
				response = receiveByte();
				transmitByte(response);                                    /* echo */
				if (response == '\r') {                     /* enter marks the end */
						break;
				}
				else {
						myString[i] = response;                       /* add in a letter */
						i++;
				}
		}
		myString[i] = 0;                          /* terminal NULL character */
}

void printByte(uint8_t byte) {
		/* Converts a byte to a string of decimal text, sends it */
		transmitByte('0' + (byte / 100));                        /* Hundreds */
		transmitByte('0' + ((byte / 10) % 10));                      /* Tens */
		transmitByte('0' + (byte % 10));                             /* Ones */
}

void printWord(uint16_t word) {
		transmitByte('0' + (word / 10000));                 /* Ten-thousands */
		transmitByte('0' + ((word / 1000) % 10));               /* Thousands */
		transmitByte('0' + ((word / 100) % 10));                 /* Hundreds */
		transmitByte('0' + ((word / 10) % 10));                      /* Tens */
		transmitByte('0' + (word % 10));                             /* Ones */
}

void printBinaryByte(uint8_t byte) {
		/* Prints out a byte as a series of 1's and 0's */
		uint8_t bit;
		for (bit = 7; bit < 255; bit--) {
				if (bit_is_set(byte, bit))
						transmitByte('1');
				else
						transmitByte('0');
		}
}

char nibbleToHexCharacter(uint8_t nibble) {
		/* Converts 4 bits into hexadecimal */
		if (nibble < 10) {
				return ('0' + nibble);
		}
		else {
				return ('A' + nibble - 10);
		}
}

void printHexByte(uint8_t byte) {
		/* Prints a byte as its hexadecimal equivalent */
		uint8_t nibble;
		nibble = (byte & 0b11110000) >> 4;
		transmitByte(nibbleToHexCharacter(nibble));
		nibble = byte & 0b00001111;
		transmitByte(nibbleToHexCharacter(nibble));
}

uint8_t getNumber(void) {
		// Gets a numerical 0-255 from the serial port.
		// Converts from string to number.
		char hundreds = '0';
		char tens = '0';
		char ones = '0';
		char thisChar = '0';
		do 
		{                                               /* shift over */
				hundreds = tens;
				tens = ones;
				ones = thisChar;
				thisChar = receiveByte();                   /* get a new character */
				transmitByte(thisChar);                                    /* echo */
		} while (thisChar != '\r');                     /* until type return */
		return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}
