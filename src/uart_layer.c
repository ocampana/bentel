#include "uart_layer.h"

#include "picow_http/http.h"

#include <pico/stdlib.h>
#include <hardware/uart.h>

void on_uart_rx()
{
    extern uart_layer_t uart_layer;

    while (uart_is_readable (uart_layer.uart))
    {
        uint8_t ch = uart_getc (uart_layer.uart);

        HTTP_LOG_ERROR("on_uart_rx: %c", ch);

	if (uart_layer.upper_layer != NULL &&
            uart_layer.ops != NULL &&
            uart_layer.ops->to_upper_layer_received_message != NULL)
            uart_layer.ops->to_upper_layer_received_message (&uart_layer.upper_layer, &ch, 1);
    }
}

int
uart_layer_start (void * layer)
{
    uart_layer_t *uart_layer;

    uart_layer = (uart_layer_t *) layer;

    uart_init (uart_layer->uart, uart_layer->speed);

    gpio_set_function (uart_layer->tx_pin, GPIO_FUNC_UART);
    gpio_set_function (uart_layer->rx_pin, GPIO_FUNC_UART);

    uart_set_baudrate(uart_layer->uart, uart_layer->speed);

    uart_set_hw_flow (uart_layer->uart, uart_layer->cts, uart_layer->rts);

    uart_set_fifo_enabled (uart_layer->uart, false);

    if (uart_layer->uart == uart0)
    {
        irq_set_exclusive_handler (UART0_IRQ, on_uart_rx);
        irq_set_enabled (UART0_IRQ, true);
    }
    else
    {
        irq_set_exclusive_handler (UART1_IRQ, on_uart_rx);
        irq_set_enabled (UART1_IRQ, true);
    }

    uart_set_irq_enables (uart_layer->uart, true, false);

    return 0;
}

void
uart_layer_stop (void * layer)
{
    uart_layer_t *uart_layer;

    uart_layer = (uart_layer_t *) layer;
}

int
uart_layer_send_message (void * layer, void * message, int len)
{
    int i;
    uart_layer_t *uart_layer;
    unsigned char * buffer;

    uart_layer = (uart_layer_t *) layer;
    buffer = (unsigned char *) message;

    for (i = 0 ; i < len ; i++)
    {
        if (uart_is_writable (uart_layer->uart))
        {
            uart_putc (uart_layer->uart, buffer[i]);
        }
	else
        {
            return -1;
        }
    }

    return 0;
}
