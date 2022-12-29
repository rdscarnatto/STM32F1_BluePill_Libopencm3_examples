#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <delay.h>
#include <uart_drv.h>
//#include <libopencm3/stm32/f1/usart.h>


int signal = 0;
char chat = 'M';

static void BP_setup(void);


int main(void)
{
	// Init BluePill clocks and componets 
	BP_setup();
	// Setup delay interrupts
	delay_setup();
	// Setup uart interface
	uart_init(USART2, 115200);


	while (1)
	{
		// Get char from uart
		chat = uart_getc();
		// Signal = 1 if recive 'S' char else signal = 0.
		if (chat == 'S') signal = 1;
		else signal = 0;		/* Using API function gpio_toggle(): */
		
		if (signal)
		{
			gpio_toggle(GPIOC,GPIO14); // if Signal = 1 toggle LED on PC14
		}else  gpio_toggle(GPIOC, GPIO13); // else toggle on board LED PC13

		delay_ms(1000);
		uart_putc(chat); // Echo chat variable
		uart_puts(" Hola man esto funka \0"); // test send un \0 terminated string
		 
	}

	return 0;
}

static void BP_setup(void)
{
	// Setup Blue pill clock
	rcc_clock_setup_in_hse_8mhz_out_72mhz(); //Blue Pill clock
	// Setup PC13 onboard LED
	rcc_periph_clock_enable(RCC_GPIOC);
	/* Set GPIO13 and GPIO14 (in GPIO port C) to 'output push-pull'. */
	gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL,GPIO13 | GPIO14);
	gpio_set(GPIOC,GPIO14); //External LED ON
}
