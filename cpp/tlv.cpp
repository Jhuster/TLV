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
#pragma one
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "tlv.h"
#define TLV_BUF_SIZE 24
namespace tlv
{

Tlv::Tlv(int type,bool value) : mType(type)
{
    char buf[TLV_BUF_SIZE]; 
    buf[0]=value?'0':'1';
    Initialize(buf,1);
}

Tlv::Tlv(int type,char value) : mType(type)
{
    char buf[TLV_BUF_SIZE]; 
    buf[0]=value;
    Initialize(buf,1);
}

Tlv::Tlv(int type,short value) : mType(type)
{
    char buf[TLV_BUF_SIZE];
    size_t len=snprintf(buf,sizeof(buf),"%hx",value);
    Initialize(buf,len);
}

Tlv::Tlv(int type,int value) : mType(type)
{
    char buf[TLV_BUF_SIZE];
    size_t len=snprintf(buf,sizeof(buf),"%x",value);
    Initialize(buf,len);
}

Tlv::Tlv(int type,long value) : mType(type)
{
    char buf[TLV_BUF_SIZE];
    size_t len=snprintf(buf,sizeof(buf),"%lx",value);
    Initialize(buf,len);
}

Tlv::Tlv(int type,long long value) : mType(type)
{
    char buf[TLV_BUF_SIZE];
    size_t len=snprintf(buf,sizeof(buf),"%llx",value);
    Initialize(buf,len);
}

Tlv::Tlv(int type,float value) : mType(type)
{
    char buf[TLV_BUF_SIZE];
    size_t len=snprintf(buf,sizeof(buf),"%f",value);
    Initialize(buf,len);
}

Tlv::Tlv(int type,double value) : mType(type)
{
    char buf[TLV_BUF_SIZE];
    size_t len=snprintf(buf,sizeof(buf),"%lf",value);
    Initialize(buf,len);
}

Tlv::Tlv(int type,char* value) : mType(type)
{
    Initialize(value,strlen(value));
}

Tlv::Tlv(int type,std::string value) : mType(type)
{
    Initialize(value.c_str(),value.size());
}

Tlv::Tlv(int type,unsigned char *value,int length) : mType(type)
{
    Initialize(value,length);
}

Tlv::Tlv(int type,const Tlv& value) : mType(type)
{
    Initialize(value.GetValue(),value.GetLength());
}
bool Tlv::to_bool(bool&value){
    if(!mValue){
        return false;
    }
    switch(mLength){
        case 1:
            switch(mValue[0]){
                case '0':
                    value=false;
                    return true;
                case '1':
                    value=true;
                    return true;
                default:
                    return false;
            }
            return true;
        default:
            return false;
    }
    return false;
}
bool Tlv::to_char(char&value){
    if(!mValue||mLength!=1){
        return false;
    }
    value=mValue[0];
    return true;
}

bool Tlv::to_short(short&value){
    if(!mValue||mLength<=0){
        return false;
    }
    sscanf((char*)mValue,"%hx",&value);
    return true;
}
bool Tlv::to_int(int&value){
    if(!mValue||mLength<=0){
        return false;
    }
    sscanf((char*)mValue,"%x",&value);
    return true;
}
bool Tlv::to_long(long&value){
    if(!mValue||mLength<=0){
        return false;
    }
    sscanf((char*)mValue,"%lx",&value);
    return true;
}
bool Tlv::to_longlong(long long&value){
    if(!mValue||mLength<=0){
        return false;
    }
    sscanf((char*)mValue,"%llx",&value);
    return true;
}
bool Tlv::to_float(float&value){
    if(!mValue||mLength<=0){
        return false;
    }
    sscanf((char*)mValue,"%f",&value);
    return true;
}
bool Tlv::to_double(double&value){
    if(!mValue||mLength<=0){
        return false;
    }
    sscanf((char*)mValue,"%lf",&value);
    return true;
}
bool Tlv::to_string(string&value){
    if(!mValue||mLength<=0){
        return false;
    }
    value.assign((char*)mValue,(size_t)mLength);
    return true;
}
bool Tlv::isdigit(){
    if(!mValue){
        return false;
    }
    if(!(mValue[0]=='+'||mValue[0]=='-'||mValue[0]>='0'&&mValue[0]<='9')){
        return false;
    }
    for(uint32_t i=1;i<mLength;i++){
        if(!(mValue[i]>='0'||mValue[i]<='9')){
            return false;
        }
    }
    return false;
}

Tlv::~Tlv()
{
    delete[] mValue;
}

void Tlv::Initialize(const void *value,int length)
{
    mLength = length;
    mValue = new unsigned char[length+1];
    memcpy(mValue,value,length);
    mValue[length]='\0';
}

int Tlv::GetType() const
{
    return mType;
}

int Tlv::GetLength() const
{
    return mLength;
}

unsigned char *Tlv::GetValue() const
{
    return mValue;
}

}
