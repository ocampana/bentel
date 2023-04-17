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

        case BENTEL_GET_STATUS_AND_FAULTS_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            configuration.zones[31].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_31;
            configuration.zones[30].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_30;
            configuration.zones[29].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_29;
            configuration.zones[28].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_28;
            configuration.zones[27].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_27;
            configuration.zones[26].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_26;
            configuration.zones[25].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_25;
            configuration.zones[24].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_24;

            configuration.zones[23].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_23;
            configuration.zones[22].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_22;
            configuration.zones[21].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_21;
            configuration.zones[20].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_20;
            configuration.zones[19].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_19;
            configuration.zones[18].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_18;
            configuration.zones[17].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_17;
            configuration.zones[16].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_16;

            configuration.zones[15].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_15;
            configuration.zones[14].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_14;
            configuration.zones[13].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_13;
            configuration.zones[12].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_12;
            configuration.zones[11].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_11;
            configuration.zones[10].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_10;
            configuration.zones[9].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_9;
            configuration.zones[8].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_8;

            configuration.zones[7].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_7;
            configuration.zones[6].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_6;
            configuration.zones[5].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_5;
            configuration.zones[4].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_4;
            configuration.zones[3].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_3;
            configuration.zones[2].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_2;
            configuration.zones[1].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_1;
            configuration.zones[0].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_zone_0;

            configuration.zones[31].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_31;
            configuration.zones[30].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_30;
            configuration.zones[29].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_29;
            configuration.zones[28].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_28;
            configuration.zones[27].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_27;
            configuration.zones[26].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_26;
            configuration.zones[25].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_25;
            configuration.zones[24].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_24;

            configuration.zones[23].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_23;
            configuration.zones[22].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_22;
            configuration.zones[21].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_21;
            configuration.zones[20].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_20;
            configuration.zones[19].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_19;
            configuration.zones[18].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_18;
            configuration.zones[17].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_17;
            configuration.zones[16].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_16;

            configuration.zones[15].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_15;
            configuration.zones[14].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_14;
            configuration.zones[13].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_13;
            configuration.zones[12].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_12;
            configuration.zones[11].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_11;
            configuration.zones[10].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_10;
            configuration.zones[9].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_9;
            configuration.zones[8].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_8;

            configuration.zones[7].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_7;
            configuration.zones[6].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_6;
            configuration.zones[5].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_5;
            configuration.zones[4].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_4;
            configuration.zones[3].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_3;
            configuration.zones[2].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_2;
            configuration.zones[1].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_1;
            configuration.zones[0].sabotage =
                bentel_message->u.get_status_and_faults_response.sabotage_zone_0;

            configuration.alarm_power =
                bentel_message->u.get_status_and_faults_response.alarm_power;
            configuration.alarm_bpi =
                bentel_message->u.get_status_and_faults_response.alarm_bpi;
            configuration.alarm_fuse =
                bentel_message->u.get_status_and_faults_response.alarm_fuse;
            configuration.alarm_battery_low =
                bentel_message->u.get_status_and_faults_response.alarm_battery_low;
            configuration.alarm_telephone_line =
                bentel_message->u.get_status_and_faults_response.alarm_telephone_line;
            configuration.alarm_default_codes =
                bentel_message->u.get_status_and_faults_response.alarm_default_codes;
            configuration.alarm_wireless =
                bentel_message->u.get_status_and_faults_response.alarm_wireless;

            configuration.partitions[7].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_partition_7;
            configuration.partitions[6].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_partition_6;
            configuration.partitions[5].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_partition_5;
            configuration.partitions[4].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_partition_4;
            configuration.partitions[3].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_partition_3;
            configuration.partitions[2].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_partition_2;
            configuration.partitions[1].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_partition_1;
            configuration.partitions[0].alarm =
                bentel_message->u.get_status_and_faults_response.alarm_partition_0;

            configuration.sabotage_partition =
                bentel_message->u.get_status_and_faults_response.sabotage_partition;
            configuration.sabotage_fake_key =
                bentel_message->u.get_status_and_faults_response.sabotage_fake_key;
            configuration.sabotage_bpi =
                bentel_message->u.get_status_and_faults_response.sabotage_bpi;
            configuration.sabotage_system =
                bentel_message->u.get_status_and_faults_response.sabotage_system;
            configuration.sabotage_jam =
                bentel_message->u.get_status_and_faults_response.sabotage_jam;
            configuration.sabotage_wireless =
                bentel_message->u.get_status_and_faults_response.sabotage_wireless;

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_ARMED_PARTITIONS_RESPONSE:
            sem_acquire_blocking (&configuration.semaphore);

            for (i = 0 ; i < 8 ; i++)
            {
                configuration.partitions[i].armed =
                    bentel_message->u.get_armed_partitions_response.partition_armed_state[i];
            }

            for (i = 0 ; i < 16 ; i++)
            {
                configuration.digital_outputs[i].active =
                    bentel_message->u.get_armed_partitions_response.digital_output_state[i];
            }

            configuration.siren_state =
                bentel_message->u.get_armed_partitions_response.siren_state;

            for (i = 0 ; i < 32 ; i++)
            {
                configuration.zones[i].inclusion =
                    bentel_message->u.get_armed_partitions_response.zone_inclusion[i];

                configuration.zones[i].alarm_memory =
                    bentel_message->u.get_armed_partitions_response.zone_alarm_memory[i];

                configuration.zones[i].sabotage_memory =
                    bentel_message->u.get_armed_partitions_response.zone_sabotage_memory[i];
            }

            sem_release (&configuration.semaphore);
            break;

        case BENTEL_GET_LOGGER_1_RESPONSE:
        case BENTEL_GET_LOGGER_2_RESPONSE:
        case BENTEL_GET_LOGGER_3_RESPONSE:
        case BENTEL_GET_LOGGER_4_RESPONSE:
        case BENTEL_GET_LOGGER_5_RESPONSE:
        case BENTEL_GET_LOGGER_6_RESPONSE:
        case BENTEL_GET_LOGGER_7_RESPONSE:
        case BENTEL_GET_LOGGER_8_RESPONSE:
        case BENTEL_GET_LOGGER_9_RESPONSE:
        case BENTEL_GET_LOGGER_10_RESPONSE:
        case BENTEL_GET_LOGGER_11_RESPONSE:
        case BENTEL_GET_LOGGER_12_RESPONSE:
        case BENTEL_GET_LOGGER_13_RESPONSE:
        case BENTEL_GET_LOGGER_14_RESPONSE:
        case BENTEL_GET_LOGGER_15_RESPONSE:
        case BENTEL_GET_LOGGER_16_RESPONSE:
        case BENTEL_GET_LOGGER_17_RESPONSE:
        case BENTEL_GET_LOGGER_18_RESPONSE:
        case BENTEL_GET_LOGGER_19_RESPONSE:
        case BENTEL_GET_LOGGER_20_RESPONSE:
        case BENTEL_GET_LOGGER_21_RESPONSE:
        case BENTEL_GET_LOGGER_22_RESPONSE:
        case BENTEL_GET_LOGGER_23_RESPONSE:
        case BENTEL_GET_LOGGER_24_RESPONSE:
        case BENTEL_GET_LOGGER_25_RESPONSE:
        case BENTEL_GET_LOGGER_26_RESPONSE:
        case BENTEL_GET_LOGGER_27_RESPONSE:
            break;

        case BENTEL_GET_LOGGER_28_RESPONSE:
            break;

        default:
            break;
    }

    return 0;
}
