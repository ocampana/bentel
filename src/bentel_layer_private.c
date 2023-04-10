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


        default:
            to_return = -1;
            break;
    }

    return to_return;
}

int
bentel_message_decode (bentel_message_t * bentel_message,
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
                bentel_message->u.get_armed_partitions_response.digital_output_state[8 + i] = false;
            }

            return 26;

        default:
            break;
    }

    return -4;
}
