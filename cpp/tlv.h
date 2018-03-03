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

#ifndef _TLV_H_
#define _TLV_H_

#include <string>
using std::string;
namespace tlv
{

class Tlv
{
public:
    Tlv(int type,bool value);
    Tlv(int type,char value);
    Tlv(int type,short value);
    Tlv(int type,int value);
    Tlv(int type,long value);
    Tlv(int type,long long value);
    Tlv(int type,float value);
    Tlv(int type,double value);
    Tlv(int type,char* value);
    Tlv(int type,std::string value);
    Tlv(int type,unsigned char *value,int length);    
    Tlv(int type,const Tlv& value);
    bool to_bool(bool&value);
    bool to_char(char&value);
    bool to_short(short&value);
    bool to_int(int&value);
    bool to_long(long&value);
    bool to_longlong(long long&value);
    bool to_float(float&value);
    bool to_double(double&value);
    bool to_string(string&value);
    ~Tlv();

public:
    int GetType() const;
    int GetLength() const;
    unsigned char *GetValue() const;

private:
    bool isdigit();
    Tlv(const Tlv& c);
    Tlv &operator=(const Tlv &c);
    void Initialize(const void *value,int length);

private:
    int mType;
    int mLength;
    unsigned char *mValue;
};

}

#endif //_TLV_H_
