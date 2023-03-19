#include <pico/stdlib.h>
#include <string.h>

#include "bentel_layer.h"
#include "bentel_layer_private.h"

int
bentel_layer_start (void * layer)
{
    int i;
    bentel_layer_t *bentel_layer;

    bentel_layer = (bentel_layer_t *) layer;

    memset (bentel_layer->buffer, 0, sizeof (bentel_layer->buffer));
    bentel_layer->buffer_index = 0;

    if (bentel_layer->lower_layer != NULL &&
        bentel_layer->ops != NULL &&
	bentel_layer->ops->to_lower_layer_start_layer != NULL)
    {
        i = bentel_layer->ops->to_lower_layer_start_layer
            (bentel_layer->lower_layer);
    }

    return i;
}

void
bentel_layer_stop (void * layer)
{
    bentel_layer_t *bentel_layer;

    bentel_layer = (bentel_layer_t *) layer;

    if (bentel_layer->lower_layer != NULL &&
        bentel_layer->ops != NULL &&
	bentel_layer->ops->to_lower_layer_stop_layer != NULL)
    {
        bentel_layer->ops->to_lower_layer_stop_layer
            (bentel_layer->lower_layer);
    }
}

int
bentel_layer_send_message (void * layer, void * message)
{
    int i = 0;
    bentel_layer_t *bentel_layer;
    bentel_message_t *bentel_message;

    bentel_layer = (bentel_layer_t *) layer;
    bentel_message = (bentel_message_t *) message;

    if (bentel_layer->lower_layer != NULL &&
        bentel_layer->ops != NULL &&
	bentel_layer->ops->to_lower_layer_send_message != NULL)
    {
        int len;
        unsigned char buffer[128];

        bentel_message_encode (bentel_message, buffer, 128);

        i = bentel_layer->ops->to_lower_layer_send_message
            (bentel_layer->lower_layer, buffer, len);
    }

    return i;
}

void
bentel_layer_received_message (void * layer, void * message, int len)
{
    int i;
    bentel_layer_t *bentel_layer;
    unsigned char * buffer;
    bentel_message_t bentel_message;

    bentel_layer = (bentel_layer_t *) layer;
    buffer = (unsigned char *) message;

    i = (bentel_layer->buffer_index + len) % 128;

    memcpy (&(bentel_layer->buffer[bentel_layer->buffer_index]), buffer, i);

    memset (&bentel_message, 0, sizeof (bentel_message));

    if (bentel_message_decode (&bentel_message, buffer, len))
    {
        if (bentel_layer->upper_layer != NULL &&
            bentel_layer->ops != NULL &&
	    bentel_layer->ops->to_upper_layer_received_message != NULL)
        {
            i = bentel_layer->ops->to_upper_layer_received_message
                (bentel_layer->upper_layer, &bentel_message);
        }

        /* no matter if we move or not, we empty the buffer */
	memset (bentel_layer->buffer, 0, sizeof (bentel_layer->buffer));
	bentel_layer->buffer_index = 0;
    }
}
