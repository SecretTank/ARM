#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include <string.h>

void initBlue(void);


void test_Read(char myString[])
{
	char response;
  uint8_t i;
  i = 0;
  while (i < (49)) {                   /* prevent over-runs */
    response = receiveByte();
    transmitByte(response);                                    /* echo */
    if (response == 'n') {                     /* enter marks the end */
      break;
    }
    else {
      myString[i] = response;                       /* add in a letter */
      i++;
    }
  }
	myString[i] = 0;
	printString("\r\n");
	printWord(i);
	printString("\r\n");
	printString(myString);
	printString("\r\n");
}

int main(void)
{
	char myString[50];
	while (1)
	{
		/*readString(str,50);
		printString(str);
		if (strcmp(str,"AT\r\n"))
			{
				printString(str);
			}
		readString(str,50);
		printString(str);*/

		initUSART();
  	printString("AT\r\n");
		test_Read(myString);
	  printString(myString);
		printString("\r\n");
		
	}

  return 0;
}




void initBlue(void)
{
	char myString[50];
	initUSART();
  printString("AT\r\n");
	test_Read(myString);

  printString(myString);
	printString("\r\n");
}
