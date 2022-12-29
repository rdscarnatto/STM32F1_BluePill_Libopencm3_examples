#include <uart_drv.h>

uint32_t uartw = 0;

void set_uart_TX_pin(uint32_t port, uint16_t gpios)
{
	gpio_set_mode(port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, gpios);
}

void set_uart_RX_pin(uint32_t port, uint16_t gpios)
{
	gpio_set_mode(port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, gpios);
}

void uart_init(unsigned long uart, uint32_t baud)
{
	if(uart == USART1)
	{
		rcc_periph_clock_enable(RCC_GPIOA);
		rcc_periph_clock_enable(RCC_USART1);
		// UART TX on PA9 (GPIO_USART1_TX)
		set_uart_TX_pin(GPIOA, GPIO_USART1_TX);
		set_uart_RX_pin(GPIOA, GPIO_USART1_RX);

	}else if (uart == USART2)
	{
		rcc_periph_clock_enable(RCC_GPIOA);
		rcc_periph_clock_enable(RCC_USART2);
		set_uart_TX_pin(GPIOA, GPIO_USART2_TX);
		set_uart_RX_pin(GPIOA, GPIO_USART2_RX);		

	}else if(uart == USART3)
	{
		rcc_periph_clock_enable(RCC_GPIOB);
		rcc_periph_clock_enable(RCC_USART3);
		set_uart_TX_pin(GPIOB, GPIO_USART3_TX);
		set_uart_RX_pin(GPIOB, GPIO_USART3_RX);			

	}
	//setup commons parameters for default
	usart_set_baudrate(uart, baud);
	usart_set_databits(uart, 8);
	usart_set_stopbits(uart, 1);
	usart_set_mode(uart, USART_MODE_TX_RX);
	usart_set_parity(uart, USART_PARITY_NONE);
	usart_set_flow_control(uart, USART_FLOWCONTROL_NONE);
	usart_enable(uart);
	uartw = uart;
}

void uart_putc(uint8_t ch)
{
	usart_send_blocking(uartw, ch);
}

void uart_puts(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		uart_putc(str[i]);
		i++;
	}
}
char uart_getc()
{
	return (char)(usart_recv(uartw));
}