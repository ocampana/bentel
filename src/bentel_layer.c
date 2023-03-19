#include <pico/stdlib.h>
#include <string.h>

#include "bentel_layer.h"

int
bentel_layer_start (void * layer)
{
    int i;
    bentel_layer_t *bentel_layer;

    bentel_layer = (bentel_layer_t *) layer;

    memset (bentel_layer->buffer, 0, sizeof (bentel_layer->buffer));

    if (bentel_layer->lower_layer != NULL &&
        bentel_layer->ops != NULL &&
	bentel_layer->ops->to_lower_layer_start_layer != NULL)
	    i = bentel_layer->ops->to_lower_layer_start_layer (bentel_layer->lower_layer);

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
	    bentel_layer->ops->to_lower_layer_stop_layer (bentel_layer->lower_layer);
}

int
bentel_layer_send_message (void * layer, void * message)
{
    int i;
    bentel_layer_t *bentel_layer;
    bentel_message_t *bentel_message;

    bentel_layer = (bentel_layer_t *) layer;
    bentel_message = (bentel_message_t *) message;

    if (bentel_layer->lower_layer != NULL &&
        bentel_layer->ops != NULL &&
	bentel_layer->ops->to_lower_layer_send_message != NULL)
	    i = bentel_layer->ops->to_lower_layer_send_message (bentel_layer->lower_layer, NULL, 0);

    return i;
}
