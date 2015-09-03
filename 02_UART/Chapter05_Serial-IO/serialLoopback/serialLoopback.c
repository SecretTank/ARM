/*
A simple test of serial-port functionality.
Takes in a character at a time and sends it right back out,
 displaying the ASCII value on the LEDs.
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

int main(void) {
  char serialCharacter;
  char buffer[50];
  char hello[] = "hello";
  int flag = 0;
  int i = 0;
  int j = 0;

  // -------- Inits --------- //
  LED_DDR = 0xff;                            /* set up LEDs for output */
  initUSART();
  printString("Hello World!\r\n");                          /* to test */

  // ------ Event loop ------ //
  while (1) {
    i=0;
//    serialCharacter = receiveByte();
    do {	
    serialCharacter = receiveByte();
    transmitByte(serialCharacter);
    buffer[i] = serialCharacter;
    i = i + 1;
    }while (serialCharacter != '\r');
    
    for (j = 0 ; j < i-1 ; j++)
	if ( buffer[j] != hello[j] )
		flag = 1;
    
    if (flag == 0)
    {
    	transmitByte('h');
    	transmitByte('i');
    }
    else
		{
			printString("STFG\r\n");
		}
//    transmitByte(serialCharacter);
//    LED_PORT = serialCharacter;
                           /* display ascii/numeric value of character */

  }                                                  /* End event loop */
  return (0);
}
