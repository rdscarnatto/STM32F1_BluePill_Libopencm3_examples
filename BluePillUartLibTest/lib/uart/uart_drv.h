#ifndef _UART_DRV_H_
#define _UART_DRV_H_

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

void uart_init(unsigned long uart, uint32_t baud);
//Llamar las siguientes funciones solo despues de inicializar la UART
void uart_putc(uint8_t ch);
void uart_puts(char str[]);
char uart_getc(void);


#endif