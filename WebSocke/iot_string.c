
/*
 * Copyright (C) K
 */

#include "iot_string.h"
#include "iot_config.h"
#include "iot_core.h"


u_char *iot_cpystrn(u_char *dst, u_char *src, size_t n)
{
    if (n == 0) {
        return dst;
    }

    for ( /* void */ ; --n; dst++, src++) {
        *dst = *src;

        if (*dst == '\0') {
            return dst;
        }
    }

    *dst = '\0';

    return dst;
}


int iot_rstrncmp(u_char *s1, u_char *s2, size_t n)
{
    if (n == 0) 
    {
        return 0;
    }

    n--;

    for ( ;; ) 
    {
        if (s1[n] != s2[n]) 
        {
            return s1[n] - s2[n];
        }

        if (n == 0) 
        {
            return 0;
        }

        n--;
    }
}


int iot_rstrncasecmp(u_char *s1, u_char *s2, size_t n)
{
    u_char  c1, c2;

    if (n == 0) {
        return 0;
    }

    n--;

    for ( ;; ) {
        c1 = s1[n];
        if (c1 >= 'a' && c1 <= 'z') {
            c1 -= 'a' - 'A';
        }

        c2 = s2[n];
        if (c2 >= 'a' && c2 <= 'z') {
            c2 -= 'a' - 'A';
        }

        if (c1 != c2) {
            return c1 - c2;
        }

        if (n == 0) {
            return 0;
        }

        n--;
    }
}


int iot_atoi(u_char *line, size_t n)
{
    int value;

    if (n == 0) {
        return IOT_ERROR;
    }

    for (value = 0; n--; line++) {
        if (*line < '0' || *line > '9') {
            return IOT_ERROR;
        }

        value = value * 10 + (*line - '0');
    }

    return (value < 0) ? IOT_ERROR : value;
}


ssize_t iot_atosz(u_char *line, size_t n)
{
    ssize_t  value;

    if (n == 0) {
        return IOT_ERROR;
    }

    for (value = 0; n--; line++) {
        if (*line < '0' || *line > '9') {
            return IOT_ERROR;
        }

        value = value * 10 + (*line - '0');
    }

    return (value < 0) ? IOT_ERROR : value;
}


off_t iot_atoof(u_char *line, size_t n)
{
    off_t  value;

    if (n == 0) 
    {
        return IOT_ERROR;
    }

    for (value = 0; n--; line++) 
    {
        if (*line < '0' || *line > '9') 
        {
            return IOT_ERROR;
        }

        value = value * 10 + (*line - '0');
    }

    return (value < 0) ? IOT_ERROR : value;
}


time_t iot_atotm(u_char *line, size_t n)
{
    time_t  value;

    if (n == 0) 
    {
        return IOT_ERROR;
    }

    for (value = 0; n--; line++) 
    {
        if (*line < '0' || *line > '9') 
        {
            return IOT_ERROR;
        }

        value = value * 10 + (*line - '0');
    }

    return (value < 0) ? IOT_ERROR : value;
}


int iot_hextoi(u_char *line, size_t n)
{
    u_char     ch;
    int value;

    if (n == 0) 
    {
        return IOT_ERROR;
    }

    for (value = 0; n--; line++) 
    {
        ch = *line;

        if (ch >= '0' && ch <= '9') 
        {
            value = value * 16 + (ch - '0');
            continue;
        }

        if (ch >= 'A' && ch <= 'F') 
        {
            value = value * 16 + (ch - 'A' + 10);
            continue;
        }

        if (ch >= 'a' && ch <= 'f') 
        {
            value = value * 16 + (ch - 'a' + 10);
            continue;
        }

        return IOT_ERROR;
    }

    return (value < 0) ? IOT_ERROR : value;
}


