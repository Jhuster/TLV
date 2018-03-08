/*
 *  COPYRIGHT NOTICE  
 *  Copyright (C) 2015, Jhuster, All Rights Reserved
 *  Author: Jhuster(lujun.hust@gmail.com)
 *  
 *  https://github.com/Jhuster/TLV
 *   
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation; either version 2.1 of the License, 
 *  or (at your option) any later version.
 */
#include "key_list.h"

key_list_t *key_list_create(value_releaser releaser) 
{
    key_list_t * list = (key_list_t * )malloc(sizeof(key_list_t));
    list->count = 0;
    list->header = NULL;
    list->releaser = releaser;
    return list;
}

int key_list_destroy(key_list_t *list) 
{
    key_list_node_t *current = list->header;    
    while (current != NULL) {
        key_list_node_t *next = current->next;
        list->releaser(current->value);  
        free(current);        
        current = next;
    }
    free(list);
    return 0;
}

int key_list_count(key_list_t *list) 
{
    return list->count;    
}

int key_list_keyset(key_list_t *list, key_t* array, int array_size)
{    
    if (array_size < list->count) {
        return -1;
    }

    int i = 0;
    key_list_node_t *current = list->header;
    while (current != NULL) {
        array[i] = current->key; 
        current = current->next;
        i++;
    }

    return i; 
}

static key_list_node_t* key_list_get_node(key_list_t *list, key_t key) 
{
    key_list_node_t *current = list->header;    
    while (current != NULL) {
        if (key_compare(key,current->key)) {
            return current;
        }       
        current = current->next;
    }
    return NULL;
}

static int key_list_remove_node(key_list_t *list, key_list_node_t *node) 
{
    if (node == list->header) {
        list->header = node->next;
    }
    else {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;                        
    }         

    list->releaser(node->value); 

    free(node);
    list->count--;

    return 0;
}

int key_list_find_key(key_list_t *list, key_t key) 
{
    return key_list_get_node(list,key) != NULL;
}

int key_list_add(key_list_t *list, key_t key, value_t value)
{
    if (key_list_find_key(list, key)) {
        return -1;
    }

    key_list_node_t* node = calloc(1, sizeof(key_list_node_t));
    if (node == NULL) {
        return -1;
    }

    node->key = key;
    node->value = value;
    node->prev = NULL;
    node->next = NULL;

    if (list->header != NULL) {
        node->next = list->header;
        list->header->prev = node;                
    }
    list->header = node;      
    list->count++;

    return 0;   
}

int key_list_get(key_list_t *list, key_t key, value_t *value) 
{
    key_list_node_t* node = key_list_get_node(list, key);
    if (node == NULL) {
        return -1;
    }
    *value = node->value;
    return 0;
}

int key_list_edit(key_list_t *list, key_t key, value_t value)
{
    key_list_node_t* node = key_list_get_node(list, key);
    if (node == NULL) {
        return -1;
    }
    node->value = value;
    return 0;
}

int key_list_delete(key_list_t *list, key_t key) 
{
    key_list_node_t* node = key_list_get_node(list, key);
    if (node == NULL) {
        return -1;
    }

    return key_list_remove_node(list, node);
}
