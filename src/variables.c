#include "configuration.h"
#include "bentel_layer.h"
#include "uart_layer.h"

configuration_t configuration;

bentel_layer_ops_t bentel_layer_ops =
{
    .to_lower_layer_start_layer = uart_layer_start,
    .to_lower_layer_stop_layer = uart_layer_stop,
    .to_lower_layer_send_message = uart_layer_send_message,
};

bentel_layer_t bentel_layer =
{
    .ops = &bentel_layer_ops,
};

uart_layer_t uart_layer =
{
    .uart = uart1,
    .speed = 9600,
    .tx_pin = 4,
    .rx_pin = 5,
    .upper_layer = &bentel_layer,
};
