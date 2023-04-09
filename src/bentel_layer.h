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
    BENTEL_GET_ZONES_NAMES_0_3_REQUEST,
    BENTEL_GET_ZONES_NAMES_0_3_RESPONSE,
    BENTEL_GET_ZONES_NAMES_4_7_REQUEST,
    BENTEL_GET_ZONES_NAMES_4_7_RESPONSE,
    BENTEL_GET_ZONES_NAMES_8_11_REQUEST,
    BENTEL_GET_ZONES_NAMES_8_11_RESPONSE,
    BENTEL_GET_ZONES_NAMES_12_15_REQUEST,
    BENTEL_GET_ZONES_NAMES_12_15_RESPONSE,
    BENTEL_GET_ZONES_NAMES_16_19_REQUEST,
    BENTEL_GET_ZONES_NAMES_16_19_RESPONSE,
    BENTEL_GET_ZONES_NAMES_20_23_REQUEST,
    BENTEL_GET_ZONES_NAMES_20_23_RESPONSE,
    BENTEL_GET_ZONES_NAMES_24_27_REQUEST,
    BENTEL_GET_ZONES_NAMES_24_27_RESPONSE,
    BENTEL_GET_ZONES_NAMES_28_31_REQUEST,
    BENTEL_GET_ZONES_NAMES_28_31_RESPONSE,
    BENTEL_GET_PARTITIONS_NAMES_0_3_REQUEST,
    BENTEL_GET_PARTITIONS_NAMES_0_3_RESPONSE,
    BENTEL_GET_PARTITIONS_NAMES_4_7_REQUEST,
    BENTEL_GET_PARTITIONS_NAMES_4_7_RESPONSE,
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
        } get_zones_names_0_3_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[4];
        } get_zones_names_0_3_response;

        struct
        {
        } get_zones_names_4_7_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[4];
        } get_zones_names_4_7_response;

        struct
        {
        } get_zones_names_8_11_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[4];
        } get_zones_names_8_11_response;

        struct
        {
        } get_zones_names_12_15_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[4];
        } get_zones_names_12_15_response;

        struct
        {
        } get_zones_names_16_19_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[4];
        } get_zones_names_16_19_response;

        struct
        {
        } get_zones_names_20_23_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[4];
        } get_zones_names_20_23_response;

        struct
        {
        } get_zones_names_24_27_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[4];
        } get_zones_names_24_27_response;

        struct
        {
        } get_zones_names_28_31_request;

        struct
        {
            struct
	    {
                char name[17];
            } zones[4];
        } get_zones_names_28_31_response;

        struct
        {
        } get_partitions_names_0_3_request;

        struct
        {
            struct
	    {
                char name[17];
            } partitions[4];
        } get_partitions_names_0_3_response;

        struct
        {
        } get_partitions_names_4_7_request;

        struct
        {
            struct
	    {
                char name[17];
            } partitions[4];
        } get_partitions_names_4_7_response;
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
