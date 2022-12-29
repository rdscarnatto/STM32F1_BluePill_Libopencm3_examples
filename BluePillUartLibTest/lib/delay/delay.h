#ifndef _DELAY_H
#define _DELAY_H

#include <libopencm3/cm3/nvic.h>

void delay_setup(void);
void delay_ms(uint32_t ms);


#endif /*delay.h*/
