//sha1.h：对字符串进行sha1加密  
#ifndef _SHA1_H_  
#define _SHA1_H_  
  
#include "iot_config.h"  
#include "iot_core.h" 
 

#define SHA_CIRCULAR_SHIFT(bits,word) ((((word) << (bits)) & 0xFFFFFFFF) | ((word) >> (32-(bits))))   

#define SHA_DIGEST_LENGTH 20

 
typedef struct sha1_context_t
{  
    unsigned Message_Digest[5];        
    unsigned Length_Low;               
    unsigned Length_High;              
    unsigned char Message_Block[64];   
    int Message_Block_Index;           
    int Computed;                      
    int Corrupted;                     
} sha1_context_t;  



  

int iot_sha1(char *dst, const char *src);


#endif  
  
  