void iot_md5_text(u_char *text, u_char *md5)
{
    int            i;
    static u_char  hex[] = "0123456789abcdef";

    for (i = 0; i < 16; i++) 
    {
        *text++ = hex[md5[i] >> 4];
        *text++ = hex[md5[i] & 0xf];
    }

    *text = '\0';
}


void iot_encode_base64(iot_str_t *dst, iot_str_t *src)
{
    u_char         *d, *s;
    size_t          len;
    static u_char   basis64[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    len = src->len;
    s = src->data;
    d = dst->data;

    while (len > 2) 
   {
        *d++ = basis64[(s[0] >> 2) & 0x3f];
        *d++ = basis64[((s[0] & 3) << 4) | (s[1] >> 4)];
        *d++ = basis64[((s[1] & 0x0f) << 2) | (s[2] >> 6)];
        *d++ = basis64[s[2] & 0x3f];

        s += 3;
        len -= 3;
    }

    if (len) {
        *d++ = basis64[(s[0] >> 2) & 0x3f];

        if (len == 1) {
            *d++ = basis64[(s[0] & 3) << 4];
            *d++ = '=';

        } else {
            *d++ = basis64[((s[0] & 3) << 4) | (s[1] >> 4)];
            *d++ = basis64[(s[1] & 0x0f) << 2];
        }

        *d++ = '=';
    }

    dst->len = d - dst->data;
}


int iot_decode_base64(iot_str_t *dst, iot_str_t *src)
{
    size_t          len;
    u_char         *d, *s;
    static u_char   basis64[] =
        { 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 62, 77, 77, 77, 63,
          52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 77, 77, 77, 77, 77, 77,
          77,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
          15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 77, 77, 77, 77, 77,
          77, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
          41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 77, 77, 77, 77, 77,

          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
          77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77 };

    for (len = 0; len < src->len; len++) {
        if (src->data[len] == '=') {
            break;
        }

        if (basis64[src->data[len]] == 77) {
            return IOT_ERROR;
        }
    }

    if (len % 4 == 1) {
        return IOT_ERROR;
    }

    s = src->data;
    d = dst->data;

    while (len > 3) {
        *d++ = (u_char) (basis64[s[0]] << 2 | basis64[s[1]] >> 4);
        *d++ = (u_char) (basis64[s[1]] << 4 | basis64[s[2]] >> 2);
        *d++ = (u_char) (basis64[s[2]] << 6 | basis64[s[3]]);

        s += 4;
        len -= 4;
    }

    if (len > 1) {
        *d++ = (u_char) (basis64[s[0]] << 2 | basis64[s[1]] >> 4);
    }

    if (len > 2) {
        *d++ = (u_char) (basis64[s[1]] << 4 | basis64[s[2]] >> 2);
    }

    dst->len = d - dst->data;

    return IOT_OK;
}


size_t iot_utf_length(iot_str_t *utf)
{
    u_char      c;
    size_t      len;
    uint32_t  i;

    for (len = 0, i = 0; i < utf->len; len++, i++) {

        c = utf->data[i];

        if (c < 0x80) {
            continue;
        }

        if (c >= 0xc0) {
            for (c <<= 1; c & 0x80; c <<= 1) {
                i++;
            }

            continue;
        }

        /* invalid utf */

        return utf->len;
    }

    return len;
}


u_char *iot_utf_cpystrn(u_char *dst, u_char *src, size_t n)
{
    u_char  c;

    if (n == 0) {
        return dst;
    }

    for ( /* void */ ; --n; dst++, src++) {

        c = *src;
        *dst = c;

        if (c < 0x80) {
            if (*dst != '\0') {
                continue;
            }

            return dst;
        }

        if (c >= 0xc0) {
            for (c <<= 1; c & 0x80; c <<= 1) {
               *++dst = *++src;
            }

            continue;
        }

        /* invalid utf */
    }

    *dst = '\0';

    return dst;
}


void *iot_memcpy(void *dst, void *src, size_t n)
{
    return memcpy(dst, src, n);
}

