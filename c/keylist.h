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
#ifndef _KEY_LIST_H_
#define _KEY_LIST_H_

#include <stdlib.h>

typedef struct _value {
    int type;
    int length;
    void *value;
} value_t;

typedef int key_t;

#define key_compare(a,b) ((a==b)?1:0)

typedef struct key_list_node { 
    key_t key;
    value_t value;
    struct key_list_node *prev;
    struct key_list_node *next;
} key_list_node_t;

typedef struct key_list {
    int count;
    key_list_node_t *header;      
} key_list_t;

key_list_t *key_list_create();
int key_list_destroy(key_list_t *list);

int key_list_count(key_list_t *list);
int key_list_keyset(key_list_t *list,key_t* array,int array_size);
int key_list_find_key(key_list_t *list,key_t key);

int key_list_add(key_list_t *list,key_t key,value_t value);
int key_list_get(key_list_t *list,key_t key,value_t *value);
int key_list_edit(key_list_t *list,key_t key,value_t value);
int key_list_delete(key_list_t *list,key_t key);

#define key_list_foreach(L,V) key_list_node_t *_node = NULL;\
    key_list_node_t* V;\
    for(V = _node = L->header; _node != NULL; V = _node = _node->next)

#endif
