tlv
----------

An easy-to-use TLV API in C 

Building
----------

    gcc -o test test.c tlv.c keylist.c
    ./test

Usage
----------

 **1. Create & Destroy Tlv object**

    tlv_t *tlv_create();    
    int tlv_destroy(tlv_t *tlv);

 **2. Public functions for encode**

    //Put one TLV box
    int tlv_put_char(tlv_t *tlv,int type,char *value);
    int tlv_put_short(tlv_t *tlv,int type,short *value);
    int tlv_put_int(tlv_t *tlv,int type,int *value);
    int tlv_put_long(tlv_t *tlv,int type,long *value);
    int tlv_put_longlong(tlv_t *tlv,int type,long long *value);
    int tlv_put_float(tlv_t *tlv,int type,float *value);
    int tlv_put_double(tlv_t *tlv,int type,double *value);
    int tlv_put_string(tlv_t *tlv,int type,char *value);
    int tlv_put_bytes(tlv_t *tlv,int type,unsigned char *value,int length);
    int tlv_put_object(tlv_t *tlv,int type,tlv_t *object);     
    
    //do encode
    int tlv_serialize(tlv_t *tlv); 
    
    //access encoded buffer and length
    unsigned char *tlv_get_buffer(tlv_t *tlv);
    int tlv_get_size(tlv_t *tlv);

 **3. Public functions for decode**
 
    //do decode
    tlv_t *tlv_parse(unsigned char *buffer,int buffersize);
    
    //Get one TLV box
    int tlv_get_char(tlv_t *tlv,int type,char *value);
    int tlv_get_short(tlv_t *tlv,int type,short *value);
    int tlv_get_int(tlv_t *tlv,int type,int *value);
    int tlv_get_long(tlv_t *tlv,int type,long *value);
    int tlv_get_longlong(tlv_t *tlv,int type,long long *value);
    int tlv_get_float(tlv_t *tlv,int type,float *value);
    int tlv_get_double(tlv_t *tlv,int type,double *value);
    int tlv_get_string(tlv_t *tlv,int type,char *value,int* length);
    int tlv_get_bytes(tlv_t *tlv,int type,unsigned char *value,int* length);
    int tlv_get_bytes_ptr(tlv_t *tlv,int type,unsigned char **value,int* length);
    int tlv_get_object(tlv_t *tlv,int type,tlv_t **object);

 **4. Sample code**
 
     Please refer to test.c.

Contact
----------
Email：lujun.hust@gmail.com
