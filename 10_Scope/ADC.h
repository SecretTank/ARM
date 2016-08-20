#include "stm32f4xx.h"
#include "USART.h"
/* Takes the defined BAUD and F_CPU,
   calculates the bit-clock multiplier,
   and configures the hardware USART                   */
void initADC(void);
void initADC_Cont(void);
void ADC_DataSend(void);

