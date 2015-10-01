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
		//uint8_t address;

		// -------- Inits --------- //
		initSPI();
		initUSART();

		// ------ Event loop ------ //
		while (1) 
		{
				RFID_setRegister(
				while(!RFID_readRegister())
					;
				printByte(RFID_readRegister());
				printString("\r\n====  EEPROM Memory Playground ====\r\n");
				//printString("Address  Value\r\n");

				/*printString(" [e] to erase all memory\r\n");
				  printString(" [w] to write byte to memory\r\n\r\n");

				  switch (receiveByte()) {                             // take input
				  case 'e':
				  printString("Clearing EEPROM, this could take a few seconds.\r\n");
				  EEPROM_clearAll();
				  break;
				  case 'w':
				  printString("Which memory slot would you like to write to?\r\n");
				  address = getNumber();
				  printString("\r\nWhat number would you like to store there?\r\n");
				  i = getNumber();
				  EEPROM_writeByte(address, i);
				  printString("\r\n");
				  break;
				  default:
				  printString("What??\r\n");
				  }*/
				_delay_ms(1000);
		}                                                  /* End event loop */
		return (0);                            /* This line is never reached */
}
