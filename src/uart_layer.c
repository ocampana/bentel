#include "uart_layer.h"

#include <pico/stdlib.h>
#include <hardware/uart.h>

#include <stdio.h>

void
__time_critical_func(on_uart_rx)(void)
{
    extern uart_layer_t uart_layer;

    if (uart_layer.upper_layer != NULL &&
        uart_layer.ops != NULL &&
        uart_layer.ops->to_upper_layer_received_message != NULL)
    {
        while (uart_is_readable (uart_layer.uart))
        {
            uint8_t ch = uart_getc (uart_layer.uart);

            uart_layer.ops->to_upper_layer_received_message (uart_layer.upper_layer,
                                                             &ch, 1);
        }
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

    uart_set_format (uart_layer->uart, uart_layer->data_bits,
                     uart_layer->stop_bits, uart_layer->parity);

    uart_set_fifo_enabled (uart_layer->uart, true);

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
    const uint8_t * buffer;

    uart_layer = (uart_layer_t *) layer;
    buffer = (const uint8_t *) message;

    uart_write_blocking (uart_layer->uart, buffer, len);

    return 0;
}
