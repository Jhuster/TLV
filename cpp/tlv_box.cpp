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

#include <string.h>
#include <stdio.h>
#include "tlv.h"
#include "tlv_box.h"
using std::string;

namespace tlv
{

TlvBox::TlvBox() : mSerializedBuffer(NULL),mSerializedBytes(0)
{

}

TlvBox::~TlvBox()
{
    if (mSerializedBuffer != NULL) {
        delete[] mSerializedBuffer;
        mSerializedBuffer = NULL;
    }

    std::map<int,Tlv*>::iterator itor;
    for(itor=mTlvMap.begin(); itor != mTlvMap.end(); itor++) {
        delete itor->second;
    }

    mTlvMap.clear();
}
//将int序列化为8字节的16进制数字，避免大小端的问题，因此会有16字节的开销
bool TlvBox::Serialize()
{
    if (mSerializedBuffer != NULL) {
        return false;
    }

    int offset = 0;
    //预留一个是为了放\0,序列话里面的字符有可能会有\0
    mSerializedBuffer = new unsigned char[mSerializedBytes+1];
    mSerializedBuffer[mSerializedBytes]='\0';

    std::map<int,Tlv*>::iterator itor;
    for(itor=mTlvMap.begin();itor!=mTlvMap.end();itor++) {    
        int type = itor->second->GetType();
        offset+=snprintf((char*)mSerializedBuffer+offset,9,"%08x",type);
        int length = itor->second->GetLength();
        offset+=snprintf((char*)mSerializedBuffer+offset,9,"%08x",length);
        memcpy(mSerializedBuffer+offset,itor->second->GetValue(),length);        
        offset += length;
    }

    return true;
}

bool TlvBox::Parse(const unsigned char *buffer,int buffersize)
{
    if (mSerializedBuffer != NULL || buffer == NULL) {
        return false;
    }
    unsigned char* cached=new unsigned char[buffersize];
    memcpy(cached,buffer,buffersize);

    int offset = 0;
    while (offset < buffersize) {
        //判断合法性
        if(offset+16>buffersize){
            delete cached;
            return false;
        }
        unsigned char temp=cached[offset+8];
        cached[offset+8]='\0';
        int type;
        sscanf((char*)cached+offset,"%x",&type);
        offset += 8;
        cached[offset]=temp;
        temp=cached[offset+8];
        cached[offset+8]='\0';
        int length;
        sscanf((char*)cached+offset,"%x",&length);
        offset += 8;
        cached[offset]=temp;
        if(offset+length>buffersize){
            delete cached;
            return false;
        }
        PutValue(new Tlv(type,cached+offset,length));
        offset += length;
    }

    mSerializedBuffer = cached;
    mSerializedBytes  = buffersize;

    return true;
}

unsigned char * TlvBox::GetSerializedBuffer() const
{
    return mSerializedBuffer;
}

int TlvBox::GetSerializedBytes() const
{
    return mSerializedBytes;
}

bool TlvBox::PutValue(Tlv *value)
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(value->GetType());
    if (itor != mTlvMap.end()) {
        delete itor->second;        
    } else {
        mSerializedBytes += (16+value->GetLength());
    }   

    mTlvMap.insert(std::pair<int,Tlv*>(value->GetType(),value));  

    return true;
}

bool TlvBox::PutBoolValue(int type,bool value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }

    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutCharValue(int type,char value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutShortValue(int type,short value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutIntValue(int type,int value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutLongValue(int type,long value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutLongLongValue(int type,long long value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutFloatValue(int type,float value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutDoubleValue(int type,double value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutStringValue(int type,char *value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutStringValue(int type,const std::string &value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value));
}

bool TlvBox::PutBytesValue(int type,unsigned char *value,int length)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    return PutValue(new Tlv(type,value,length));
}

bool TlvBox::PutObjectValue(int type,const TlvBox& value)
{
    if (mSerializedBuffer != NULL) {
        return false;
    }
    unsigned char *buffer = value.GetSerializedBuffer();
    if (buffer == NULL) {
        return false;
    }
    return PutValue(new Tlv(type,buffer,value.GetSerializedBytes()));
}

bool TlvBox::GetBoolValue(int type,bool &value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {
        return itor->second->to_bool(value);
    }
    return false;
}

bool TlvBox::GetCharValue(int type,char &value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {
        return itor->second->to_char(value);
    }
    return false;
}

bool TlvBox::GetShortValue(int type,short &value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {
        return itor->second->to_short(value);
    }
    return false;
}

bool TlvBox::GetIntValue(int type,int &value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {
        return itor->second->to_int(value);
    }
    return false;
}

bool TlvBox::GetLongValue(int type,long &value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {
        return itor->second->to_long(value);
    }
    return false;
}

bool TlvBox::GetLongLongValue(int type,long long &value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {
        return itor->second->to_longlong(value);
    }
    return false;
}

bool TlvBox::GetFloatValue(int type,float& value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {
        return itor->second->to_float(value);
    }
    return false;
}

bool TlvBox::GetDoubleValue(int type,double& value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {
        return itor->second->to_double(value);
    }
    return false;
}

bool TlvBox::GetStringValue(int type,char *value,int &length) const
{
    return GetBytesValue(type,(unsigned char *)value,length);
}

bool TlvBox::GetStringValue(int type,std::string &value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor != mTlvMap.end()) {        
        return itor->second->to_string(value);
    }
    return false;
}

bool TlvBox::GetBytesValue(int type,unsigned char *value,int &length) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor == mTlvMap.end()) {
        return false;
    }

    if (length < itor->second->GetLength()) {
        return false;
    }

    memset(value,0,length);
    length = itor->second->GetLength();
    memcpy(value,itor->second->GetValue(),length);

    return true;
}

bool TlvBox::GetBytesValuePtr(int type,unsigned char **value,int &length) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor == mTlvMap.end()) {
        return false;        
    }
    *value = itor->second->GetValue();
    length = itor->second->GetLength();    
    return true;
}

bool TlvBox::GetObjectValue(int type,TlvBox& value) const
{
    std::map<int,Tlv*>::const_iterator itor = mTlvMap.find(type);
    if (itor == mTlvMap.end()) {
        return false;    
    }
    return value.Parse(itor->second->GetValue(),itor->second->GetLength());
}


} //namespace 
