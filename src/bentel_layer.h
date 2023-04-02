#ifndef _bentel_layer_h_
#define _bentel_layer_h_

#include <stdbool.h>

typedef enum _bentel_message_type_t bentel_message_type_t;

enum _bentel_message_type_t
{
    BENTEL_GET_MODEL_REQUEST = 1,
    BENTEL_GET_MODEL_RESPONSE,
    BENTEL_GET_PERIPHERALS_REQUEST,
    BENTEL_GET_PERIPHERALS_RESPONSE,
    BENTEL_GET_ZONES_NAMES_REQUEST,
    BENTEL_GET_ZONES_NAMES_RESPONSE,
    BENTEL_GET_PARTITIONS_NAMES_REQUEST,
    BENTEL_GET_PARTITIONS_NAMES_RESPONSE,
};

typedef struct _bentel_message_t bentel_message_t;

struct _bentel_message_t
{
    bentel_message_type_t message_type;

    union
    {
        struct
        {
        } get_model_request;

        struct
        {
            char model[9];
	    int fw_major;
	    int fw_minor;
        } get_model_response;

        struct
        {
        } get_peripherals_request;

        struct
        {
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
        } get_peripherals_response;

        struct
        {
        } get_zones_names_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[32];
        } get_zones_names_response;

        struct
        {
        } get_partitions_names_request;

        struct
        {
            struct
	    {
                char name[17];
            } partitions[8];
        } get_partitions_names_response;
    } u;
};

typedef struct _bentel_layer_ops_t bentel_layer_ops_t;

struct _bentel_layer_ops_t
{
    int (*to_lower_layer_start_layer) (void * layer);
    void (*to_lower_layer_stop_layer) (void * layer);
    int (*to_lower_layer_send_message) (void * layer, void * message, int len);
    int (*to_upper_layer_received_message) (void * layer, void * message);
};

typedef struct _bentel_layer_t bentel_layer_t;

struct _bentel_layer_t
{
    void * upper_layer;
    void * lower_layer;
    bentel_layer_ops_t * ops;

    unsigned char buffer[524];
    int buffer_index;
};

int bentel_layer_start (void * layer);

void bentel_layer_stop (void * layer);

int bentel_layer_send_message (void * layer, void * message);

void bentel_layer_received_message (void * layer, void * message, int len);

#endif /* _bentel_layer_h_ */
