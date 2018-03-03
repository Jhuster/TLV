tlv_box
----------

An easy-to-use TLV API in C 

Building
----------

    gcc -o test test.c tlv_box.c key_list.c
    ./test

Usage
----------

 **1. Create & Destroy Tlv box**

    tlv_box_t *tlv_box_create();
    int tlv_box_destroy(tlv_box_t *box);

 **2. Public functions for encode**

    //put one TLV object
    int tlv_box_put_char(tlv_box_t *box, int type, char value);
    int tlv_box_put_short(tlv_box_t *box, int type, short value);
    int tlv_box_put_int(tlv_box_t *box, int type, int value);
    int tlv_box_put_long(tlv_box_t *box, int type, long value);
    int tlv_box_put_longlong(tlv_box_t *box, int type, long long value);
    int tlv_box_put_float(tlv_box_t *box, int type, float value);
    int tlv_box_put_double(tlv_box_t *box, int type, double value);
    int tlv_box_put_string(tlv_box_t *box, int type, char* value);
    int tlv_box_put_bytes(tlv_box_t *box, int type, unsigned char *value, int length);
    int tlv_box_put_object(tlv_box_t *box, int type, tlv_box_t *object);    
    
    //do encode
    int tlv_box_serialize(tlv_box_t *box);
    
    //access encoded buffer and length
    unsigned char *tlv_box_get_buffer(tlv_box_t *box);
    int tlv_box_get_size(tlv_box_t *box);

 **3. Public functions for decode**
 
    //do decode
    tlv_box_t *tlv_box_parse(unsigned char *buffer, int buffersize);
    
    //get one TLV object
    int tlv_box_get_char(tlv_box_t *box, int type, char *value);
    int tlv_box_get_short(tlv_box_t *box, int type, short *value);
    int tlv_box_get_int(tlv_box_t *box, int type, int *value);
    int tlv_box_get_long(tlv_box_t *box, int type, long *value);
    int tlv_box_get_longlong(tlv_box_t *box, int type, long long *value);
    int tlv_box_get_float(tlv_box_t *box, int type, float *value);
    int tlv_box_get_double(tlv_box_t *box, int type, double *value);
    int tlv_box_get_string(tlv_box_t *box, int type, char *value, int* length);
    int tlv_box_get_bytes(tlv_box_t *box, int type, unsigned char *value, int* length);
    int tlv_box_get_bytes_ptr(tlv_box_t *box, int type, unsigned char **value, int* length);
    int tlv_box_get_object(tlv_box_t *box, int type, tlv_box_t **object);

 **4. Sample code**
 
     Please refer to test.c.

Contact
----------
Email：lujun.hust@gmail.com
