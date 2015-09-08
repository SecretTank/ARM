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
	initUSART();
	while(1){
		printString("hello world ! :D \r\n");
		ms_delay(100);
	}
}
