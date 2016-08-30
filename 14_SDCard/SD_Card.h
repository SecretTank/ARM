#ifndef _SD_CARD_H_
#define _SD_CARD_H_

#define MISO 6                         // Port B bit 6 (pin7): data in (data from MMC)
#define MOSI 5                        // Port B bit 5 (pin6): data out (data to MMC)
#define CLK 7                     // Port B bit 7 (pin8): clock
#define CS 4                        // Port B bit 4 (pin5): chip select for MMC

#define GO_IDLE_STATE            0
#define SEND_OP_COND             1
#define SEND_CSD                 9
#define STOP_TRANSMISSION        12
#define SEND_STATUS              13
#define SET_BLOCK_LEN            16
#define READ_SINGLE_BLOCK        17
#define READ_MULTIPLE_BLOCKS     18
#define WRITE_SINGLE_BLOCK       24
#define WRITE_MULTIPLE_BLOCKS    25
#define ERASE_BLOCK_START_ADDR   32
#define ERASE_BLOCK_END_ADDR     33
#define ERASE_SELECTED_BLOCKS    38
#define CRC_ON_OFF               59

char buffer[512];
volatile unsigned long startBlock, totalBlocks;

#define DISABLE_SD PORTB |= _BV(CS)
#define ENABLE_SD  PORTB &= ~(_BV(CS))

void init_SPI_mega16(void);
char SPI_sendchar(char chr);
char Command(char cmd, uint16_t ArgH, uint16_t ArgL, char crc );

void init_SD(void);
unsigned char SD_sendCommand(unsigned char cmd, unsigned long arg);
unsigned char SD_readSingleBlock(unsigned long startBlock);
unsigned char SD_writeSingleBlock(unsigned long startBlock);

#endif
