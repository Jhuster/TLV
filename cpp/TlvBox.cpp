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
#include "TlvBox.h"

namespace tlv
{

TlvBox::TlvBox() : mSerializedBuffer(NULL),mSerializedBytes(0)
{

}

TlvBox::~TlvBox()
{
    if(mSerializedBuffer != NULL) {
        delete[] mSerializedBuffer;
        mSerializedBuffer = NULL;
    }
    mTlvMap.clear();
}

bool TlvBox::Serialize()
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

bool TlvBox::Parse(const unsigned char *buffer,int buffersize)
{
    if(mSerializedBuffer != NULL) {
        return false;
    }

    unsigned char *cached = new unsigned char[buffersize];
    memcpy(cached,buffer,buffersize);

    int offset = 0;
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

unsigned char * TlvBox::GetSerializedBuffer() const
{
    return mSerializedBuffer;
}

int TlvBox::GetSerializedBytes() const
{
    return mSerializedBytes;
}

bool TlvBox::PutValue(int type,const void *value,int length)
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

bool TlvBox::PutCharValue(int type,const char &value)
{
    return PutValue(type,&value,sizeof(char));
}

bool TlvBox::PutShortValue(int type,const short &value)
{
    return PutValue(type,&value,sizeof(short));
}

bool TlvBox::PutIntValue(int type,const int &value)
{
    return PutValue(type,&value,sizeof(int));
}

bool TlvBox::PutLongValue(int type,const long &value)
{
    return PutValue(type,&value,sizeof(long));
}

bool TlvBox::PutLongLongValue(int type,const long long &value)
{
    return PutValue(type,&value,sizeof(long long));
}

bool TlvBox::PutFloatValue(int type,const float &value)
{
    return PutValue(type,&value,sizeof(float));
}

bool TlvBox::PutDoubleValue(int type,const double &value)
{
    return PutValue(type,&value,sizeof(float));
}

bool TlvBox::PutStringValue(int type,const char *value)
{
    return PutValue(type,value,strlen(value)+1);
}

bool TlvBox::PutStringValue(int type,const std::string &value)
{
    int length = value.size()+1;
    return PutValue(type,value.c_str(),length);
}

bool TlvBox::PutBytesValue(int type,const unsigned char *value,int length)
{
    return PutValue(type,value,length);
}

bool TlvBox::PutObjectValue(int type,const TlvBox& value)
{
    return PutValue(type,value.GetSerializedBuffer(),value.GetSerializedBytes());   
}

bool TlvBox::GetValue(int type,const void **value,int& length) const
{
    std::map<int,Tlv>::const_iterator itor = mTlvMap.find(type);
    if(itor == mTlvMap.end()) {
        return false;
    }
    *value = itor->second.value;
    length = itor->second.length;
    return true;
}

bool TlvBox::GetCharValue(int type,char &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(char *)(obj.value));
    return true;
}

bool TlvBox::GetShortValue(int type,short &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(short *)(obj.value));
    return true;
}

bool TlvBox::GetIntValue(int type,int &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(int *)(obj.value));
    return true;
}

bool TlvBox::GetLongValue(int type,long &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(long *)(obj.value));
    return true;
}

bool TlvBox::GetLongLongValue(int type,long long &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(long long *)(obj.value));
    return true;
}

bool TlvBox::GetFloatValue(int type,float& value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(float *)(obj.value));
    return true;
}

bool TlvBox::GetDoubleValue(int type,double& value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (*(double *)(obj.value));
    return true;
}

bool TlvBox::GetStringValue(int type,char *value,int &length) const
{
    return GetBytesValue(type,(unsigned char *)value,length);
}

bool TlvBox::GetStringValue(int type,std::string &value) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    value = (char *)obj.value;
    return true;
}

bool TlvBox::GetBytesValue(int type,unsigned char *value,int &length) const
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

bool TlvBox::GetBytesValuePtr(int type,unsigned char **value,int &length) const
{
    Tlv obj;
    if(!GetValue(type,&obj.value,obj.length)) {
        return false;
    }
    *value = (unsigned char *)obj.value;
    length = obj.length;
    return true;
}

bool TlvBox::GetObjectValue(int type,TlvBox& value) const
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
