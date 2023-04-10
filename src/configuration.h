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

    /** @brief zones are the sensors */
    struct
    {
        char name[17];
	bool alarm;
	bool sabotage;
	bool inclusion;
	bool alarm_memory;
	bool sabotage_memory;
    } zones[32];

    /**
     * @brief partition are group of sensors. Bentel also
     * calls them areas.
     */
    struct
    {
        char name[17];
	bool alarm;
	bool armed;
    } partitions[8];

    struct
    {
        bool active;
    } digital_outputs[16];

    bool alarm_power;
    bool alarm_bpi;
    bool alarm_fuse;
    bool alarm_battery_low;
    bool alarm_telephone_line;
    bool alarm_default_codes;
    bool alarm_wireless;

    bool sabotage_partition;
    bool sabotage_fake_key;
    bool sabotage_bpi;
    bool sabotage_system;
    bool sabotage_jam;
    bool sabotage_wireless;

    bool siren_state;
};

int configuration_start (void * layer);

void configuration_stop (void * layer);

#endif /* _configuration_h_ */
