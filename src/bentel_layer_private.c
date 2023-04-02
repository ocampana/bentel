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

        case BENTEL_GET_ZONES_NAMES_REQUEST:
            /* -> f0 b0 19 3f 00 f8 */
            buffer[0] = 0xf0;
            buffer[1] = 0xb0;
            buffer[2] = 0x19;
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
             * BENTEL_GET_ZONES_NAMES_RESPONSE
             *
             * -> f0 b0 19 3f 00 f8
             * <- f0 b0 19 3f 00 f8 70 ... 20 f7
             *                      \-------/
             *         32 contiguous strings 16 characters long,
             *                  not NULL terminated
             */
            if (buffer[5] != evaluate_checksum (buffer, 5))
            {
                return -1;
            }

            if (len < 518)
            {
                /*
                 * incomplete message, we need to wait for more
                 * characters
                 */
                return 0;
            }

            /* let's check the second checksum */
            if (buffer[517] != evaluate_checksum (&buffer[6], 512))
            {
                return -2;
            }

            bentel_message->message_type = BENTEL_GET_ZONES_NAMES_RESPONSE;

            for (i = 0 ; i < 32 ; i++)
            {
                snprintf (bentel_message->u.get_zones_names_response.zones[i].name,
                          sizeof (bentel_message->u.get_zones_names_response.zones[i].name),
                          "%s", &buffer[6+i*16]);
                bentel_message->u.get_zones_names_response.zones[i].name[16] = 0;
                right_strip (bentel_message->u.get_zones_names_response.zones[i].name,
                             sizeof (bentel_message->u.get_zones_names_response.zones[i].name) -2);
            }

            return 518;

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
