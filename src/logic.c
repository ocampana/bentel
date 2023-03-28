#include <stdio.h>

#include "logic.h"
#include "configuration.h"

int handle_bentel_message (void * layer, void * message)
{
    bentel_message_t * bentel_message;
    extern configuration_t configuration;

    bentel_message = (bentel_message_t *) message;

    switch (bentel_message->message_type)
    {
        case BENTEL_GET_MODEL_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            configuration.fw_major =
                bentel_message->u.get_model_response.fw_major;
            configuration.fw_minor =
                bentel_message->u.get_model_response.fw_minor;
	    snprintf (configuration.model,
                      sizeof (configuration.model), "%s", 
                      bentel_message->u.get_model_response.model);

            sem_release (&configuration.semaphore);
            break;

        default:
            break;
    }

    return 0;
}
