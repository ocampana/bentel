#ifndef _bentel_layer_private_h_
#define _bentel_layer_private_h_

#include "bentel_layer.h"

int bentel_message_encode (bentel_message_t * bentel_message,
                           unsigned char * buffer, int len);

int bentel_message_decode (bentel_layer_t * bental_layer,
                           bentel_message_t * bentel_message,
                           unsigned char * buffer, int len);

#endif /* _bentel_layer_private_h_ */
