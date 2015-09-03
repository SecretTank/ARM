#include "stm32f4xx.h"

void Delay(__IO uint32_t nCount) 
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



//Flash orange LED at about 1hz
int main(void)
{
	int i;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // enable the clock to GPIOD
    asm("dsb");                         // stall instruction pipeline, until instruction completes, as
                                          //    per Errata 2.1.13, "Delay after an RCC peripheral clock enabling"
    GPIOD->MODER = (1 << 26);             // set pin 13 to be general purpose output
    GPIOD->MODER |= (1 << 24);
    GPIOD->MODER |= (1 << 28);
    GPIOD->MODER |= (1 << 30);

    for (i=150;;i=i/1.1) 
    {
       ms_delay(i);
       GPIOD->ODR ^= (1 << 13);           // Toggle the pin 
       ms_delay(i);
       GPIOD->ODR ^= (1 << 12);           
       ms_delay(i);
       GPIOD->ODR ^= (1 << 15);
       ms_delay(i);
       GPIOD->ODR ^= (1 << 14);
	if(i<=1)i=80;
    }
}
