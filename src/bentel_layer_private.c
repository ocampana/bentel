#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "bentel_layer.h"
#include "bentel_layer_private.h"

static unsigned char
evaluate_checksum (unsigned char * buffer, int len)
{
    int i;
    unsigned char to_return = 0;

    for (i = 0 ; i < len ; i++) 
    {
        to_return = (to_return + buffer[i]) & 0xff;
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

    if (buffer[0] != 0xf0)
    {
        /* error, we are out of sync */
        return -1;
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
            if (buffer[18] != evaluate_checksum (buffer, 18))
            {
                return -1;
            }

            bentel_message->message_type = BENTEL_GET_MODEL_RESPONSE;

            snprintf (bentel_message->u.get_model_response.model, 8,
                      "%s", &bentel_message[6]);
            c = index ((const char *) &bentel_message[6], ' ');
            *c = 0;

            bentel_message->u.get_model_response.fw_major =
                buffer[14] - '0';
            bentel_message->u.get_model_response.fw_minor =
                (buffer[16] - '0') * 10 + (buffer[17] - '0');

            return 19;

        default:
            break;
    }

    return -1;
}
