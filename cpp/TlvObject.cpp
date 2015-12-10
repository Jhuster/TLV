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
#include <arpa/inet.h>
#include "TlvObject.h"

namespace TLV
{

TlvObject::TlvObject() : mSerializedBuffer(NULL),mSerializedBytes(0)
{

}

TlvObject::~TlvObject()
{
    if(mSerializedBuffer != NULL) {
        delete[] mSerializedBuffer;
        mSerializedBuffer = NULL;
    }
    mTlvMap.clear();
}

bool TlvObject::Serialize()
{
    if(mSerializedBuffer != NULL) {
        return false;
    }

    int offset = 0;
    mSerializedBuffer = new unsigned char[mSerializedBytes];

    std::map<int,Tlv>::iterator itor;
    for(itor=mTlvMap.begin();itor!=mTlvMap.end();itor++) {
        int type = htonl(itor->second.type);
        memcpy(mSerializedBuffer+offset,&type,sizeof(int));
        offset += sizeof(int);
        int length = htonl(itor->second.length);
        memcpy(mSerializedBuffer+offset,&length,sizeof(int));
        offset += sizeof(int);
        memcpy(mSerializedBuffer+offset,itor->second.value,itor->second.length);
        itor->second.value = mSerializedBuffer+offset;
        offset += itor->second.length;
    }

    return true;
}

bool TlvObject::Parse(const unsigned char *buffer,int buffersize)
{
    if(mSerializedBuffer != NULL) {
        return false;
    }

    unsigned char *cached = new unsigned char[buffersize];
    memcpy(cached,buffer,buffersize);

    int offset = 0, length = 0;
    while(offset < buffersize) {
        int type = ntohl((*(int *)(cached+offset)));
        offset += sizeof(int);
        int length = ntohl((*(int *)(cached+offset)));
        offset += sizeof(int);
        PutValue(type,cached+offset,length);
        offset += length;
    }

    mSerializedBuffer = cached;
    mSerializedBytes  = buffersize;

    return true;
}

unsigned char * TlvObject::GetSerializedBuffer() const
{
    return mSerializedBuffer;
}

int TlvObject::GetSerializedBytes() const
{
    return mSerializedBytes;
}

bool TlvObject::PutValue(int type,const void *value,int length)
{
    if(mSerializedBuffer != NULL || value == NULL) {
        return false;
    }
    Tlv obj;
    obj.type  = type;
    obj.value = value;
    obj.length = length;
    mTlvMap.insert(std::pair<int,Tlv>(type,obj));
    mSerializedBytes += (sizeof(int)*2+length);
    return true;
}

bool TlvObject::PutCharValue(int type,const char &value)
{
    return PutValue(type,&value,sizeof(char));
}

bool TlvObject::PutShortValue(int type,const short &value)
{
    return PutValue(type,&value,sizeof(short));
}

bool TlvObject::PutIntValue(int type,const int &value)
{
    return PutValue(type,&value,sizeof(int));
}

bool TlvObject::PutLongValue(int type,const long &value)
{
    return PutValue(type,&value,sizeof(long));
}

bool TlvObject::PutLongLongValue(int type,const long long &value)
{
    return PutValue(type,&value,sizeof(long long));
}

bool TlvObject::PutFloatValue(int type,const float &value)
{
    return PutValue(type,&value,sizeof(float));
}

bool TlvObject::PutDoubleValue(int type,const double &value)
{
    return PutValue(type,&value,sizeof(float));
}

bool TlvObject::PutStringValue(int type,const char *value)
{
    return PutValue(type,value,strlen(value)+1);
}

bool TlvObject::PutBytesValue(int type,const unsigned char *value,int length)
{
    return PutValue(type,value,length);
}

bool TlvObject::PutObjectValue(int type,const TlvObject& value)
{
    return PutValue(type,value.GetSerializedBuffer(),value.GetSerializedBytes());   
}

bool TlvObject::GetValue(int type,const void **value,int& length) const
{
    std::map<int,Tlv>::const_iterator itor = mTlvMap.find(type);
    if(itor == mTlvMap.end()) {
        return false;
    }
    *value = itor->second.value;
    length = itor->second.length;
    return true;
}

bool TlvObject::GetCharValue(int type,char &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(char *)(obj.value));
    return true;
}

bool TlvObject::GetShortValue(int type,short &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(short *)(obj.value));
    return true;
}

bool TlvObject::GetIntValue(int type,int &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(int *)(obj.value));
    return true;
}

bool TlvObject::GetLongValue(int type,long &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(long *)(obj.value));
    return true;
}

bool TlvObject::GetLongLongValue(int type,long long &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(long long *)(obj.value));
    return true;
}

bool TlvObject::GetFloatValue(int type,float& value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(float *)(obj.value));
    return true;
}

bool TlvObject::GetDoubleValue(int type,double& value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(double *)(obj.value));
    return true;
}

bool TlvObject::GetStringValue(int type,char *value,int &length) const
{
    return GetBytesValue(type,(unsigned char *)value,length);
}

bool TlvObject::GetBytesValue(int type,unsigned char *value,int &length) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length) || length < obj.length) {
        return false;
    }
    memset(value,0,length);
    length = obj.length;
    memcpy(value,obj.value,obj.length);
    return true;
}

bool TlvObject::GetBytesValuePtr(int type,unsigned char **value,int &length) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    *value = (unsigned char *)obj.value;
    length = obj.length;
    return true;
}

bool TlvObject::GetObjectValue(int type,TlvObject& value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    if(!value.Parse((const unsigned char *)obj.value,obj.length)) {
        return false;   
    }    
    return true;
}


} //namespace 
