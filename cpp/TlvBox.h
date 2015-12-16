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

#ifndef _TLV_BOX_H_
#define _TLV_BOX_H_

#include <map>

namespace TLV
{

class TlvBox
{
public:
    TlvBox();
    virtual ~TlvBox();

private:
    TlvBox(const TlvBox& c);
    TlvBox &operator=(const TlvBox &c);

public:
    //put one TLV object
    bool PutCharValue(int type,const char &value);
    bool PutShortValue(int type,const short &value);
    bool PutIntValue(int type,const int &value);
    bool PutLongValue(int type,const long &value);
    bool PutLongLongValue(int type,const long long &value);
    bool PutFloatValue(int type,const float &value);
    bool PutDoubleValue(int type,const double &value);
    bool PutStringValue(int type,const char *value);
    bool PutBytesValue(int type,const unsigned char *value,int length);
    bool PutObjectValue(int type,const TlvBox& value);
    bool PutValue(int type,const void *value,int length);  

    //do encode
    bool Serialize(); 

    //access encoded buffer and length
    unsigned char * GetSerializedBuffer() const;
    int GetSerializedBytes() const;

public:    
    //do decode
    bool Parse(const unsigned char *buffer,int buffersize); 

    //get one TLV object
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
    bool GetObjectValue(int type,TlvBox& value) const;
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
