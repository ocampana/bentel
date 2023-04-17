#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include <ctype.h>

#include "bentel_layer.h"
#include "bentel_layer_private.h"

//#include "hardware/uart.h"

static void
right_strip (unsigned char * c, int len)
{
    int i;

    for (i = len ; i >= 0 ; i--)
    {
        if (isspace (c[i]) == 0)
        {
            return;
        }

        c[i] = 0;
    }
}

static unsigned char
evaluate_checksum (unsigned char * buffer, int len)
{
    int i;
    unsigned char to_return = 0;

    for (i = 0 ; i < len ; i++) 
    {
        to_return = (to_return + buffer[i]) % 256;
    }

    return to_return;
}

int
bentel_message_encode (bentel_message_t * bentel_message,
                       unsigned char * buffer, int len)
{
    int to_return = 0;

    memset (buffer, 0, len);

    switch (bentel_message->message_type)
    {
        case BENTEL_GET_MODEL_REQUEST:
            /* -> f0 00 00 0b 00 fb */
            buffer[0] = 0xf0;
            buffer[1] = 0x00;
            buffer[2] = 0x00;
            buffer[3] = 0x0b;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_PERIPHERALS_REQUEST:
            /* -> f0 09 f0 0b 00 fb */
            buffer[0] = 0xf0;
            buffer[1] = 0x09;
            buffer[2] = 0xf0;
            buffer[3] = 0x0b;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ZONES_NAMES_0_3_REQUEST:
            /* -> f0 b0 19 3f 00 f8 */
            buffer[0] = 0xf0;
            buffer[1] = 0xb0;
            buffer[2] = 0x19;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ZONES_NAMES_4_7_REQUEST:
            /* -> f0 f0 19 3f 00 38 */
            buffer[0] = 0xf0;
            buffer[1] = 0xf0;
            buffer[2] = 0x19;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ZONES_NAMES_8_11_REQUEST:
            /* -> f0 30 1a 3f 00 79 */
            buffer[0] = 0xf0;
            buffer[1] = 0x30;
            buffer[2] = 0x1a;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ZONES_NAMES_12_15_REQUEST:
            /* -> f0 70 1a 3f 00 b9 */
            buffer[0] = 0xf0;
            buffer[1] = 0x70;
            buffer[2] = 0x1a;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ZONES_NAMES_16_19_REQUEST:
            /* -> f0 b0 1a 3f 00 f9 */
            buffer[0] = 0xf0;
            buffer[1] = 0xb0;
            buffer[2] = 0x1a;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ZONES_NAMES_20_23_REQUEST:
            /* -> f0 f0 1a 3f 00 39 */
            buffer[0] = 0xf0;
            buffer[1] = 0xf0;
            buffer[2] = 0x1a;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ZONES_NAMES_24_27_REQUEST:
            /* -> f0 30 1b 3f 00 7a */
            buffer[0] = 0xf0;
            buffer[1] = 0x30;
            buffer[2] = 0x1b;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ZONES_NAMES_28_31_REQUEST:
            /* -> f0 70 1b 3f 00 ba */
            buffer[0] = 0xf0;
            buffer[1] = 0x70;
            buffer[2] = 0x1b;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_PARTITIONS_NAMES_0_3_REQUEST:
            /* -> f0 50 17 3f 00 96 */
            buffer[0] = 0xf0;
            buffer[1] = 0x50;
            buffer[2] = 0x17;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_PARTITIONS_NAMES_4_7_REQUEST:
            /* -> f0 90 17 3f 00 d6 */
            buffer[0] = 0xf0;
            buffer[1] = 0x90;
            buffer[2] = 0x17;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_STATUS_AND_FAULTS_REQUEST:
            /* -> f0 04 f0 0a 00 ee */
            buffer[0] = 0xf0;
            buffer[1] = 0x04;
            buffer[2] = 0xf0;
            buffer[3] = 0x0a;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_ARMED_PARTITIONS_REQUEST:
            /* -> f0 02 15 12 00 19 */
            buffer[0] = 0xf0;
            buffer[1] = 0x02;
            buffer[2] = 0x15;
            buffer[3] = 0x12;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_1_REQUEST:
            /* -> f0 3d 0d 3f 00 79 */
            buffer[0] = 0xf0;
            buffer[1] = 0x3d;
            buffer[2] = 0x0d;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_2_REQUEST:
            /* -> f0 7d 0d 3f 00 b9 */
            buffer[0] = 0xf0;
            buffer[1] = 0x7d;
            buffer[2] = 0x0d;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_3_REQUEST:
            /* -> f0 bd 0d 3f 00 f9 */
            buffer[0] = 0xf0;
            buffer[1] = 0xbd;
            buffer[2] = 0x0d;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_4_REQUEST:
            /* -> f0 fd 0d 3f 00 39 */
            buffer[0] = 0xf0;
            buffer[1] = 0xfd;
            buffer[2] = 0x0d;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_5_REQUEST:
            /* -> f0 3d 0e 3f 00 7a */
            buffer[0] = 0xf0;
            buffer[1] = 0x3d;
            buffer[2] = 0x0e;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_6_REQUEST:
            /* -> f0 7d 0e 3f 00 ba */
            buffer[0] = 0xf0;
            buffer[1] = 0x7d;
            buffer[2] = 0x0e;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_7_REQUEST:
            /* -> f0 bd 0e 3f 00 fa */
            buffer[0] = 0xf0;
            buffer[1] = 0xbd;
            buffer[2] = 0x0e;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_8_REQUEST:
            /* -> f0 fd 0e 3f 00 3a */
            buffer[0] = 0xf0;
            buffer[1] = 0xfd;
            buffer[2] = 0x0e;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_9_REQUEST:
            /* -> f0 3d 0f 3f 00 7b */
            buffer[0] = 0xf0;
            buffer[1] = 0x3d;
            buffer[2] = 0x0f;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_10_REQUEST:
            /* -> f0 7d 0f 3f 00 bb */
            buffer[0] = 0xf0;
            buffer[1] = 0x7d;
            buffer[2] = 0x0f;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_11_REQUEST:
            /* -> f0 bd 0f 3f 00 fb */
            buffer[0] = 0xf0;
            buffer[1] = 0xbd;
            buffer[2] = 0x0f;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_12_REQUEST:
            /* -> f0 fd 0f 3f 00 3b */
            buffer[0] = 0xf0;
            buffer[1] = 0xfd;
            buffer[2] = 0x0f;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_13_REQUEST:
            /* -> f0 3d 10 3f 00 7c */
            buffer[0] = 0xf0;
            buffer[1] = 0x3d;
            buffer[2] = 0x10;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_14_REQUEST:
            /* -> f0 7d 10 3f 00 bc */
            buffer[0] = 0xf0;
            buffer[1] = 0x7d;
            buffer[2] = 0x10;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_15_REQUEST:
            /* -> f0 bd 10 3f 00 fc */
            buffer[0] = 0xf0;
            buffer[1] = 0xbd;
            buffer[2] = 0x10;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_16_REQUEST:
            /* -> f0 fd 10 3f 00 3c */
            buffer[0] = 0xf0;
            buffer[1] = 0xfd;
            buffer[2] = 0x10;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_17_REQUEST:
            /* -> f0 3d 11 3f 00 7d */
            buffer[0] = 0xf0;
            buffer[1] = 0x3d;
            buffer[2] = 0x11;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_18_REQUEST:
            /* -> f0 7d 11 3f 00 bd */
            buffer[0] = 0xf0;
            buffer[1] = 0x7d;
            buffer[2] = 0x11;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_19_REQUEST:
            /* -> f0 bd 11 3f 00 fd */
            buffer[0] = 0xf0;
            buffer[1] = 0xbd;
            buffer[2] = 0x11;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_20_REQUEST:
            /* -> f0 fd 11 3f 00 3d */
            buffer[0] = 0xf0;
            buffer[1] = 0xfd;
            buffer[2] = 0x11;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_21_REQUEST:
            /* -> f0 3d 12 3f 00 7e */
            buffer[0] = 0xf0;
            buffer[1] = 0x3d;
            buffer[2] = 0x12;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_22_REQUEST:
            /* -> f0 7d 12 3f 00 be */
            buffer[0] = 0xf0;
            buffer[1] = 0x7d;
            buffer[2] = 0x12;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_23_REQUEST:
            /* -> f0 bd 12 3f 00 fe */
            buffer[0] = 0xf0;
            buffer[1] = 0xbd;
            buffer[2] = 0x12;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        case BENTEL_GET_LOGGER_24_REQUEST:
            /* -> f0 fd 12 3f 00 3e */
            buffer[0] = 0xf0;
            buffer[1] = 0xfd;
            buffer[2] = 0x12;
            buffer[3] = 0x3f;
            buffer[4] = 0x00;
            buffer[5] = evaluate_checksum (buffer, 5);

            to_return = 6;
            break;

        default:
            to_return = -1;
            break;
    }

    return to_return;
}

