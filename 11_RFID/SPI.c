#include "SPI.h"
#include "RFID.h"
#include <stdio.h>
#include <stdlib.h>

void initSPI(void) {
  SPI_SS_DDR |= (1 << SPI_SS);                        /* set SS output */
  SPI_SS_PORT |= (1 << SPI_SS);       /* start off not selected (high) */

  SPI_MOSI_DDR |= (1 << SPI_MOSI);                   /* output on MOSI */
  SPI_MISO_PORT |= (1 << SPI_MISO);                  /* pullup on MISO */
  SPI_SCK_DDR |= (1 << SPI_SCK);                      /* output on SCK */

  /* Don't have to set phase, polarity b/c
   * default works with 25LCxxx chips */
  SPCR |= (1 << SPR1);                /* div 16, safer for breadboards */
  SPCR |= (1 << MSTR);                                  /* clockmaster */
  SPCR |= (1 << SPE);                                        /* enable */
}

void SPI_tradeByte(uint8_t byte) {
  SPDR = byte;                       /* SPI starts sending immediately */
  loop_until_bit_is_set(SPSR, SPIF);                /* wait until done */
                                /* SPDR now contains the received byte */
}

void RFID_setRegister(uint8_t  data,uint8_t address) 
{
	SLAVE_SELECT;
	SPI_tradeByte( address << 1 ); //transmit command start 0x01 is address 
	SPI_tradeByte(data);
	SLAVE_DESELECT;
}

uint8_t RFID_readRegister(uint8_t address)
{
	SLAVE_SELECT;
	SPI_tradeByte( address << 1 | 0x80 ); //transmit command start 0x01 is address 
	SPI_tradeByte(0);
	SLAVE_DESELECT;
  return (SPDR);                                  /* return the result */
}

uint8_t* RFID_readFIFODataReg()
{
	int i;
	uint8_t* buffer;
	buffer =(uint8_t*) malloc(sizeof(char)*64);
	for(i=0;i<64;i++){
		if( RFID_readRegister(FIFOLEVELREG) == 0x00 )
			return buffer;
		buffer[i] = RFID_readRegister(FIFODATAREG);
	}
	return buffer;
}

uint8_t RFID_doWait(uint8_t command)
{
	uint8_t buffer;
	do
		buffer = RFID_readRegister(COMMANDREG); //loop until idel mode
	while(buffer != 0);
			
	buffer = buffer & 0xf0; // reset command bits 
	buffer |= command; // set command
	RFID_setRegister(COMMANDREG,buffer);
		
	do
		buffer = RFID_readRegister(COMMANDREG); //loop until idel mode
	while(buffer != 0);
}

