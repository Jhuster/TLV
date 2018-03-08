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
#include <stdio.h>
#include <string.h>
#include "tlv_box.h"

#define TEST_TYPE_0 0x00
#define TEST_TYPE_1 0x01
#define TEST_TYPE_2 0x02
#define TEST_TYPE_3 0x03
#define TEST_TYPE_4 0x04
#define TEST_TYPE_5 0x05
#define TEST_TYPE_6 0x06
#define TEST_TYPE_7 0x07
#define TEST_TYPE_8 0x08
#define TEST_TYPE_9 0x09

#define LOG(format,...) printf(format, ##__VA_ARGS__)

int main(int argc, char const *argv[])
{
    tlv_box_t *box = tlv_box_create();    
    tlv_box_put_char(box, TEST_TYPE_1, 'x');
    tlv_box_put_short(box, TEST_TYPE_2, (short)2);
    tlv_box_put_int(box, TEST_TYPE_3, (int)3);
    tlv_box_put_long(box, TEST_TYPE_4, (long)4);
    tlv_box_put_float(box, TEST_TYPE_5, (float)5.67);
    tlv_box_put_double(box, TEST_TYPE_6, (double)8.91);
    tlv_box_put_string(box, TEST_TYPE_7, (char *)"hello world !");    
    unsigned char array[6] = {1, 2, 3, 4, 5, 6};
    tlv_box_put_bytes(box,TEST_TYPE_8, array, 6);    

    if (tlv_box_serialize(box) != 0) {
        LOG("box serialize failed !\n");
        return -1;
    }

    LOG("box serialize success, %d bytes \n", tlv_box_get_size(box));

    tlv_box_t *boxes = tlv_box_create();  
    tlv_box_put_object(boxes, TEST_TYPE_9, box);
    
    if (tlv_box_serialize(boxes) != 0) {
        LOG("boxes serialize failed !\n"); 
        return -1;
    }

    LOG("boxes serialize success, %d bytes \n", tlv_box_get_size(boxes));
    
    tlv_box_t *parsedBoxes = tlv_box_parse(tlv_box_get_buffer(boxes), tlv_box_get_size(boxes));

    LOG("boxes parse success, %d bytes \n", tlv_box_get_size(parsedBoxes));

    tlv_box_t* parsedBox;
    if (tlv_box_get_object(parsedBoxes, TEST_TYPE_9, &parsedBox) != 0) {
        LOG("tlv_box_get_object failed !\n");
        return -1;
    }

    LOG("box parse success, %d bytes \n", tlv_box_get_size(parsedBox));

    {
        char value;
        if (tlv_box_get_char(parsedBox, TEST_TYPE_1, &value) != 0) {
            LOG("tlv_box_get_char failed !\n");  
            return -1;
        }
        LOG("tlv_box_get_char success %c \n", value);
    }

    {
        short value;
        if (tlv_box_get_short(parsedBox, TEST_TYPE_2, &value) != 0) {
            LOG("tlv_box_get_short failed !\n");             
            return -1;
        }
        LOG("tlv_box_get_short success %d \n", value);
    }

    {
        int value;
        if (tlv_box_get_int(parsedBox, TEST_TYPE_3, &value) != 0) {
            LOG("tlv_box_get_int failed !\n");            
            return -1;
        }
        LOG("tlv_box_get_int success %d \n", value);
    }

    {
        long value;
        if (tlv_box_get_long(parsedBox, TEST_TYPE_4, &value) != 0) {
            LOG("tlv_box_get_long failed !\n");            
            return -1;
        }
        LOG("tlv_box_get_long success %ld \n", value);
    }

    {
        float value;
        if (tlv_box_get_float(parsedBox, TEST_TYPE_5, &value) != 0) {
            LOG("tlv_box_get_float failed !\n");            
            return -1;
        }
        LOG("tlv_box_get_float success %f \n", value);
    }

    {
        double value;
        if (tlv_box_get_double(parsedBox, TEST_TYPE_6, &value) != 0) {
            LOG("tlv_box_get_double failed !\n");            
            return -1;
        }
        LOG("tlv_box_get_double success %f \n", value);
    }

    {
        char value[128]; 
        int length = 128;
        if (tlv_box_get_string(parsedBox, TEST_TYPE_7, value, &length) != 0) {
            LOG("tlv_box_get_string failed !\n");            
            return -1;
        }
        LOG("tlv_box_get_string success %s \n", value);
    }

    {
        unsigned char value[128]; 
        int length = 128;
        if (tlv_box_get_bytes(parsedBox,TEST_TYPE_8, value, &length) != 0) {
            LOG("tlv_box_get_bytes failed !\n"); 
            return -1;
        }        

        LOG("tlv_box_get_bytes success:  ");         
        int i = 0;
        for(i=0; i<length; i++) {
            LOG("%d-", value[i]); 
        }        
        LOG("\n");
    }

    tlv_box_destroy(box);
    tlv_box_destroy(boxes);
    tlv_box_destroy(parsedBox);
    tlv_box_destroy(parsedBoxes);

    return 0;
}
