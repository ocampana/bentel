#include "uart_layer.h"

#include <pico/stdlib.h>
#include <hardware/uart.h>

int
uart_layer_start (void * layer)
{
    uart_layer_t *uart_layer;

    uart_layer = (uart_layer_t *) layer;

    uart_init (uart_layer->uart, uart_layer->speed);

    gpio_set_function (uart_layer->tx_pin, GPIO_FUNC_UART);
    gpio_set_function (uart_layer->rx_pin, GPIO_FUNC_UART);

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
    return -1;
}
