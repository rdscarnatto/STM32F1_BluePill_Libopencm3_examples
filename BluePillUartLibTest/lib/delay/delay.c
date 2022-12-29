#include <delay.h>
#include <libopencm3/cm3/systick.h>

volatile uint32_t mills;

void delay_setup()
{
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8); // 72Mhz/8 = 9M
	systick_set_reload(8999); //9M / 9000
	systick_counter_enable();
	systick_interrupt_enable();
}

void delay_ms(uint32_t ms)
{
	uint32_t lm = mills;
	while ((mills-lm) < ms);
	
}

void sys_tick_handler()
{
	mills++;
}
