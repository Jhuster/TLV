TlvBox
----------

An easy-to-use TLV API in C plus plus. 

It can help you construct & parse one or several TLV objects.

Building
----------

- Linux/Mac

~~~
g++ -o test test.cpp tlv_box.cpp tlv.cpp
./test
~~~

- Windows

Pls Open `VS20xx Native Tools Command Prompt` to build

~~~
cl test.cpp tlv_box.cpp tlv.cpp
test.exe
~~~

Usage
----------

 **1. Public functions for encode**

    //put one TLV box
    bool PutBoolValue(int type, bool value);
    bool PutCharValue(int type, char value);
    bool PutShortValue(int type, short value);
    bool PutIntValue(int type, int value);
    bool PutLongValue(int type, long value);
    bool PutLongLongValue(int type, long long value);
    bool PutFloatValue(int type, float value);
    bool PutDoubleValue(int type, double value);
    bool PutStringValue(int type, char *value);
    bool PutStringValue(int type, const std::string &value);
    bool PutBytesValue(int type, unsigned char *value, int length);
    bool PutObjectValue(int type, const TlvBox& value);          
    
    //do encode
    bool Serialize(); 
    
    //access encoded buffer and length
    unsigned char * GetSerializedBuffer() const;
    int GetSerializedBytes() const;

 **2. Public functions for decode**

    //do decode
    bool Parse(const unsigned char *buffer,int buffersize); 
    
    //get one TLV box
    bool GetBoolValue(int type, bool &value) const;
    bool GetCharValue(int type, char &value) const;
    bool GetShortValue(int type, short &value) const;
    bool GetIntValue(int type, int &value) const;
    bool GetLongValue(int type, long &value) const;
    bool GetLongLongValue(int type, long long &value) const;
    bool GetFloatValue(int type, float &value) const;
    bool GetDoubleValue(int type, double &value) const;
    bool GetStringValue(int type, char *value,int &length) const;
    bool GetStringValue(int type, std::string &value) const;
    bool GetBytesValue(int type, unsigned char *value, int &length) const;
    bool GetBytesValuePtr(int type, unsigned char **value, int &length) const;
    bool GetObjectValue(int type, TlvBox& value) const;

 **3. Sample code**

     Please refer to Test.cpp.

Contact
----------
Email：lujun.hust@gmail.com
