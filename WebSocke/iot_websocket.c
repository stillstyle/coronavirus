#include "iot_config.h"
#include "iot_core.h"
#include "iot_websocket.h"

static int  iot_fetch_sec_key(const char *buf, char *seckey);
static void iot_websocket_uumask(char *data,int len,char *mask);


int iot_websocket_shake_hand(int fd)  
{  
    char buffer[WEBSOCKET_DATA_LEN_MAX] = {0};
    char header [WEBSOCKET_DATA_LEN_MAX] = {0}; 
    char * clientkey;  
    char sha1temp[256] = {0};  
    int i,n;  
    static char GUID[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";  
    iot_str_t src_str,dst_str;

    n = read(fd, buffer, WEBSOCKET_DATA_LEN_MAX);

    printf("%s\n",buffer);
    dst_str.data = malloc(256 * sizeof(char *));
    iot_memzero(dst_str.data,256);
        
    clientkey = (char *)malloc(256);  
    memset(clientkey,0,256);  
    if(iot_fetch_sec_key(buffer,clientkey) != IOT_OK) 
        return IOT_ERROR;
    
    if(!clientkey)  
    {  
        return IOT_ERROR;  
    }  

    strcat(clientkey,GUID);  
    iot_sha1(sha1temp,clientkey);  
    
    src_str.data = malloc(256 * sizeof(char *));
    iot_memzero(src_str.data,256);

    for(i=0; i < strlen(sha1temp); i+=2)  
    {        
        src_str.data[i/2] = iot_hextoi(sha1temp+i,2);      
    }   
    src_str.len = strlen(src_str.data);    
    iot_encode_base64(&dst_str,&src_str);

    sprintf(header, "HTTP/1.1 101 Switching Protocols\r\n" \
                  "Upgrade: websocket\r\n" \
                  "Connection: Upgrade\r\n" \
                  "Sec-WebSocket-Accept: %s\r\n" \
                  "\r\n",dst_str.data);

    write(fd,header,strlen(header));

    free(clientkey);
    free(src_str.data);
    free(dst_str.data);
    return IOT_OK;
}


static int  iot_fetch_sec_key(const char *buf, char *seckey)  
{  
    char *keyBegin;  
    static char flag[] = "Sec-WebSocket-Key: ";  
    int i=0;  

    if(buf == NULL)  
    {  
        return IOT_ERROR;  
    }  

    keyBegin = strstr(buf,flag);  
    if(!keyBegin)  
    {  
        return IOT_ERROR;  
    }  
    
    keyBegin += strlen(flag);  

    for(i=0; i < strlen(buf); i++)  
    {  
        if(keyBegin[i]==0x0A ||keyBegin[i]==0x0D)  
        {  
            break;  
        }  
        seckey[i] = keyBegin[i];  
    }  

    return IOT_OK;
}  
    
static void iot_websocket_uumask(char *data,int len,char *mask)
{
    int i;
    for (i=0;i<len;++i)
    {
        *(data+i) ^= *(mask+(i%4));
    }
}

int iot_websocket_parse(int fd, websocket_frame_t *head)
{
    char one_char;
    
    //read fin and op code
    if (read(fd,&one_char,1)<=0)
    {
        perror("read fin");
        return IOT_ERROR;
    }
    
    head->fin = (one_char & 0x80) == 0x80;
    head->opcode = one_char & 0x0F;
    if (read(fd,&one_char,1)<=0)
    {
        perror("read mask");
        return IOT_ERROR;
    }
    
    head->mask = (one_char & 0x80) == 0X80;

    //get payload length
    head->payload_length = one_char & 0x7F;

    if (head->payload_length == 126)
    {
        char extern_len[2];
        if (read(fd,extern_len,2)<=0)
        {
            perror("read extern_len");
            return IOT_ERROR;
        }
        head->payload_length = (extern_len[0]&0xFF) << 8 | (extern_len[1]&0xFF);
    }
    else if (head->payload_length == 127)
    {
        char extern_len[8],temp;
        int i;
        if (read(fd,extern_len,8)<=0)
        {
            perror("read extern_len");
            return IOT_ERROR;
        }
        for(i=0;i<4;i++)
        {
            temp = extern_len[i];
            extern_len[i] = extern_len[7-i];
            extern_len[7-i] = temp;
        }
        memcpy(&(head->payload_length),extern_len,8);
    }

    //read masking-key
    if (read(fd,head->masking_key,4)<=0)
    {
        perror("read masking-key");
        return IOT_ERROR;
    }

    //read payload data
    if (read(fd,head->payload_data,WEBSOCKET_DATA_LEN_MAX) <= 0)
    {
        perror("read payload data");
        return IOT_ERROR;
    }

    iot_websocket_uumask(head->payload_data, strlen(head->payload_data), head->masking_key);
    printf("d--%s\n",head->payload_data);       
     
    return 0;
}

  
int iot_send_to_web(int fd, iot_str_t *message)  
{  
    u_char data[WEBSOCKET_DATA_LEN_MAX] = {0};  
    int head_length = 0;  

    if(message == NULL)
    {
        return IOT_ERROR;
    }
        
    if(message->len < 126)
    {
        data[0] = 0x81;
        data[1] = message->len;
        head_length = 2;
        memcpy(data+2,message->data,message->len);
    }
    else if (message->len < 0xFFFF)
    {
        data[0] = 0x81;
        data[1] = 126;
        data[2] = (message->len >> 8 & 0xFF);
        data[3] = (message->len & 0xFF);
        head_length = 4;
        memcpy(data+4,message->data,message->len);
    }
    else
    {
        //no code
        head_length = 12;
    }

    if(write(fd,data,(head_length+message->len)) <= 0)
    {
        perror("write head");
        return IOT_ERROR;
    }

    return IOT_OK;
}  


