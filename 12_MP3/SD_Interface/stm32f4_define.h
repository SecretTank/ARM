#ifndef _STM32_F$_DEFINE_H_
#define _STM32_F$_DEFINE_H_

#define 	_BV(bit)   (1 << (bit))
#define 	bit_is_set(sfr, bit)   (sfr & bit)
#define 	bit_is_clear(sfr, bit)   (!(sfr & bit))
#define 	loop_until_bit_is_set(sfr, bit)   do { } while (bit_is_clear(sfr, bit))
#define 	loop_until_bit_is_clear(sfr, bit)   do { } while (bit_is_set(sfr, bit))
#define		TRUE	1 
#define		FALSE	0 

#endif
