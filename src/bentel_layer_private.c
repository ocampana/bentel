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
             * BENTEL_GET_PARTITIONS_NAMES_RESPONSE
             *
             * -> f0 50 17 3f 00 f8
             * <- f0 50 17 3f 00 96 70 ... 20 f7
             *                      \-------/
             *         8 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 134)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[133] != evaluate_checksum (&buffer[6], 128))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_PARTITIONS_NAMES_RESPONSE;

            for (i = 0 ; i < 8 ; i++)
            {
                snprintf (bentel_message->u.get_partitions_names_response.partitions[i].name,
                          sizeof (bentel_message->u.get_partitions_names_response.partitions[i].name),
                          "%s", &buffer[6+i*16]);
                bentel_message->u.get_partitions_names_response.partitions[i].name[16] = 0;
                right_strip (bentel_message->u.get_partitions_names_response.partitions[i].name,
                             sizeof (bentel_message->u.get_partitions_names_response.partitions[i].name) -2);
            }

            return 134;


        default:
            break;
    }

    return -4;
}
