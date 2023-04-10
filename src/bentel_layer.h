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
    BENTEL_GET_STATUS_AND_FAULTS_REQUEST,
    BENTEL_GET_STATUS_AND_FAULTS_RESPONSE,
    BENTEL_GET_ARMED_PARTITIONS_REQUEST,
    BENTEL_GET_ARMED_PARTITIONS_RESPONSE,
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

        struct
        {
        } get_status_and_faults_request;

        struct
        {
            bool alarm_zone_0;
            bool alarm_zone_1;
            bool alarm_zone_2;
            bool alarm_zone_3;
            bool alarm_zone_4;
            bool alarm_zone_5;
            bool alarm_zone_6;
            bool alarm_zone_7;
            bool alarm_zone_8;
            bool alarm_zone_9;
            bool alarm_zone_10;
            bool alarm_zone_11;
            bool alarm_zone_12;
            bool alarm_zone_13;
            bool alarm_zone_14;
            bool alarm_zone_15;
            bool alarm_zone_16;
            bool alarm_zone_17;
            bool alarm_zone_18;
            bool alarm_zone_19;
            bool alarm_zone_20;
            bool alarm_zone_21;
            bool alarm_zone_22;
            bool alarm_zone_23;
            bool alarm_zone_24;
            bool alarm_zone_25;
            bool alarm_zone_26;
            bool alarm_zone_27;
            bool alarm_zone_28;
            bool alarm_zone_29;
            bool alarm_zone_30;
            bool alarm_zone_31;

            bool sabotage_zone_0;
            bool sabotage_zone_1;
            bool sabotage_zone_2;
            bool sabotage_zone_3;
            bool sabotage_zone_4;
            bool sabotage_zone_5;
            bool sabotage_zone_6;
            bool sabotage_zone_7;
            bool sabotage_zone_8;
            bool sabotage_zone_9;
            bool sabotage_zone_10;
            bool sabotage_zone_11;
            bool sabotage_zone_12;
            bool sabotage_zone_13;
            bool sabotage_zone_14;
            bool sabotage_zone_15;
            bool sabotage_zone_16;
            bool sabotage_zone_17;
            bool sabotage_zone_18;
            bool sabotage_zone_19;
            bool sabotage_zone_20;
            bool sabotage_zone_21;
            bool sabotage_zone_22;
            bool sabotage_zone_23;
            bool sabotage_zone_24;
            bool sabotage_zone_25;
            bool sabotage_zone_26;
            bool sabotage_zone_27;
            bool sabotage_zone_28;
            bool sabotage_zone_29;
            bool sabotage_zone_30;
            bool sabotage_zone_31;

            bool alarm_power;
            bool alarm_bpi;
            bool alarm_fuse;
            bool alarm_battery_low;
            bool alarm_telephone_line;
            bool alarm_default_codes;
            bool alarm_wireless;

            bool alarm_partition_0;
            bool alarm_partition_1;
            bool alarm_partition_2;
            bool alarm_partition_3;
            bool alarm_partition_4;
            bool alarm_partition_5;
            bool alarm_partition_6;
            bool alarm_partition_7;

            bool sabotage_partition;
            bool sabotage_fake_key;
            bool sabotage_bpi;
            bool sabotage_system;
            bool sabotage_jam;
            bool sabotage_wireless;
        } get_status_and_faults_response;

        struct
        {
        } get_armed_partitions_request;

        struct
        {
            bool partition_armed_state[8];
            bool siren_state;
            bool digital_output_state[16];
            bool zone_inclusion[32];
            bool zone_alarm_memory[32];
            bool zone_sabotage_memory[32];
        } get_armed_partitions_response;

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
