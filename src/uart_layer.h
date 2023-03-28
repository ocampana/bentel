#ifndef _uart_layer_h_
#define _uart_layer_h_

#include <stdbool.h>

#include <hardware/uart.h>

typedef struct _uart_layer_ops_t uart_layer_ops_t;

struct _uart_layer_ops_t
{
    void (*to_upper_layer_received_message) (void * layer, void * message, int len);
};

typedef struct _uart_layer_t uart_layer_t;

struct _uart_layer_t
{
    uart_inst_t *uart;
    int speed;
    int tx_pin;
    int rx_pin;
    bool cts;
    bool rts;
    int data_bits;
    int stop_bits;
    int parity;
    void * upper_layer;
    uart_layer_ops_t *ops;
};

int uart_layer_start (void * layer);

void uart_layer_stop (void * layer);

int uart_layer_send_message (void * layer, void * message, int len);

#endif /* _uart_layer_h_ */
