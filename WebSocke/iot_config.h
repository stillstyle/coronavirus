
/*
 * Copyright (C) K
 */


#ifndef _IOT_CONFIG_H_
#define _IOT_CONFIG_H_


#include "iot_linux_config.h"



#ifndef IOT_HAVE_SO_SNDLOWAT
#define IOT_HAVE_SO_SNDLOWAT     1
#endif



#define IOT_INVALID_ARRAY_INDEX 0x80000000



#define IOT_INT_T_LEN   sizeof("-2147483648") - 1



#define IOT_INT32_LEN   sizeof("-2147483648") - 1
#define IOT_INT64_LEN   sizeof("-9223372036854775808") - 1



#define iot_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define iot_align_ptr(p, a)                                                   \
    (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))


#define iot_abort       abort


#define IOT_ACCEPT_THRESHOLD   100



#define IOT_MAXHOSTNAMELEN 64



#if ((__GNU__ == 2) && (__GNUC_MINOR__ < 8))
#define IOT_MAX_UINT32_VALUE  (uint32_t) 0xffffffffLL
#else
#define IOT_MAX_UINT32_VALUE  (uint32_t) 0xffffffff
#endif






void get_config_svalue(uint8_t *pszSectionName, uint8_t *pszKeyName, uint8_t *pDefaultVal, uint8_t *pszOutput, uint32_t iOutputLen, uint8_t *pszConfigFileName);
int get_config_ivalue(uint8_t *pszSectionName, uint8_t *pszKeyName, uint32_t iDefaultVal, uint8_t *pszConfigFileName);




#endif /* _IOT_CONFIG_H_INCLUDED_ */
