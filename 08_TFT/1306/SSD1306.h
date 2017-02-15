/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
#ifndef _SSD1306_H_
#define _SSD1306_H_


#define DISCOF4_LED_GREEN	1 << 12		//PD12
#define DISCOF4_LED_ORANGE	1 << 13		//PD13
#define DISCOF4_LED_RED		1 << 14		//PD14
#define DISCOF4_LED_BLUE	1 << 15		//PD15

#define  SPI_CS_HIGH	GPIOD->ODR |= 1;
#define  SPI_CS_LOW		GPIOD->ODR &= ~1;
#define  SPI_DC_HIGH	GPIOD->ODR |= DISCOF4_LED_GREEN;
#define  SPI_DC_LOW		GPIOD->ODR &= ~DISCOF4_LED_GREEN;
#define  SPI_RST_HIGH	GPIOD->ODR |= DISCOF4_LED_ORANGE;
#define  SPI_RST_LOW		GPIOD->ODR &= ~DISCOF4_LED_ORANGE;


#define BLACK 0
#define WHITE 1
#define INVERSE 2


#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 64
	
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

void ssd1306_init();
uint8_t ssd1306_command(uint8_t c);

void ssd1306_clearDisplay(void);
void invertDisplay(uint8_t i);
void ssd1306_display();
void ms_delay(int ms);


void drawPixel(int16_t x, int16_t y, uint16_t color);

void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

void drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color);
void drawFastVLineInternal(int16_t x, int16_t __y, int16_t __h, uint16_t color);

#endif /* _Adafruit_SSD1306_H_ */
