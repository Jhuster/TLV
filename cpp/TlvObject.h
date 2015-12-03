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

#ifndef _TLVOBJECT_H_
#define _TLVOBJECT_H_

#include <map>

namespace TLV
{

class TlvObject
{
public:
    TlvObject();
    virtual ~TlvObject();

private:
    TlvObject(const TlvObject& c);
    TlvObject &operator=(const TlvObject &c);

public:
    bool Serialize();
    bool Parse(const unsigned char *buffer,int buffersize);

public:
    unsigned char * GetSerializedBuffer() const;
    int GetSerializedBytes() const;

public:
    bool PutCharValue(int type,const char &value);
    bool PutShortValue(int type,const short &value);
    bool PutIntValue(int type,const int &value);
    bool PutLongValue(int type,const long &value);
    bool PutLongLongValue(int type,const long long &value);
    bool PutFloatValue(int type,const float &value);
    bool PutDoubleValue(int type,const double &value);
    bool PutStringValue(int type,const char *value);
    bool PutBytesValue(int type,const unsigned char *value,int length);
    bool PutObjectValue(int type,const TlvObject& value);
    bool PutValue(int type,const void *value,int length);    

public:    
    bool GetCharValue(int type,char &value) const;
    bool GetShortValue(int type,short &value) const;
    bool GetIntValue(int type,int &value) const;
    bool GetLongValue(int type,long &value) const;
    bool GetLongLongValue(int type,long long &value) const;
    bool GetFloatValue(int type,float &value) const;
    bool GetDoubleValue(int type,double &value) const;
    bool GetStringValue(int type,char *value,int &length) const;
    bool GetBytesValue(int type,unsigned char *value,int &length) const;
    bool GetBytesValuePtr(int type,unsigned char **value,int &length) const;
    bool GetObjectValue(int type,TlvObject& value) const;
    bool GetValue(int type,const void **value,int& length) const;

private:
    typedef struct tagTlv {
        int type;
        int length;
        const void *value;
    } Tlv;

private:
    std::map<int,Tlv> mTlvMap;
    unsigned char *mSerializedBuffer;
    int mSerializedBytes;
};

} //namespace 

#endif //_TLVOBJECT_H_
