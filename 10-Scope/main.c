#include "USART.h"

void Delay( uint32_t nCount) 
{
  while(nCount--) {
  }
}
 
void ms_delay(int ms)
{
   while (ms-- > 0) 
   {
      volatile int x=5971;
      while (x-- > 0)
        asm("nop");
   }
}


int main(void)
{
	char buffer[100];
	initUSART();
	while(1){
		printString("another pretty day is started ! \r\nwhat do u want ? \r\n");
		readString(buffer,100);
		if( buffer == "go to hell"){
				printString("\r\nshut up ... \r\n");
		}
		else {
				printString("\r\nerror in input command\r\n");
		}
		ms_delay(300);
	}
}
