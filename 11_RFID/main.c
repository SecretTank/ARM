/* SPI EEPROM 25LC256 Demo */

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#include "pinDefines.h"

#include "USART.h"
#include "SPI.h"
#include "RFID.h"

int main(void) {
		uint8_t i;
		uint8_t buffer;
		//uint8_t address;

		// -------- Inits --------- //
		initSPI();
		initUSART();
		
		// ------ Event loop ------ //
		while (1) 
		{
				RFID_doWait(PCD_SOFTRESET); // perform softreset 
				RFID_doWait(PCD_MEM);

				_delay_ms(2000);
				
				printString("\r\n====  RFID Responsed ====\r\n");
				printByte(RFID_readRegister(CommandReg));
				uint8_t *FIFO = RFID_readFIFODataReg();
				for (i = 0 ; i < 64 ; i++)
					printByte(FIFO[i]);

		}                                                  /* End event loop */

		return (0);                            /* This line is never reached */
}
