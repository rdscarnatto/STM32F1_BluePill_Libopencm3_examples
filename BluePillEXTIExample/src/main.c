#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>

volatile uint32_t mills;
int signal = 0;

//void sys_tick_handler(void);
static void gpio_setup(void);
void systick_init(void);


void delay_ms(uint32_t ms)
{
	uint32_t lm = mills;
	while ((mills-lm) < ms);
	
}
static void exti_setup(void)
{
    /* Enable GPIOA and AFIO clock. */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_AFIO);

/* Enable EXTI0 interrupt. */
    nvic_enable_irq(NVIC_EXTI0_IRQ);

/* Set GPIO12 (in GPIO port B) to input  */
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT,GPIO_CNF_INPUT_FLOAT, GPIO0);

/* Configure the EXTI subsystem. */
    exti_select_source(EXTI0,GPIOA);
    exti_set_trigger(EXTI0, EXTI_TRIGGER_RISING);
    exti_enable_request(EXTI0);
}




int main(void)
{
	//int i;
	gpio_setup();
	// Enable systick timers
	systick_init();
	/* Blink the LED on the board. */
	exti_setup();
	
	while (1) {
		/* Using API function gpio_toggle(): */
		if (signal) //Ojo gpio_get Read 16 bit
		{
			gpio_toggle(GPIOC,GPIO14);
		}else  gpio_toggle(GPIOC, GPIO13);	/* LED on/off */
		
		delay_ms(1000);
		 
	}

	return 0;
}

void sys_tick_handler()
{
	mills++;
}

static void gpio_setup(void)
{
	/* Enable GPIO clock. */
	/* Using API functions: */
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	//rcc_periph_clock_enable(RCC_GPIOA);
	//rcc_periph_clock_enable(RCC_GPIOA);
	//rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOC);
	//rcc_periph_clock_enable(RCC_GPIOA);
	/* Set pin to 'output push-pull'. */
	/* Using API functions: */
	//gpio_set_mode(GPIOA,GPIO_MODE_INPUT,GPIO_CNF_INPUT_FLOAT,GPIO0);
	/* Set GPIO13 and GPIO14 (in GPIO port C) to 'output push-pull'. */
	gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL,GPIO13 | GPIO14);
	gpio_set(GPIOC,GPIO14); //External LED ON

}

void systick_init()
{
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8); // 72Mhz/8 = 9M
	systick_set_reload(8999); //9M / 9000
	systick_counter_enable();
	systick_interrupt_enable();
}

void exti0_isr()
{
    exti_reset_request(EXTI0);
    if (signal == 0)
	{
		signal =1;
	}else{
		signal = 0;
	}
}
