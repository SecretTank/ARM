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
				do
					buffer = RFID_readRegister(CommandReg); //loop until idel mode
				while(buffer != 0);
					
					
				buffer = buffer | COMMAND_SoftReset; // perform softreset 
				RFID_setRegister(CommandReg,buffer);

				do
					buffer = RFID_readRegister(CommandReg); //loop until idel mode
				while(buffer != 0);
				
				buffer = buffer & 0xf0; // perform Mem 
				buffer |= COMMAND_Mem; // perform Mem 
				RFID_setRegister(CommandReg,buffer);
				
				_delay_ms(2000);
				
				printString("\r\n====  RFID Responsed ====\r\n");
				printByte(RFID_readRegister(CommandReg));
		}                                                  /* End event loop */
		return (0);                            /* This line is never reached */
}
