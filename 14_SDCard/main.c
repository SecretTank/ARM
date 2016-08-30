#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include "FAT32.h"
#include "SD_Card.h"
#include <avr/interrupt.h>


int main(void) 
{
    //int i;
    char filename[12] = "amiri.txt";
    unsigned char error, FAT32_active;
    initUSART();
    init_SPI_mega16();
    init_SD();
    printString("Start Writing File!\r\n");                          /* to test */
    
    
    
    FAT32_active = 1;
    error = getBootSectorData (); //read boot sector and keep necessary data in global variables
    if(error) 	
    {
        printString("FAT32 not found!\r\n");  //FAT32 incompatible drive
        FAT32_active = 0;
    }
    else
    {
        printString("FAT32 Detected\r\n");  //FAT32 incompatible drive
    }
    
    if (FAT32_active)
    {
        _delay_ms(1000); 
        printString("Writing to file!\r\n");                          /* to test */
        writeFile(filename);
    }
    findFiles(GET_LIST,0);
    while(1)
    {
        printString("Hello World!\r\n");                          /* to test */
        _delay_ms(1000); 
        _delay_ms(1000); 
    }
    
    return 0;
}
