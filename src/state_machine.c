#include "state_machine.h"
#include "bentel_layer.h"

#include <string.h>

extern bentel_layer_t bentel_layer;

void
state_machine_init (state_machine_t *machine)
{
    machine->state = STATE_START;
}

void
state_machine_next (state_machine_t * machine)
{
    bentel_message_t bentel_message;

    switch (machine->state)
    {
        case STATE_START:
            machine->state = STATE_REQUEST_MODEL;
            break;

        case STATE_REQUEST_MODEL:
            memset (&bentel_message, 0, sizeof (bentel_message_t));

            bentel_message.message_type = BENTEL_GET_MODEL_REQUEST;

	    bentel_layer_send_message (&bentel_layer, &bentel_message);

            break;

        default:
            break;
    }
}
