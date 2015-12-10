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
#include <stdio.h>
#include <string.h>
#include "tlv.h"

tlv_t *tlv_create()
{
    tlv_t* tlv = calloc(1,sizeof(tlv_t));
    tlv->m_list = key_list_create();
    tlv->m_serialized_buffer = NULL;
    tlv->m_serialized_bytes = 0;
    return tlv;
}

tlv_t *tlv_parse(unsigned char *buffer,int buffersize)
{
    tlv_t *tlv = tlv_create();

    unsigned char *cached = (unsigned char*)malloc(buffersize);
    memcpy(cached,buffer,buffersize);

    int offset = 0, length = 0;
    while(offset < buffersize) {
        int type = ntohl((*(int *)(cached+offset)));
        offset += sizeof(int);
        int length = ntohl((*(int *)(cached+offset)));
        offset += sizeof(int);
        tlv_put_value(tlv,type,cached+offset,length);
        offset += length;
    }

    tlv->m_serialized_buffer = cached;
    tlv->m_serialized_bytes  = buffersize;

    return tlv;
}

int tlv_destroy(tlv_t *tlv)
{
    key_list_destroy(tlv->m_list);
    if(tlv->m_serialized_buffer != NULL) {
        free(tlv->m_serialized_buffer);        
    }

    free(tlv);

    return 0;
}

unsigned char *tlv_get_buffer(tlv_t *tlv)
{
    return tlv->m_serialized_buffer;
}

int tlv_get_size(tlv_t *tlv)
{
    return tlv->m_serialized_bytes;
}

int tlv_put_value(tlv_t *tlv,int type,void *value,int length)
{
    if(tlv->m_serialized_buffer != NULL) {
        return -1;
    }

    value_t _value;
    _value.type = type;
    _value.value = value;
    _value.length = length; 

    if(key_list_add(tlv->m_list,type,_value) != 0) {
        return -1;
    }    
    tlv->m_serialized_bytes += sizeof(int)*2+length;
    
    return 0;
}

int tlv_put_char(tlv_t *tlv,int type,char *value)
{
    return tlv_put_value(tlv,type,value,sizeof(char));
}

int tlv_put_short(tlv_t *tlv,int type,short *value)
{
    return tlv_put_value(tlv,type,value,sizeof(short));
}

int tlv_put_int(tlv_t *tlv,int type,int *value)
{
    return tlv_put_value(tlv,type,value,sizeof(int));
}

int tlv_put_long(tlv_t *tlv,int type,long *value)
{
    return tlv_put_value(tlv,type,value,sizeof(long));
}

int tlv_put_longlong(tlv_t *tlv,int type,long long *value)
{
    return tlv_put_value(tlv,type,value,sizeof(long long));
}

int tlv_put_float(tlv_t *tlv,int type,float *value)
{
    return tlv_put_value(tlv,type,value,sizeof(float));
}

int tlv_put_double(tlv_t *tlv,int type,double *value)
{
    return tlv_put_value(tlv,type,value,sizeof(double));
}

int tlv_put_string(tlv_t *tlv,int type,char *value)
{
    return tlv_put_value(tlv,type,value,strlen(value)+1);
}

int tlv_put_bytes(tlv_t *tlv,int type,unsigned char *value,int length)
{
    return tlv_put_value(tlv,type,value,length);
}

int tlv_put_object(tlv_t *tlv,int type,tlv_t *object)
{
    return tlv_put_value(tlv,type,tlv_get_buffer(object),tlv_get_size(object));
}

int tlv_serialize(tlv_t *tlv)
{
    if(tlv->m_serialized_buffer != NULL) {
        return -1;
    }

    int offset = 0;
    unsigned char* buffer = (unsigned char*)malloc(tlv->m_serialized_bytes);    
    key_list_foreach(tlv->m_list,node) {
        int type = htonl(node->value.type);
        memcpy(buffer+offset,&type,sizeof(int));
        offset += sizeof(int);
        int length = htonl(node->value.length);
        memcpy(buffer+offset,&length,sizeof(int));
        offset += sizeof(int);
        memcpy(buffer+offset,node->value.value,node->value.length);
        node->value.value = buffer+offset;
        offset += node->value.length;
    }

    tlv->m_serialized_buffer = buffer;

    return 0;
}

int tlv_get_char(tlv_t *tlv,int type,char *value)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *value = (*(char *)(_value.value));
    return 0;
}

int tlv_get_short(tlv_t *tlv,int type,short *value)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *value = (*(short *)(_value.value));
    return 0;
}

int tlv_get_int(tlv_t *tlv,int type,int *value)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *value = (*(int *)(_value.value));
    return 0;
}

int tlv_get_long(tlv_t *tlv,int type,long *value)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *value = (*(long *)(_value.value));
    return 0;
}

int tlv_get_longlong(tlv_t *tlv,int type,long long *value)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *value = (*(long long *)(_value.value));
    return 0;
}

int tlv_get_float(tlv_t *tlv,int type,float *value)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *value = (*(float *)(_value.value));
    return 0;
}

int tlv_get_double(tlv_t *tlv,int type,double *value)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *value = (*(double *)(_value.value));
    return 0;
}

int tlv_get_string(tlv_t *tlv,int type,char *value,int* length)
{
    return tlv_get_bytes(tlv,type,value,length);
}

int tlv_get_bytes(tlv_t *tlv,int type,unsigned char *value,int* length)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0 || *length < _value.length) {
        return -1;
    }
    memset(value,0,*length);
    *length = _value.length;
    memcpy(value,_value.value,_value.length);
    return 0;
}

int tlv_get_bytes_ptr(tlv_t *tlv,int type,unsigned char **value,int* length)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *value  = _value.value;
    *length = _value.length;
    return 0;
}

int tlv_get_object(tlv_t *tlv,int type,tlv_t **object)
{
    value_t _value;
    if(key_list_get(tlv->m_list,type,&_value) != 0) {
        return -1;
    }
    *object = tlv_parse(_value.value,_value.length);
    return 0;
}