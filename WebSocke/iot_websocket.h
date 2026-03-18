#ifndef _IOT_WEBSOCKET_H_
#define _IOT_WEBSOCKET_H_

#include "iot_config.h"
#include "iot_core.h"
#include "iot_string.h"

#define WEBSOCKET_SERVER_PORT 9999

#define WEBSOCKET_DATA_LEN_MAX 1024  
  

struct websocket_frame_s 
{
    char fin;
    char opcode;
    char mask;
    unsigned long long payload_length;
    char masking_key[4];
    char *payload_data;
};



int iot_websocket_shake_hand(int fd);
int iot_websocket_parse(int fd, websocket_frame_t *head);
int iot_send_to_web(int fd, iot_str_t *message);



#endif

