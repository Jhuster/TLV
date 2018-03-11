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
#ifndef _TLV_H_
#define _TLV_H_

#include <string>

namespace tlv
{

class Tlv
{
public:
    Tlv(int type);
    Tlv(int type, bool value);
    Tlv(int type, char value);
    Tlv(int type, short value);
    Tlv(int type, int value);
    Tlv(int type, long value);
    Tlv(int type, long long value);
    Tlv(int type, float value);
    Tlv(int type, double value);
    Tlv(int type, char* value);
    Tlv(int type, std::string value);
    Tlv(int type, unsigned char *value, int length);    
    Tlv(int type, const Tlv& value);
    ~Tlv();

public:
    int GetType() const;
    int GetLength() const;
    unsigned char *GetValue() const;

private:
    Tlv(const Tlv& c);
    Tlv &operator=(const Tlv &c);
    void Initialize(const void *value, int length);

private:
    int mType;
    int mLength;
    unsigned char *mValue;
};

}

#endif //_TLV_H_
