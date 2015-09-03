                /* Reads LM75 Thermometer and Prints Value over Serial */

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#include "pinDefines.h"
#include "USART.h"
#include "i2c.h"

// -------- Defines -------- //

#define EEPROM_ADDRESS_W               0b10100000
#define EEPROM_ADDRESS_R               0b10100001
// -------- Functions --------- //
#define EEPROM_ADDRESS_DATA_H          0b00100001
#define EEPROM_ADDRESS_DATA_L          0b00100000
#define EEPROM_DATA                    'h'

int main(void) {


  // -------- Inits --------- //
  initUSART();
  printString("\r\n====  EEPROM STARTED  ====\r\n");
  initI2C();
  
  int Read_Data;

  while (1)
  {
    //Write To EEPROM
    i2cStart();
    i2cSend(EEPROM_ADDRESS_W);
    i2cStop();
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
