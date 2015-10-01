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
					; //loop until idel mode
				printByte(RFID_readRegister());
				printString("\r\n====  RFID Responsed ====\r\n");

				_delay_ms(1000);
		}                                                  /* End event loop */
		return (0);                            /* This line is never reached */
}
