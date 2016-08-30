#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include "SD_Card.h"

void init_SPI_mega16(void) 
{
     DDRB =  ( 1 << MOSI ) | ( 1 << CLK  ) | ( 1 << CS   );
     SPCR =  ( 1 << SPE  ) | ( 1 << MSTR ) | ( 1 << SPR0 );
}

char SPI_sendchar(char chr) 
{
     SPDR = chr;
     while(!(SPSR & (1<<SPIF)));
     return SPDR;
}

char Command(char cmd, uint16_t ArgH, uint16_t ArgL, char crc ) {
     SPI_sendchar(0xFF);
     SPI_sendchar(cmd);
     SPI_sendchar((uint8_t)(ArgH >> 8));
     SPI_sendchar((uint8_t)ArgH);
     SPI_sendchar((uint8_t)(ArgL >> 8));
     SPI_sendchar((uint8_t)ArgL);
     SPI_sendchar(crc);
     SPI_sendchar(0xFF);
     return SPI_sendchar(0xFF);                // Returns the last byte received
}

void init_SD(void) 
{
		unsigned char i, response, retry=0 ;

		ENABLE_SD;
		do
		{
				for(i=0;i<10;i++)
					SPI_sendchar(0xff);
				response = SD_sendCommand(GO_IDLE_STATE, 0);      //send 'reset & go idle' command
				retry++;
				if(retry>0xfe) 
				{
					printString("SD init fail..Code: ");
					printByte(response);
					printString("Retry: ");
					printByte(retry);
					printString("\r\n");
					return ;
				} //time out
			 
		} while(response != 0x01);

		DISABLE_SD;
		SPI_sendchar (0xff);
		SPI_sendchar (0xff);

		retry = 0;

		do
		{
				response = SD_sendCommand(SEND_OP_COND, 0); //activate card's initialization process
				response = SD_sendCommand(SEND_OP_COND, 0); //same command sent again for compatibility with some cards
				retry++;
				if(retry>0xfe)
				{
					printString("SD Failed: SEND_OP_COND\r\n");
					return ; //time out
				}
		}while(response);

		SD_sendCommand(CRC_ON_OFF, 0); //disable CRC; deafault - CRC disabled in SPI mode
		SD_sendCommand(SET_BLOCK_LEN, 512); //set block size to 512

		printString("SD initialized\r\n");
		return;
}

unsigned char SD_sendCommand(unsigned char cmd, unsigned long arg)
{
		unsigned char response, retry=0;

		ENABLE_SD;

		SPI_sendchar(cmd | 0x40); //send command, first two bits always '01'
		SPI_sendchar(arg>>24);
		SPI_sendchar(arg>>16);
		SPI_sendchar(arg>>8);
		SPI_sendchar(arg);
		SPI_sendchar(0x95);

		while((response = SPI_sendchar(0xff)) == 0xff) //wait response
			 if(retry++ > 0xfe) break; //time out error

		SPI_sendchar(0xff); //extra 8 CLK
		DISABLE_SD;

		return response; //return state
}

unsigned char SD_writeSingleBlock(unsigned long startBlock)
{ 
    uint8_t wbr;
    
    unsigned char response;
		unsigned int i;
		DISABLE_SD;
		response = SD_sendCommand(24, startBlock<<9); //write a Block command
		if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
			return response;

		ENABLE_SD;

		SPI_sendchar(0xfe);     //Send start block token 0xfe (0x11111110)

		for(i=0; i<512; i++)    //send 512 bytes data
		{
			SPI_sendchar(buffer[i]);
			//SPI_sendchar(0x12);
		}
    
    SPI_sendchar(0xff); //transmit dummy CRC (16-bit), CRC is ignored here
		SPI_sendchar(0xff);

		wbr = SPI_sendchar(0xff);
    //write block response and testing error
    wbr &= 0x1F;
    //zeroing top three indeterminate bits 0b.0001.1111
    if (wbr != 0x05) 
    {
			printString("ERooR\r\n");
			printByte(wbr);
		  return 1;
    }
    while(SPI_sendchar(0xFF) != (char)0xFF);
		//printString("File writed\r\n");
    //wait for the completion of a write operation to the card
    DISABLE_SD;
    return 0;
}

unsigned char SD_readSingleBlock(unsigned long startBlock)
{
    /*int i;
    uint16_t ix;
    char r1 =  Command(0x51,0,512,0xFF);
    for (ix = 0; ix < 50000; ix++) {
        if (r1 == (char)0x00) break;
        r1 = SPI_sendchar(0xFF);
    }
    if (r1 != (char)0x00) {
    return 1;
    }
    //read from the card will start after the framework
    while(SPI_sendchar(0xFF) != (char)0xFE);
    for(i=0; i < 512; i++) {
        while(!(SPSR & (1<<SPIF)));
        buffer[i] = SPDR;
        SPDR = SPI_sendchar(0xFF);
    }
    SPI_sendchar(0xFF);
    SPI_sendchar(0xFF);
    return 0;*/
    unsigned char response;
		unsigned int i, retry=0;

		response = SD_sendCommand(READ_SINGLE_BLOCK, startBlock<<9); //read a Block command
		//block address converted to starting address of 512 byte Block
		if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
			return response;

		ENABLE_SD;

		retry = 0;
		while(SPI_sendchar(0xFF) != 0xfe) //wait for start block token 0xfe (0x11111110)
		{
			if(retry++ > 0xfffe)
			{
				printString("Error reading\r\n");
				DISABLE_SD;
				return 1;
			} //return if time-out
		}

		for(i=0; i<512; i++) //read 512 bytes
			buffer[i] = SPI_sendchar(0xFF);

		SPI_sendchar(0xFF); //receive incoming CRC (16-bit), CRC is ignored here
		SPI_sendchar(0xFF);

		SPI_sendchar(0xFF); //extra 8 clock pulses
		DISABLE_SD;
		//printString("Reading succesful\r\n");

		return 0;
}