int
bentel_message_decode (bentel_layer_t * bentel_layer,
                       bentel_message_t * bentel_message,
                       unsigned char * buffer, int len)
{
    uint32_t command_id;
    char *c;
    int i;

    if (buffer[0] != 0xf0)
    {
        /* error, we are out of sync */
        return -3;
    }

    command_id = (buffer[1] << 24) + (buffer[2] << 16) + (buffer[3] << 8) + buffer[4];

    switch (command_id)
    {
        case 0x00000b00:
            /*
             * BENTEL_GET_MODEL_RESPONSE
             *
             * -> f0 00 00 0b 00 fb
             * <- f0 00 00 0b 00 fb 4b 59 4f 33 32 20 20 20 32 2e 31 32 7b 
             *                      K  Y  O  3  2           2  .  1  2
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 19)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[18] != evaluate_checksum (&buffer[6], 12))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_MODEL_RESPONSE;

            snprintf (bentel_message->u.get_model_response.model,
                      sizeof (bentel_message->u.get_model_response.model),
                      "%s", &buffer[6]);
            right_strip (bentel_message->u.get_model_response.model,
                         sizeof (bentel_message->u.get_model_response.model) - 2);

            bentel_message->u.get_model_response.fw_major =
                buffer[14] - '0';
            bentel_message->u.get_model_response.fw_minor =
                (buffer[16] - '0') * 10 + (buffer[17] - '0');

            return 19;

        case 0x09f00b00:
            /*
             * BENTEL_GET_PERIPHERALS_RESPONSE
             *
             * -> f0 09 f0 0b 00 f4
             * <- f0 09 f0 0b 00 f4 00 01 02 01 00 00 00 00 00 01 02 01 08
             *                          |  |  | \------/  |     |  |  |
             *                 one reader  |  |everything | reader |  |
             *                  one keyboard  |     OK    | alive  |  |
             *                          ignored     ignored        |  |
             *                                        keyboard alive  |
             *                                                  ignored
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 19)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[18] != evaluate_checksum (&buffer[6], 12))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_PERIPHERALS_RESPONSE;

            for (i = 0 ; i < 8 ; i++)
            {
                bentel_message->u.get_peripherals_response.readers[i].present =
                    (buffer[7] & (0x01 << i));
                bentel_message->u.get_peripherals_response.readers[i].sabotage =
                    (buffer[11] & (0x01 << i));
                bentel_message->u.get_peripherals_response.readers[i].alive =
                    (buffer[15] & (0x01 << i));
            }

            for (i = 0 ; i < 8 ; i++)
            {
                bentel_message->u.get_peripherals_response.readers[i + 8].present =
                    (buffer[6] & (0x01 << i));
                bentel_message->u.get_peripherals_response.readers[i + 8].sabotage =
                    (buffer[10] & (0x01 << i));
                bentel_message->u.get_peripherals_response.readers[i + 8].alive =
                    (buffer[14] & (0x01 << i));
            }

            for (i = 0 ; i < 8 ; i++)
            {
                bentel_message->u.get_peripherals_response.keyboards[i].present =
                    (buffer[8] & (0x01 << i));
                bentel_message->u.get_peripherals_response.keyboards[i].sabotage =
                    (buffer[12] & (0x01 << i));
                bentel_message->u.get_peripherals_response.keyboards[i].alive =
                    (buffer[16] & (0x01 << i));
            }

            return 19;

        case 0xb0193f00:
            /*
             * BENTEL_GET_ZONES_NAMES_0_3_RESPONSE
             *
             * -> f0 b0 19 3f 00 f8
             * <- f0 b0 19 3f 00 f8 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_0_3_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_0_3_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_0_3_response.zones[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_zones_names_0_3_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_0_3_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_0_3_response.zones[i].name) - 2);
            }

            return 71;

        case 0xf0193f00:
            /*
             * BENTEL_GET_ZONES_NAMES_4_7_RESPONSE
             *
             * -> f0 f0 19 3f 00 38
             * <- f0 f0 19 3f 00 38 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_4_7_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_4_7_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_4_7_response.zones[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_zones_names_0_3_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_4_7_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_4_7_response.zones[i].name) - 2);
            }

            return 71;

        case 0x301a3f00:
            /*
             * BENTEL_GET_ZONES_NAMES_8_11_RESPONSE
             *
             * -> f0 30 1a 3f 00 79
             * <- f0 30 1a 3f 00 79 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_8_11_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_8_11_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_8_11_response.zones[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_zones_names_0_3_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_8_11_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_8_11_response.zones[i].name) - 2);
            }

            return 71;

        case 0x701a3f00:
            /*
             * BENTEL_GET_ZONES_NAMES_12_15_RESPONSE
             *
             * -> f0 70 1a 3f 00 b9
             * <- f0 70 1a 3f 00 b9 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_12_15_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_12_15_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_12_15_response.zones[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_zones_names_0_3_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_12_15_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_12_15_response.zones[i].name) - 2);
            }

            return 71;

        case 0xb01a3f00:
            /*
             * BENTEL_GET_ZONES_NAMES_16_19_RESPONSE
             *
             * -> f0 b0 1a 3f 00 f9
             * <- f0 b0 1a 3f 00 f9 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_16_19_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_16_19_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_16_19_response.zones[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_zones_names_0_3_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_16_19_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_16_19_response.zones[i].name) - 2);
            }

            return 71;

        case 0xf01a3f00:
            /*
             * BENTEL_GET_ZONES_NAMES_20_23_RESPONSE
             *
             * -> f0 f0 1a 3f 00 39
             * <- f0 f0 1a 3f 00 39 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_20_23_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_20_23_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_20_23_response.zones[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_zones_names_0_3_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_20_23_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_20_23_response.zones[i].name) - 2);
            }

            return 71;

        case 0x301b3f00:
            /*
             * BENTEL_GET_ZONES_NAMES_24_27_RESPONSE
             *
             * -> f0 30 1b 3f 00 7a
             * <- f0 30 1b 3f 00 7a 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_24_27_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_24_27_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_24_27_response.zones[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_zones_names_0_3_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_24_27_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_24_27_response.zones[i].name) - 2);
            }

            return 71;

        case 0x701b3f00:
            /*
             * BENTEL_GET_ZONES_NAMES_28_31_RESPONSE
             *
             * -> f0 70 1b 3f 00 5a
             * <- f0 70 1b 3f 00 5a 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_28_31_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_28_31_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_28_31_response.zones[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_zones_names_0_3_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_28_31_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_28_31_response.zones[i].name) - 2);
            }

            return 71;

        case 0x50173f00:
            /*
             * BENTEL_GET_PARTITIONS_NAMES_0_3_RESPONSE
             *
             * -> f0 50 17 3f 00 96
             * <- f0 50 17 3f 00 96 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_PARTITIONS_NAMES_0_3_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_partitions_names_0_3_response.partitions[i].name,
                          sizeof (bentel_message->u.get_partitions_names_0_3_response.partitions[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_partitions_names_0_3_response.partitions[i].name[16] = 0;
                right_strip (bentel_message->u.get_partitions_names_0_3_response.partitions[i].name,
                             sizeof (bentel_message->u.get_partitions_names_0_3_response.partitions[i].name) - 2);
            }

            return 71;

        case 0x90173f00:
            /*
             * BENTEL_GET_PARTITIONS_NAMES_4_7_RESPONSE
             *
             * -> f0 90 17 3f 00 d6
             * <- f0 90 17 3f 00 d6 70 ... 20 f7
             *                      \-------/
             *         4 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_PARTITIONS_NAMES_4_7_RESPONSE;

            for (i = 0 ; i < 4 ; i++)
            {
                snprintf (bentel_message->u.get_partitions_names_4_7_response.partitions[i].name,
                          sizeof (bentel_message->u.get_partitions_names_4_7_response.partitions[i].name),
                          "%s", &buffer[6 + (i * 16)]);
                bentel_message->u.get_partitions_names_0_3_response.partitions[i].name[16] = 0;
                right_strip (bentel_message->u.get_partitions_names_4_7_response.partitions[i].name,
                             sizeof (bentel_message->u.get_partitions_names_4_7_response.partitions[i].name) - 2);
            }

            return 71;

        case 0x04f00a00:
            /*
             * BENTEL_GET_STATUS_AND_FAULTS_RESPONSE
             *
             * -> f0 04 f0 0a 00 ee
             * <- f0 04 f0 0a 00 ee 00 00 00 00 00 00 00 00 00 00 00 00
             *                      \---------/ \---------/  |  |  |
             *                         zones       zones     |  |  |
             *                         alarm     sabotage    |  |  |
             *                                         warnings |  |
             *                                        areas alarm  |
             *                                                sabotages
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 18)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[17] != evaluate_checksum (&buffer[6], 11))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_STATUS_AND_FAULTS_RESPONSE;

            bentel_message->u.get_status_and_faults_response.alarm_zone_31 =
                buffer[6] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.alarm_zone_30 =
                buffer[6] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.alarm_zone_29 =
                buffer[6] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.alarm_zone_28 =
                buffer[6] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.alarm_zone_27 =
                buffer[6] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.alarm_zone_26 =
                buffer[6] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.alarm_zone_25 =
                buffer[6] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.alarm_zone_24 =
                buffer[6] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.alarm_zone_23 =
                buffer[7] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.alarm_zone_22 =
                buffer[7] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.alarm_zone_21 =
                buffer[7] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.alarm_zone_20 =
                buffer[7] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.alarm_zone_19 =
                buffer[7] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.alarm_zone_18 =
                buffer[7] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.alarm_zone_17 =
                buffer[7] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.alarm_zone_16 =
                buffer[7] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.alarm_zone_15 =
                buffer[8] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.alarm_zone_14 =
                buffer[8] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.alarm_zone_13 =
                buffer[8] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.alarm_zone_12 =
                buffer[8] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.alarm_zone_11 =
                buffer[8] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.alarm_zone_10 =
                buffer[8] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.alarm_zone_9 =
                buffer[8] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.alarm_zone_8 =
                buffer[8] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.alarm_zone_7 =
                buffer[9] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.alarm_zone_6 =
                buffer[9] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.alarm_zone_5 =
                buffer[9] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.alarm_zone_4 =
                buffer[9] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.alarm_zone_3 =
                buffer[9] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.alarm_zone_2 =
                buffer[9] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.alarm_zone_1 =
                buffer[9] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.alarm_zone_0 =
                buffer[9] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.sabotage_zone_31 =
                buffer[10] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_30 =
                buffer[10] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_29 =
                buffer[10] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_28 =
                buffer[10] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_27 =
                buffer[10] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_26 =
                buffer[10] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_25 =
                buffer[10] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_24 =
                buffer[10] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.sabotage_zone_23 =
                buffer[11] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_22 =
                buffer[11] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_21 =
                buffer[11] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_20 =
                buffer[11] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_19 =
                buffer[11] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_18 =
                buffer[11] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_17 =
                buffer[11] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_16 =
                buffer[11] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.sabotage_zone_15 =
                buffer[12] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_14 =
                buffer[12] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_13 =
                buffer[12] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_12 =
                buffer[12] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_11 =
                buffer[12] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_10 =
                buffer[12] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_9 =
                buffer[12] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_8 =
                buffer[12] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.sabotage_zone_7 =
                buffer[13] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_6 =
                buffer[13] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_5 =
                buffer[13] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_4 =
                buffer[13] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_3 =
                buffer[13] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_2 =
                buffer[13] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_1 =
                buffer[13] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.sabotage_zone_0 =
                buffer[13] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.alarm_power =
                buffer[14] & (0x01 << 0);
            bentel_message->u.get_status_and_faults_response.alarm_bpi =
                buffer[14] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.alarm_fuse =
                buffer[14] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.alarm_battery_low =
                buffer[14] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.alarm_telephone_line =
                buffer[14] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.alarm_default_codes =
                buffer[14] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.alarm_wireless =
                buffer[14] & (0x01 << 6);

            bentel_message->u.get_status_and_faults_response.alarm_partition_7 =
                buffer[15] & (0x01 << 7);
            bentel_message->u.get_status_and_faults_response.alarm_partition_6 =
                buffer[15] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.alarm_partition_5 =
                buffer[15] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.alarm_partition_4 =
                buffer[15] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.alarm_partition_3 =
                buffer[15] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.alarm_partition_2 =
                buffer[15] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.alarm_partition_1 =
                buffer[15] & (0x01 << 1);
            bentel_message->u.get_status_and_faults_response.alarm_partition_0 =
                buffer[15] & (0x01 << 0);

            bentel_message->u.get_status_and_faults_response.sabotage_partition =
                buffer[16] & (0x01 << 2);
            bentel_message->u.get_status_and_faults_response.sabotage_fake_key =
                buffer[16] & (0x01 << 3);
            bentel_message->u.get_status_and_faults_response.sabotage_bpi =
                buffer[16] & (0x01 << 4);
            bentel_message->u.get_status_and_faults_response.sabotage_system =
                buffer[16] & (0x01 << 5);
            bentel_message->u.get_status_and_faults_response.sabotage_jam =
                buffer[16] & (0x01 << 6);
            bentel_message->u.get_status_and_faults_response.sabotage_wireless =
                buffer[16] & (0x01 << 7);

            return 18;

        case 0x02151200:
            /*
             * BENTEL_GET_ARMED_PARTITIONS_RESPONSE
             *
             * -> f0 02 15 12 00 19
             * <- f0 02 15 12 00 19 00 00 00 ff 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ff
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 26)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[25] != evaluate_checksum (&buffer[6], 19))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ARMED_PARTITIONS_RESPONSE;

            for (i = 0 ; i < 8 ; i++)
            {
                bentel_message->u.get_armed_partitions_response.partition_armed_state[i] =
                    (buffer[9] & (0x01 << i) != 0);
            }

            bentel_message->u.get_armed_partitions_response.siren_state =
                (buffer[10] != 0);

            for (i = 0 ; i < 8 ; i++)
            {
                bentel_message->u.get_armed_partitions_response.digital_output_state[8 + i] =
                    (buffer[11] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.digital_output_state[i] =
                    (buffer[12] & (0x01 << i) != 0);
            }

            for (i = 0 ; i < 8 ; i++)
            {
                bentel_message->u.get_armed_partitions_response.zone_inclusion[24 + i] =
                    (buffer[13] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_inclusion[16 + i] =
                    (buffer[14] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_inclusion[8 + i] =
                    (buffer[15] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_inclusion[i] =
                    (buffer[16] & (0x01 << i) != 0);
            }

            for (i = 0 ; i < 8 ; i++)
            {
                bentel_message->u.get_armed_partitions_response.zone_alarm_memory[24 + i] =
                    (buffer[17] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_alarm_memory[16 + i] =
                    (buffer[18] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_alarm_memory[8 + i] =
                    (buffer[19] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_alarm_memory[i] =
                    (buffer[20] & (0x01 << i) != 0);
            }

            for (i = 0 ; i < 8 ; i++)
            {
                bentel_message->u.get_armed_partitions_response.zone_sabotage_memory[24 + i] =
                    (buffer[21] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_sabotage_memory[16 + i] =
                    (buffer[22] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_sabotage_memory[8 + i] =
                    (buffer[23] & (0x01 << i) != 0);

                bentel_message->u.get_armed_partitions_response.zone_sabotage_memory[i] =
                    (buffer[24] & (0x01 << i) != 0);
            }

            return 26;

        case 0x3d0d3f00:
            /*
             * BENTEL_GET_LOGGER_1_RESPONSE
             *
             * -> f0 3d 0d 3f 00 79
             * <- f0 3d 0d 3f 00 79 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_1_RESPONSE;

            memcpy (&(bentel_layer->logger[0 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x7d0d3f00:
            /*
             * BENTEL_GET_LOGGER_2_RESPONSE
             *
             * -> f0 7d 0d 3f 00 b9
             * <- f0 7d 0d 3f 00 b9 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_2_RESPONSE;

            memcpy (&(bentel_layer->logger[1 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xbd0d3f00:
            /*
             * BENTEL_GET_LOGGER_3_RESPONSE
             *
             * -> f0 bd 0d 3f 00 f9
             * <- f0 bd 0d 3f 00 f9 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_3_RESPONSE;

            memcpy (&(bentel_layer->logger[2 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xfd0d3f00:
            /*
             * BENTEL_GET_LOGGER_4_RESPONSE
             *
             * -> f0 fd 0d 3f 00 39
             * <- f0 fd 0d 3f 00 39 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_4_RESPONSE;

            memcpy (&(bentel_layer->logger[3 * 64]), &(buffer[6]), 64);

            return 71;

/**/
        case 0x3d0e3f00:
            /*
             * BENTEL_GET_LOGGER_5_RESPONSE
             *
             * -> f0 3d 0e 3f 00 7a
             * <- f0 3d 0e 3f 00 7a 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_5_RESPONSE;

            memcpy (&(bentel_layer->logger[4 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x7d0e3f00:
            /*
             * BENTEL_GET_LOGGER_6_RESPONSE
             *
             * -> f0 7d 0e 3f 00 ba
             * <- f0 7d 0e 3f 00 ba 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_6_RESPONSE;

            memcpy (&(bentel_layer->logger[5 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xbd0e3f00:
            /*
             * BENTEL_GET_LOGGER_7_RESPONSE
             *
             * -> f0 bd 0e 3f 00 fa
             * <- f0 bd 0e 3f 00 fa 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_7_RESPONSE;

            memcpy (&(bentel_layer->logger[6 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xfd0e3f00:
            /*
             * BENTEL_GET_LOGGER_8_RESPONSE
             *
             * -> f0 fd 0e 3f 00 3a
             * <- f0 fd 0e 3f 00 3a 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_8_RESPONSE;

            memcpy (&(bentel_layer->logger[7 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x3d0f3f00:
            /*
             * BENTEL_GET_LOGGER_9_RESPONSE
             *
             * -> f0 3d 0f 3f 00 7b
             * <- f0 3d 0f 3f 00 7b 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_9_RESPONSE;

            memcpy (&(bentel_layer->logger[8 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x7d0f3f00:
            /*
             * BENTEL_GET_LOGGER_10_RESPONSE
             *
             * -> f0 7d 0f 3f 00 bb
             * <- f0 7d 0f 3f 00 bb 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_10_RESPONSE;

            memcpy (&(bentel_layer->logger[9 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xbd0f3f00:
            /*
             * BENTEL_GET_LOGGER_11_RESPONSE
             *
             * -> f0 bd 0f 3f 00 fb
             * <- f0 bd 0f 3f 00 fb 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_11_RESPONSE;

            memcpy (&(bentel_layer->logger[10 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xfd0f3f00:
            /*
             * BENTEL_GET_LOGGER_12_RESPONSE
             *
             * -> f0 fd 0f 3f 00 3b
             * <- f0 fd 0f 3f 00 3b 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_12_RESPONSE;

            memcpy (&(bentel_layer->logger[11 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x3d103f00:
            /*
             * BENTEL_GET_LOGGER_13_RESPONSE
             *
             * -> f0 3d 10 3f 00 7c
             * <- f0 3d 10 3f 00 7c 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_13_RESPONSE;

            memcpy (&(bentel_layer->logger[12 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x7d103f00:
            /*
             * BENTEL_GET_LOGGER_14_RESPONSE
             *
             * -> f0 7d 10 3f 00 bc
             * <- f0 7d 10 3f 00 bc 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_14_RESPONSE;

            memcpy (&(bentel_layer->logger[13 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xbd103f00:
            /*
             * BENTEL_GET_LOGGER_15_RESPONSE
             *
             * -> f0 bd 10 3f 00 fc
             * <- f0 bd 10 3f 00 fc 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_15_RESPONSE;

            memcpy (&(bentel_layer->logger[14 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xfd103f00:
            /*
             * BENTEL_GET_LOGGER_16_RESPONSE
             *
             * -> f0 fd 10 3f 00 3c
             * <- f0 fd 10 3f 00 3c 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_16_RESPONSE;

            memcpy (&(bentel_layer->logger[15 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x3d113f00:
            /*
             * BENTEL_GET_LOGGER_17_RESPONSE
             *
             * -> f0 3d 11 3f 00 7d
             * <- f0 3d 11 3f 00 7d 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_17_RESPONSE;

            memcpy (&(bentel_layer->logger[16 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x7d113f00:
            /*
             * BENTEL_GET_LOGGER_18_RESPONSE
             *
             * -> f0 7d 11 3f 00 bd
             * <- f0 7d 11 3f 00 bd 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_18_RESPONSE;

            memcpy (&(bentel_layer->logger[17 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xbd113f00:
            /*
             * BENTEL_GET_LOGGER_19_RESPONSE
             *
             * -> f0 bd 11 3f 00 fd
             * <- f0 bd 11 3f 00 fd 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_19_RESPONSE;

            memcpy (&(bentel_layer->logger[18 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xfd113f00:
            /*
             * BENTEL_GET_LOGGER_20_RESPONSE
             *
             * -> f0 fd 11 3f 00 3d
             * <- f0 fd 11 3f 00 3d 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_20_RESPONSE;

            memcpy (&(bentel_layer->logger[19 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x3d123f00:
            /*
             * BENTEL_GET_LOGGER_21_RESPONSE
             *
             * -> f0 3d 12 3f 00 7e
             * <- f0 3d 12 3f 00 7e 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_21_RESPONSE;

            memcpy (&(bentel_layer->logger[20 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x7d123f00:
            /*
             * BENTEL_GET_LOGGER_22_RESPONSE
             *
             * -> f0 7d 12 3f 00 be
             * <- f0 7d 12 3f 00 be 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_22_RESPONSE;

            memcpy (&(bentel_layer->logger[21 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xbd123f00:
            /*
             * BENTEL_GET_LOGGER_23_RESPONSE
             *
             * -> f0 bd 12 3f 00 fe
             * <- f0 bd 12 3f 00 fe 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_23_RESPONSE;

            memcpy (&(bentel_layer->logger[22 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xfd123f00:
            /*
             * BENTEL_GET_LOGGER_24_RESPONSE
             *
             * -> f0 fd 12 3f 00 3e
             * <- f0 fd 12 3f 00 3e 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_24_RESPONSE;

            memcpy (&(bentel_layer->logger[23 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x3d133f00:
            /*
             * BENTEL_GET_LOGGER_25_RESPONSE
             *
             * -> f0 3d 13 3f 00 7f
             * <- f0 3d 13 3f 00 7f 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_25_RESPONSE;

            memcpy (&(bentel_layer->logger[24 * 64]), &(buffer[6]), 64);

            return 71;

        case 0x7d133f00:
            /*
             * BENTEL_GET_LOGGER_26_RESPONSE
             *
             * -> f0 7d 13 3f 00 bf
             * <- f0 7d 13 3f 00 bf 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_26_RESPONSE;

            memcpy (&(bentel_layer->logger[25 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xbd133f00:
            /*
             * BENTEL_GET_LOGGER_27_RESPONSE
             *
             * -> f0 bd 13 3f 00 ff
             * <- f0 bd 13 3f 00 ff 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_27_RESPONSE;

            memcpy (&(bentel_layer->logger[26 * 64]), &(buffer[6]), 64);

            return 71;

        case 0xfd133f00:
            /*
             * BENTEL_GET_LOGGER_28_RESPONSE
             *
             * -> f0 fd 13 3f 00 3f
             * <- f0 fd 13 3f 00 3f 01 .. 00 c2
             *                      \------/
             *    64 bytes, since 64 * 28 = 1792, the size of the logger
             *
             * Each event is 7 bytes long, there is no alignement in the
             * BENTEL_GET_LOGGER_*_RESPONSE
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 71)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[70] != evaluate_checksum (&buffer[6], 64))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_LOGGER_28_RESPONSE;

            memcpy (&(bentel_layer->logger[27 * 64]), &(buffer[6]), 64);

            return 71;

        default:
            break;
    }

    return -4;
}
