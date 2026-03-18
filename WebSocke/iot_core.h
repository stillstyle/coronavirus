
/*
 * Copyright (C) K
 */


#ifndef _IOT_CORE_H_
#define _IOT_CORE_H_


//typedef struct iot_kedas_s iot_kedas_t;
//typedef struct iot_queue_s iot_queue_t;
//typedef struct iot_async_queue_s iot_async_queue_t;
//typedef struct iot_socket_s iot_socket_t;
typedef struct iot_str_s iot_str_t;
typedef struct websocket_frame_s websocket_frame_t;
//typedef struct iot_odbc_s iot_odbc_t;



#define  IOT_OK          0
#define  IOT_ERROR      -1
#define  IOT_AGAIN      -2
#define  IOT_BUSY       -3
#define  IOT_DONE       -4
#define  IOT_DECLINED   -5
#define  IOT_ABORT      -6


//#include "iot_socket.h"
//#include "iot_log.h"
//#include "iot_queue.h"
#include "iot_string.h"
#include "iot_sha1.h" 
#include "iot_websocket.h"


#define LF     (u_char) 10
#define CR     (u_char) 13
#define CRLF   "\x0d\x0a"


#define iot_abs(value)   (((value) >= 0) ? (value) : - (value))



#endif /* _IOT_CORE_H_INCLUDED_ */
