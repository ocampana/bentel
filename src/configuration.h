#ifndef _configuration_h_
#define _configuration_h_

#include <pico/sem.h>

#include <stdbool.h>

typedef struct _configuration_t configuration_t;

struct _configuration_t
{
    semaphore_t semaphore;
    char model[9];
    int fw_major;
    int fw_minor;

    struct
    {
        bool present;
        bool sabotage;
        bool alive;
    } readers[16];

    struct
    {
        bool present;
        bool sabotage;
        bool alive;
    } keyboards[8];
};

int configuration_start (void * layer);

void configuration_stop (void * layer);

#endif /* _configuration_h_ */
