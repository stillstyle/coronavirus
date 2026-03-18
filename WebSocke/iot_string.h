
/*
 * Copyright (C) $K
 */


#ifndef _IOT_STRING_H_
#define _IOT_STRING_H_


#include "iot_config.h"
#include "iot_core.h"


struct iot_str_s
{
    size_t    len;
    u_char   *data;
};


#define break_uint32( var, ByteNum ) \
          (u_char)((uint32_t)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define build_uint32(Byte0, Byte1, Byte2, Byte3) \
          ((u_char)((uint32_t)((Byte0) & 0x00FF) \
          + ((uint32_t)((Byte1) & 0x00FF) << 8) \
          + ((uint32_t)((Byte2) & 0x00FF) << 16) \
          + ((uint32_t)((Byte3) & 0x00FF) << 24)))

#define build_uint16(loByte, hiByte) \
          ((u_short)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define hi_uint16(a) (((a) >> 8) & 0xFF)
#define lo_uint16(a) ((a) & 0xFF)

#define build_uint8(hiByte, loByte) \
          ((u_char)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))

#define hi_uint8(a) (((a) >> 4) & 0x0F)
#define lo_uint8(a) ((a) & 0x0F)



#define iot_string(str)  { sizeof(str) - 1, (u_char *) str }
#define iot_null_string  { 0, NULL }


#define iot_tolower(c)     (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define iot_toupper(c)     (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)




#define iot_strncasecmp(s1, s2, n)                                           \
                           strncasecmp((const char *) s1, (const char *) s2, n)
#define iot_strcasecmp(s1, s2)                                               \
                           strcasecmp((const char *) s1, (const char *) s2)


#define iot_strncmp(s1, s2, n)  strncmp((const char *) s1, (const char *) s2, n)


#define iot_strcmp(s1, s2)  strcmp((const char *) s1, (const char *) s2)


#define iot_strstr(s1, s2)  strstr((const char *) s1, (const char *) s2)
#define iot_strlen(s)       strlen((const char *) s)


#define iot_memzero(buf, n)       (void) memset(buf, 0, n)
#define iot_memset(buf, c, n)     (void) memset(buf, c, n)


#define iot_cpymem(dst, src, n)   ((u_char *) memcpy(dst, src, n)) + (n)


#define iot_memcmp                memcmp


u_char *iot_cpystrn(u_char *dst, u_char *src, size_t n);

int iot_rstrncmp(u_char *s1, u_char *s2, size_t n);
int iot_rstrncasecmp(u_char *s1, u_char *s2, size_t n);

int iot_atoi(u_char *line, size_t n);
ssize_t iot_atosz(u_char *line, size_t n);
off_t iot_atoof(u_char *line, size_t n);
time_t iot_atotm(u_char *line, size_t n);
int iot_hextoi(u_char *line, size_t n);

void iot_md5_text(u_char *text, u_char *md5);


#define iot_base64_encoded_length(len)  (((len + 2) / 3) * 4)
#define iot_base64_decoded_length(len)  (((len + 3) / 4) * 3)

void iot_encode_base64(iot_str_t *dst, iot_str_t *src);
int iot_decode_base64(iot_str_t *dst, iot_str_t *src);

size_t iot_utf_length(iot_str_t *utf);
u_char * iot_utf_cpystrn(u_char *dst, u_char *src, size_t n);


#define  iot_qsort                qsort


#define  iot_value_helper(n)      #n
#define  iot_value(n)             iot_value_helper(n)


#endif /* _IOT_STRING_H_INCLUDED_ */
