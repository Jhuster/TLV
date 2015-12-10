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

#define TLV_TYPE_OBJECTS   0xff

#define TLV_TYPE_USERNAME  0x01
#define TLV_TYPE_PASSWORD  0x02
#define TLV_TYPE_SEX       0x03
#define TLV_TYPE_AGE       0x04
#define TLV_TYPE_SNO       0x05
#define TLV_TYPE_SCORE     0x06

#define LOG(format,...) printf(format,##__VA_ARGS__)

typedef struct _file_header_t
{
    char startcode[4];
    int content_length;
} file_header_t;

typedef struct _student_t
{
    char username[20];
    char sex;
    int  age;
    long long sno;
    float score;
} student_t;

static int test_write_tlv()
{
    const char *filepath = "student.txt";
    FILE *wp = fopen(filepath,"wb");
    if(wp == NULL) {
        LOG("failed to open %s\n",filepath);
        return -1;
    }

    student_t student;
    strcpy(student.username,"jhuster");
    student.sex = 1;
    student.age = 28;
    student.sno = 1234567890;
    student.score = 98.55;

    tlv_t *object = tlv_create();
    tlv_put_char(object,TLV_TYPE_SEX,&student.sex);
    tlv_put_string(object,TLV_TYPE_USERNAME,student.username);
    tlv_put_int(object,TLV_TYPE_AGE,&student.age);
    tlv_put_longlong(object,TLV_TYPE_SNO,&student.sno);
    tlv_put_float(object,TLV_TYPE_SCORE,&student.score);

    if(tlv_serialize(object) != 0) {
        LOG("failed to serialize object !\n");
        fclose(wp);
        return -1;
    }

    tlv_t *objects = tlv_create();
    tlv_put_object(objects,TLV_TYPE_OBJECTS,object);    
    if(tlv_serialize(objects) != 0) {
        LOG("failed to serialize objects !\n");
        fclose(wp);
        return -1;
    }

    file_header_t header;
    header.startcode[0] = 0x0A;
    header.startcode[1] = 0x0B;
    header.startcode[2] = 0x0C;
    header.startcode[3] = 0x0D;
    header.content_length = tlv_get_size(objects);

    if(fwrite(&header,sizeof(header),1,wp) != 1) {
        LOG("failed to write file_header_t !\n");
        fclose(wp);
        return -1;
    }

    if(fwrite(tlv_get_buffer(objects),tlv_get_size(objects),1,wp) != 1) {
        LOG("failed to write objects !\n");
        fclose(wp);
        return -1;
    }

    fclose(wp);

    tlv_destroy(object);
    tlv_destroy(objects);

    LOG("Write student success !\n");

    return 0;
}

static int test_read_tlv()
{
    const char *filepath = "student.txt";
    FILE *rp = fopen(filepath,"rb");
    if(rp == NULL) {
        LOG("failed to open %s\n",filepath);
        return -1;
    }

    file_header_t header;
    if(fread(&header,sizeof(header),1,rp) != 1) {
        LOG("failed to read file_header_t !\n");
        fclose(rp);
        return -1;
    }

    if(header.startcode[0] != 0x0A || header.startcode[1] != 0x0B ||
       header.startcode[2] != 0x0C || header.startcode[3] != 0x0D) {
        LOG("invalid file_header_t !\n");
        fclose(rp);
        return -1;
    }

    unsigned char *buffer = (unsigned char*)malloc(header.content_length*sizeof(char));
    if(fread(buffer,header.content_length,1,rp) != 1) {
        LOG("failed to read student !\n");
        fclose(rp);
        return -1;
    }

    tlv_t* objects = tlv_parse(buffer,header.content_length);
    if(objects == NULL) {
        LOG("failed to do parse !\n");
        fclose(rp);
        return -1;
    }
    free(buffer);
    fclose(rp);

    tlv_t* object = NULL;
    if(tlv_get_object(objects,TLV_TYPE_OBJECTS,&object) != 0) {
        LOG("failed get_object !\n");
        return -1;
    }

    student_t student;
    int usernameLen = 20;
    tlv_get_char(object,TLV_TYPE_SEX,&student.sex);
    tlv_get_string(object,TLV_TYPE_USERNAME,student.username,&usernameLen);
    tlv_get_int(object,TLV_TYPE_AGE,&student.age);
    tlv_get_longlong(object,TLV_TYPE_SNO,&student.sno);
    tlv_get_float(object,TLV_TYPE_SCORE,&student.score);    

    LOG("Read student success, sex = %d, username = %s, age = %d, sno = %lld, score = %0.2f \n",
         student.sex,student.username,student.age,student.sno,student.score);

    tlv_destroy(object);
    tlv_destroy(objects);

    return 0;
}

int main(int argc, char const *argv[])
{
    if(test_write_tlv() == 0 && test_read_tlv() == 0) {
        LOG("All tests passed !\n");
    }

    return 0;
}
