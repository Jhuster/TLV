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
#include <iostream>
#include <string>
#include "tlv_box.h"

using namespace tlv;

#define TEST_TYPE_0 0x00
#define TEST_TYPE_1 0x01
#define TEST_TYPE_2 0x02
#define TEST_TYPE_3 0x03
#define TEST_TYPE_4 0x04
#define TEST_TYPE_5 0x05
#define TEST_TYPE_6 0x06
#define TEST_TYPE_7 0x07
#define TEST_TYPE_8 0x08
#define TEST_TYPE_9 0x09
#define TEST_TYPE_a 0x0a
#define TEST_TYPE_b 0x0b
#define TEST_TYPE_c 0x0c


int main(int argc, char const *argv[])
{
    TlvBox box;
    box.PutNoValue(TEST_TYPE_b);
    box.PutBoolValue(TEST_TYPE_0, true);
    box.PutCharValue(TEST_TYPE_1, 'x');
    box.PutShortValue(TEST_TYPE_2, (short)2);
    box.PutIntValue(TEST_TYPE_3, (int)3);
    box.PutLongValue(TEST_TYPE_4, (long)4);
    box.PutLongLongValue(TEST_TYPE_c, (long long)4);
    box.PutFloatValue(TEST_TYPE_5, (float)5.67);
    box.PutDoubleValue(TEST_TYPE_6, (double)8.91);
    box.PutStringValue(TEST_TYPE_7, (char *)"hello world !");
    std::string name = "name";
    box.PutStringValue(TEST_TYPE_8, name);
    unsigned char array[6] = {1, 2, 3, 4, 5, 6};
    box.PutBytesValue(TEST_TYPE_9, array, 6);    

    if (!box.Serialize()) {
        std::cout << "box Serialize Failed !\n";
        return -1;
    }

    std::cout << "box Serialize Success, " << box.GetSerializedBytes() << " bytes \n";

    TlvBox boxes;
    boxes.PutObjectValue(TEST_TYPE_a, box);
    
    if (!boxes.Serialize()) {
        std::cout << "boxes Serialize Failed !\n"; 
        return -1;
    }

    std::cout << "boxes Serialize Success, " << boxes.GetSerializedBytes() << " bytes \n";
    
    TlvBox parsedBoxes;
    if (!parsedBoxes.Parse(boxes.GetSerializedBuffer(), boxes.GetSerializedBytes())) {
        std::cout << "boxes Parse Failed !\n";
        return -1;
    }

    std::cout << "boxes Parse Success, " << parsedBoxes.GetSerializedBytes() << " bytes \n";

    TlvBox parsedBox;
    if (!parsedBoxes.GetObjectValue(TEST_TYPE_a, parsedBox)) {
        std::cout << "GetObjectValue Failed !\n";
        return -1;
    }

    std::cout << "box Parse Success, " << parsedBox.GetSerializedBytes() << " bytes \n";

    std::vector<int> tlvList;
    int numTlvs = parsedBox.GetTLVList(tlvList);
    std::cout <<  "box contains " << numTlvs << " TLVs: \n";
    for (int i=0;i<numTlvs; i++)
        std::cout << "Tlv " << std::hex << tlvList[i] << "\n";

    {
        if (!parsedBox.GetNoValue(TEST_TYPE_b)) {
            std::cout << "GetNoValue Failed !\n";            
            return -1;
        }
        std::cout << "GetNoValue Success " << std::endl;
    }
    
    {
        bool value;
        if (!parsedBox.GetBoolValue(TEST_TYPE_0, value)) {
            std::cout << "GetBoolValue Failed !\n";            
            return -1;
        }
        std::cout << "GetBoolValue Success " << value << std::endl;
    }

    {
        char value;
        if (!parsedBox.GetCharValue(TEST_TYPE_1, value)) {
            std::cout << "GetCharValue Failed !\n";            
            return -1;
        }
        std::cout << "GetCharValue Success " << value << std::endl;
    }

    {
        short value;
        if (!parsedBox.GetShortValue(TEST_TYPE_2, value)) {
            std::cout << "GetShortValue Failed !\n";            
            return -1;
        }
        std::cout << "GetShortValue Success " << value << std::endl;
    }

    {
        int value;
        if (!parsedBox.GetIntValue(TEST_TYPE_3, value)) {
            std::cout << "GetIntValue Failed !\n";            
            return -1;
        }
        std::cout << "GetIntValue Success " << value << std::endl;
    }

    {
        long value;
        if (!parsedBox.GetLongValue(TEST_TYPE_4, value)) {
            std::cout << "GetLongValue Failed !\n";            
            return -1;
        }
        std::cout << "GetLongValue Success " << value << std::endl;
    }

    {
        long long value;
        if (!parsedBox.GetLongLongValue(TEST_TYPE_c, value)) {
            std::cout << "GetLongLongValue Failed !\n";            
            return -1;
        }
        std::cout << "GetLongLongValue Success " << value << std::endl;
    }
    
    {
        float value;
        if (!parsedBox.GetFloatValue(TEST_TYPE_5, value)) {
            std::cout << "GetFloatValue Failed !\n";            
            return -1;
        }
        std::cout << "GetFloatValue Success " << value << std::endl;
    }

    {
        double value;
        if (!parsedBox.GetDoubleValue(TEST_TYPE_6, value)) {
            std::cout << "GetDoubleValue Failed !\n";            
            return -1;
        }
        std::cout << "GetDoubleValue Success " << value << std::endl;
    }

    {
        char value[128]; 
        int length = 128;
        if (!parsedBox.GetStringValue(TEST_TYPE_7, value, length)) {
            std::cout << "GetStringValue Failed !\n";            
            return -1;
        }
        std::cout << "GetStringValue Success " << value << std::endl;
    }

    {
        std::string value; 
        if (!parsedBox.GetStringValue(TEST_TYPE_8, value)) {
            std::cout << "GetStringValue Failed !\n";            
            return -1;
        }
        std::cout << "GetStringValue Success " << value << std::endl;
    }

    {
        unsigned char value[128]; 
        int length = 128;
        if (!parsedBox.GetBytesValue(TEST_TYPE_9, value, length)) {
            std::cout << "GetBytesValue Failed !\n";            
            return -1;
        }

        std::cout << "GetBytesValue Success ";
        for (int i=0; i<length; i++) {
            std::cout << (int)value[i] << "--";
        }        
        std::cout << std::endl;
    }

    return 0;
}
