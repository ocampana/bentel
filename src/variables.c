#include "configuration.h"
#include "bentel_layer.h"
#include "state_machine.h"
#include "uart_layer.h"

configuration_t configuration =
{
    .model = "",
    .fw_major = 0,
    .fw_minor = 0,
};

state_machine_t state_machine;

/* forward declaration of uart_layer */
uart_layer_t uart_layer;

bentel_layer_ops_t bentel_layer_ops =
{
    .to_lower_layer_start_layer = uart_layer_start,
    .to_lower_layer_stop_layer = uart_layer_stop,
    .to_lower_layer_send_message = uart_layer_send_message,
};

bentel_layer_t bentel_layer =
{
    .ops = &bentel_layer_ops,
    .lower_layer = &uart_layer,
};

uart_layer_ops_t uart_layer_ops =
{
    .to_upper_layer_received_message = &bentel_layer_received_message,
};

uart_layer_t uart_layer =
{
    .uart = uart1,
    .speed = 9600,
    .tx_pin = 4,
    .rx_pin = 5,
    .cts = false,
    .rts = false,
    .upper_layer = &bentel_layer,
    .ops = &uart_layer_ops,
};
