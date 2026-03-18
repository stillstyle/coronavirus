
#include "iot_config.h"
#include "iot_core.h"
 
  
 
#define LINE_MAX 256  
  
  
int main(int argc, char *argv[])  
{  
    struct sockaddr_in servaddr, cliaddr;  
    socklen_t cliaddr_len;  
    int listenfd, connfd;  
    char buf[WEBSOCKET_DATA_LEN_MAX];  
    char *data;  
    char str[INET_ADDRSTRLEN];  
    char *secWebSocketKey;  
    int i,n;  

    iot_str_t sec_web_key,send_data;
    iot_str_t *sec_web_key_dst;
    websocket_frame_t websocket_frame;
        
    listenfd = socket(AF_INET, SOCK_STREAM, 0);  

    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    servaddr.sin_port = htons(WEBSOCKET_SERVER_PORT);  
      
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));  
  
    listen(listenfd, 20);  
  
    printf("Listen %d\nAccepting connections ...\n",WEBSOCKET_SERVER_PORT);  
    cliaddr_len = sizeof(cliaddr);  
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);  
    printf("From %s at PORT %d\n",  
               inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),  
               ntohs(cliaddr.sin_port));  

    iot_websocket_shake_hand(connfd);
    websocket_frame.payload_data = malloc(WEBSOCKET_DATA_LEN_MAX * sizeof(char *));
    while (1)  
    { 
         
        iot_memzero(websocket_frame.payload_data,WEBSOCKET_DATA_LEN_MAX);
        iot_websocket_parse(connfd,&websocket_frame);
//        memset(buf,0,WEBSOCKET_DATA_LEN_MAX);  
//        n = read(connfd, buf, WEBSOCKET_DATA_LEN_MAX);   
        printf("---------------------\n");  
        printf("fin=%d opcode=0x%X mask=%d payload_len=%llu\n",websocket_frame.fin,websocket_frame.opcode,websocket_frame.mask,websocket_frame.payload_length);
//        data = iot_websocket_parse(buf,n);

        send_data.len = websocket_frame.payload_length;
        send_data.data = websocket_frame.payload_data;   
        iot_send_to_web(connfd,&send_data);  
    } 

    free(websocket_frame.payload_data); 
    close(connfd);  
} 

