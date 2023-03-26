#ifndef _bentel_layer_h_
#define _bentel_layer_h_

typedef enum _bentel_message_type_t bentel_message_type_t;

enum _bentel_message_type_t
{
    BENTEL_GET_MODEL_REQUEST = 1,
    BENTEL_GET_MODEL_RESPONSE,
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
            char model[10];
	    int fw_major;
	    int fw_minor;
        } get_model_response;
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

    unsigned char buffer[128];
    int buffer_index;
};

int bentel_layer_start (void * layer);

void bentel_layer_stop (void * layer);

int bentel_layer_send_message (void * layer, void * message);

void bentel_layer_received_message (void * layer, void * message, int len);

#endif /* _bentel_layer_h_ */
