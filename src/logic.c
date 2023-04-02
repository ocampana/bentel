#include <stdio.h>

#include "logic.h"
#include "configuration.h"

int handle_bentel_message (void * layer, void * message)
{
    int i;
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

        case BENTEL_GET_PERIPHERALS_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 16 ; i++)
            {
                configuration.readers[i].present =
                    bentel_message->u.get_peripherals_response.readers[i].present;
                configuration.readers[i].sabotage =
                    bentel_message->u.get_peripherals_response.readers[i].sabotage;
                configuration.readers[i].alive =
                    bentel_message->u.get_peripherals_response.readers[i].alive;
            }

            for (i = 0 ; i < 8 ; i++)
            {
                configuration.keyboards[i].present =
                    bentel_message->u.get_peripherals_response.keyboards[i].present;
                configuration.keyboards[i].sabotage =
                    bentel_message->u.get_peripherals_response.keyboards[i].sabotage;
                configuration.keyboards[i].alive =
                    bentel_message->u.get_peripherals_response.keyboards[i].alive;
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ZONES_NAMES_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 32 ; i++)
            {
                snprintf (configuration.zones[i].name,
                          sizeof (configuration.zones[i].name), "%s", 
                          bentel_message->u.get_zones_names_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_PARTITIONS_NAMES_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 8 ; i++)
            {
                snprintf (configuration.partitions[i].name,
                          sizeof (configuration.partitions[i].name), "%s", 
                          bentel_message->u.get_partitions_names_response.partitions[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        default:
            break;
    }

    return 0;
}
