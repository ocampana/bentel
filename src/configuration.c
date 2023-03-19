#include "configuration.h"

int configuration_start (void * layer)
{
    configuration_t * configuration;

    configuration = (configuration_t *) layer;

    sem_init(&configuration->semaphore, 1, 1);

    return 0;
}

void configuration_stop (void * layer)
{
    configuration_t * configuration;

    configuration = (configuration_t *) layer;
}
