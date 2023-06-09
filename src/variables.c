#include "configuration.h"
#include "bentel_layer.h"
#include "state_machine.h"
#include "uart_layer.h"
#include "logic.h"

configuration_t configuration =
{
    .model = "",
    .fw_major = 0,
    .fw_minor = 0,
    .readers =
    {
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
    },

    .keyboards =
    {
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
        {
            .present = false,
            .sabotage = false,
            .alive = false,
        },
    },

    .zones =
    {
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
        {
            .name = "",
            .alarm = false,
            .sabotage = false,
	    .inclusion = false,
	    .alarm_memory = false,
	    .sabotage_memory = false,
        },
    },

    .partitions =
    {
        {
            .name = "",
            .alarm = false,
	    .armed = false,
        },
        {
            .name = "",
            .alarm = false,
	    .armed = false,
        },
        {
            .name = "",
            .alarm = false,
	    .armed = false,
        },
        {
            .name = "",
            .alarm = false,
	    .armed = false,
        },
        {
            .name = "",
            .alarm = false,
	    .armed = false,
        },
        {
            .name = "",
            .alarm = false,
	    .armed = false,
        },
        {
            .name = "",
            .alarm = false,
	    .armed = false,
        },
        {
            .name = "",
            .alarm = false,
	    .armed = false,
        },
    },

    .alarm_power = false,
    .alarm_bpi = false,
    .alarm_fuse = false,
    .alarm_battery_low = false,
    .alarm_telephone_line = false,
    .alarm_default_codes = false,
    .alarm_wireless = false,

    .sabotage_partition = false,
    .sabotage_fake_key = false,
    .sabotage_bpi = false,
    .sabotage_system = false,
    .sabotage_jam = false,
    .sabotage_wireless = false,

    .siren_state = false,
};

state_machine_t state_machine;

/* forward declaration of uart_layer */
uart_layer_t uart_layer;

bentel_layer_ops_t bentel_layer_ops =
{
    .to_lower_layer_start_layer = uart_layer_start,
    .to_lower_layer_stop_layer = uart_layer_stop,
    .to_lower_layer_send_message = uart_layer_send_message,
    .to_upper_layer_received_message = handle_bentel_message,
};

bentel_layer_t bentel_layer =
{
    .ops = &bentel_layer_ops,
    .lower_layer = &uart_layer,
    .upper_layer = &configuration,
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
    .data_bits = 8,
    .stop_bits = 1,
    .parity = UART_PARITY_NONE,
    .upper_layer = &bentel_layer,
    .ops = &uart_layer_ops,
};
