/*
 *  COPYRIGHT NOTICE  
 *  Copyright (C) 2015, Jhuster, All Rights Reserved
 *  Author: Jhuster(lujun.hust@gmail.com)
 *  
 *  https://github.com/Jhuster/TLV
 *   
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.  
 */
#ifndef _TLV_H_
#define _TLV_H_

#include "key_list.h"

typedef struct _tlv {
    key_list_t *m_list;
    unsigned char *m_serialized_buffer;
    int m_serialized_bytes;
} tlv_t;

tlv_t *tlv_create();
tlv_t *tlv_parse(unsigned char *buffer,int buffersize);
int tlv_destroy(tlv_t *tlv);

unsigned char *tlv_get_buffer(tlv_t *tlv);
int tlv_get_size(tlv_t *tlv);

int tlv_put_char(tlv_t *tlv,int type,char *value);
int tlv_put_short(tlv_t *tlv,int type,short *value);
int tlv_put_int(tlv_t *tlv,int type,int *value);
int tlv_put_long(tlv_t *tlv,int type,long *value);
int tlv_put_longlong(tlv_t *tlv,int type,long long *value);
int tlv_put_float(tlv_t *tlv,int type,float *value);
int tlv_put_double(tlv_t *tlv,int type,double *value);
int tlv_put_string(tlv_t *tlv,int type,char *value);
int tlv_put_bytes(tlv_t *tlv,int type,unsigned char *value,int length);
int tlv_put_object(tlv_t *tlv,int type,tlv_t *object);
int tlv_serialize(tlv_t *tlv);

int tlv_get_char(tlv_t *tlv,int type,char *value);
int tlv_get_short(tlv_t *tlv,int type,short *value);
int tlv_get_int(tlv_t *tlv,int type,int *value);
int tlv_get_long(tlv_t *tlv,int type,long *value);
int tlv_get_longlong(tlv_t *tlv,int type,long long *value);
int tlv_get_float(tlv_t *tlv,int type,float *value);
int tlv_get_double(tlv_t *tlv,int type,double *value);
int tlv_get_string(tlv_t *tlv,int type,char *value,int* length);
int tlv_get_bytes(tlv_t *tlv,int type,unsigned char *value,int* length);
int tlv_get_bytes_ptr(tlv_t *tlv,int type,unsigned char **value,int* length);
int tlv_get_object(tlv_t *tlv,int type,tlv_t **object);

#endif //_TLV_H_
