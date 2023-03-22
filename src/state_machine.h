#ifndef _state_machine_h
#define _state_machine_h

typedef enum _state_t state_t;

enum _state_t
{
    STATE_START = 1,
    STATE_REQUEST_MODEL,
};

typedef struct _state_machine_t state_machine_t;

struct _state_machine_t
{
    state_t state;
};

void state_machine_next (state_machine_t * machine);

void state_machine_init (state_machine_t *machine);

#endif /* _state_machine_h */
