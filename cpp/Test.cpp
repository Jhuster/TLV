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
#include <string>
#include "TlvBox.h"

using namespace tlv;

#define TLV_TYPE_OBJECT    0xff

#define TLV_TYPE_USERNAME  0x01
#define TLV_TYPE_PASSWORD  0x02
#define TLV_TYPE_SEX       0x03
#define TLV_TYPE_AGE       0x04
#define TLV_TYPE_SNO       0x05
#define TLV_TYPE_SCORE     0x06

#define LOG(format,...) printf(format,##__VA_ARGS__)

typedef struct tagFileHeader
{
    char startcode[4];
    int content_length;
} FileHeader;

typedef struct tagStudent
{
    std::string username;
    char sex;
    int  age;
    long long sno;
    float score;
} Student;

static bool test_write_tlv()
{
    const char *filepath = "student.txt";
    FILE *wp = fopen(filepath,"wb");
    if(wp == NULL) {
        LOG("failed to open %s\n",filepath);
        return false;
    }

    Student student;
    student.username = "jhuster";
    student.sex = 1;
    student.age = 28;
    student.sno = 1234567890;
    student.score = 98.55;

    TlvBox box;
    box.PutCharValue(TLV_TYPE_SEX,student.sex);
    box.PutStringValue(TLV_TYPE_USERNAME,student.username);
    box.PutIntValue(TLV_TYPE_AGE,student.age);
    box.PutLongLongValue(TLV_TYPE_SNO,student.sno);
    box.PutFloatValue(TLV_TYPE_SCORE,student.score);
    if(!box.Serialize()) {
        LOG("failed to do Serialize box !\n");
        fclose(wp);
        return false;
    }

    TlvBox boxes;
    boxes.PutObjectValue(TLV_TYPE_OBJECT,box);
    if(!boxes.Serialize()) {
        LOG("failed to do Serialize boxes !\n");
        fclose(wp);
        return false;
    }

    FileHeader header;
    header.startcode[0] = 0x0A;
    header.startcode[1] = 0x0B;
    header.startcode[2] = 0x0C;
    header.startcode[3] = 0x0D;
    header.content_length = boxes.GetSerializedBytes();

    if(fwrite(&header,sizeof(header),1,wp) != 1) {
        LOG("failed to write FileHeader !\n");
        fclose(wp);
        return false;
    }

    if(fwrite(boxes.GetSerializedBuffer(),boxes.GetSerializedBytes(),1,wp) != 1) {
        LOG("failed to write TlvBox !\n");
        fclose(wp);
        return false;
    }

    fclose(wp);

    LOG("Write student success !\n");

    return true;
}

static bool test_read_tlv()
{
    const char *filepath = "student.txt";
    FILE *rp = fopen(filepath,"rb");
    if(rp == NULL) {
        LOG("failed to open %s\n",filepath);
        return -1;
    }

    FileHeader header;
    if(fread(&header,sizeof(header),1,rp) != 1) {
        LOG("failed to read FileHeader !\n");
        fclose(rp);
        return false;
    }

    if(header.startcode[0] != 0x0A || header.startcode[1] != 0x0B ||
       header.startcode[2] != 0x0C || header.startcode[3] != 0x0D) {
        LOG("invalid FileHeader !\n");
        fclose(rp);
        return false;
    }

    unsigned char *buffer = new unsigned char[header.content_length];
    if(fread(buffer,header.content_length,1,rp) != 1) {
        LOG("failed to read student !\n");
        fclose(rp);
        return false;
    }

    TlvBox boxes;
    if(!boxes.Parse(buffer,header.content_length)) {
        LOG("failed to do Parse !\n");
        fclose(rp);
        return false;
    }
    delete[] buffer;

    TlvBox box;
    boxes.GetObjectValue(TLV_TYPE_OBJECT,box);

    Student student;
    box.GetCharValue(TLV_TYPE_SEX,student.sex);
    box.GetStringValue(TLV_TYPE_USERNAME,student.username);
    box.GetIntValue(TLV_TYPE_AGE,student.age);
    box.GetLongLongValue(TLV_TYPE_SNO,student.sno);
    box.GetFloatValue(TLV_TYPE_SCORE,student.score);

    LOG("Read student success, sex = %d, username = %s, age = %d, sno = %lld, score = %0.2f \n",
         student.sex,student.username.c_str(),student.age,student.sno,student.score);

    fclose(rp);

    return true;
}

int main(int argc, char const *argv[])
{
    if(test_write_tlv() && test_read_tlv()) {
        LOG("All tests passed !\n");
    }

    return 0;
}
