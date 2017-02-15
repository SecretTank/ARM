#include "stm32f4xx.h"
#include "stm32f4_define.h"
#include "USART.h"
#include "SPI.h"
#include "SSD1306.h"

#define DEBUG_SEND_USART printDebug
#define DEBUG_BYTE_USART printByteDebug


//set LED pins on discovery board to output mode
void dsco_led_init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0  | GPIO_MODER_MODER14_0  | GPIO_MODER_MODER15_0 ;
}

//call on avalible data on usart line
void UART4_IRQHandler(void) {
  uint8_t data;
	GPIOD->ODR ^= DISCOF4_LED_RED;
  if ( UART4->SR & USART_SR_RXNE ) 
  {
		UART4->SR &= ~USART_SR_RXNE;
  	data = UART4->DR;
    transmitByte(data);
  }
}

uint8_t spi_read_auto(uint8_t address) 
{
	uint8_t response;
	SPI_CS_LOW
	spi_transfer(address | 0x80);
	response = spi_transfer(0xFF);
	SPI_CS_HIGH
	return response;
}

uint8_t spi_write_auto(uint8_t address,uint8_t data) 
{
	uint8_t response;
	SPI_CS_LOW
	spi_transfer(address);
	response = spi_transfer(data);
	SPI_CS_HIGH
	return response;
}


void main ()
{
	dsco_led_init();
	spi_init(FALSE); //no hardware chip select
	usart_init();
	
	//initialise chip select on PD0 ( Open Drain not work for this module )
	GPIOD->MODER |= GPIO_MODER_MODER0_0 ;SPI_CS_HIGH
	
	uint8_t response, i;
	GPIOD->ODR ^= DISCOF4_LED_GREEN; //Lights on green LED
	uint8_t inReset = 1;
	printString("Reset command sent\r\n");
	i = 0;
	//ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
	ssd1306_init();
	ssd1306_display();
	ms_delay(300);
	ssd1306_clearDisplay();
	//ssd1306_clearDisplay();
	uint8_t gyro_xl, gyro_xh, gyro_yl, gyro_yh, gyro_zl, gyro_zh;
	uint8_t accel_xl, accel_xh, accel_yl, accel_yh, accel_zl, accel_zh;
	
	
	drawFastVLine(1,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(1,5,15,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastVLine(16,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(1,15,15,WHITE);
	ssd1306_display();
	ms_delay(30);
	
	drawFastVLine(25,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(25,15,15,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastVLine(40,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	
	drawFastVLine(50,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(50,5,10,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastVLine(60,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(60,5,10,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastVLine(70,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	
	drawFastVLine(80,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(80,5,15,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastVLine(96,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(80,15,15,WHITE);
	ssd1306_display();
	ms_delay(30);
	
	drawFastVLine(105,5,25,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(105,5,13,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastVLine(120,9,19,WHITE);
	ssd1306_display();
	ms_delay(30);
	drawFastHLine(105,30,13,WHITE);
	ssd1306_display();
	ms_delay(30);
	
	while (TRUE)
	{
		printString("Gyro : {");printWord((gyro_xh << 8) + gyro_xl);
		printString(", ");printWord((gyro_yh << 8) + gyro_yl);
		printString(", ");printWord((gyro_zh << 8) + gyro_zl);
		printString("}     Accel : {");printWord((accel_xh << 8) + accel_xl);
		printString(", ");printWord((accel_yh << 8) + accel_yl);
		printString(", ");printWord((accel_zh << 8) + accel_zl);printString("}\r");
		//drawFastHLine(1,1,70,WHITE);
		//ssd1306_display();
		ms_delay(50);
		ms_delay(20);
	}
}
