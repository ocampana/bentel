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

        case BENTEL_GET_ZONES_NAMES_0_3_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.zones[i].name,
                          sizeof (configuration.zones[i].name), "%s",
                          bentel_message->u.get_zones_names_0_3_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ZONES_NAMES_4_7_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.zones[i + 4].name,
                          sizeof (configuration.zones[i + 4].name), "%s",
                          bentel_message->u.get_zones_names_4_7_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ZONES_NAMES_8_11_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.zones[i + 8].name,
                          sizeof (configuration.zones[i + 8].name), "%s",
                          bentel_message->u.get_zones_names_8_11_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ZONES_NAMES_12_15_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.zones[i + 12].name,
                          sizeof (configuration.zones[i + 12].name), "%s",
                          bentel_message->u.get_zones_names_12_15_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ZONES_NAMES_16_19_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.zones[i + 16].name,
                          sizeof (configuration.zones[i + 16].name), "%s",
                          bentel_message->u.get_zones_names_16_19_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ZONES_NAMES_20_23_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.zones[i + 20].name,
                          sizeof (configuration.zones[i + 20].name), "%s",
                          bentel_message->u.get_zones_names_20_23_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ZONES_NAMES_24_27_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.zones[i + 24].name,
                          sizeof (configuration.zones[i + 24].name), "%s",
                          bentel_message->u.get_zones_names_24_27_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ZONES_NAMES_28_31_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.zones[i + 28].name,
                          sizeof (configuration.zones[i + 28].name), "%s",
                          bentel_message->u.get_zones_names_28_31_response.zones[i].name);
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_PARTITIONS_NAMES_0_3_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.partitions[i].name,
                          sizeof (configuration.partitions[i].name), "%s",
                          bentel_message->u.get_partitions_names_0_3_response.partitions[i].name);
            }


            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_PARTITIONS_NAMES_4_7_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (configuration.partitions[i + 4].name,
                          sizeof (configuration.partitions[i + 4].name), "%s",
                          bentel_message->u.get_partitions_names_4_7_response.partitions[i].name);
            }


            sem_release (&configuration.semaphore);
            break;

        default:
            break;
    }

    return 0;
}
