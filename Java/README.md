TlvBox.java
----------

An easy-to-use TLV API in Java version

Building
----------

    $ javac Tester.java TlvBox.java 
    $ java Tester

Usage
----------

 **1. Public functions for encode**

    //put one TLV object
    public void putByteValue(int type, byte value);        
    public void putShortValue(int type, short value);    
    public void putIntValue(int type, int value);    
    public void putLongValue(int type, long value);    
    public void putFloatValue(int type, float value);    
    public void putDoubleValue(int type, double value);    
    public void putStringValue(int type, String value);
    public void putObjectValue(int type, TlvBox value);    
    public void putBytesValue(int type, byte[] value);    

    //do encode
    public byte[] serialize(); 
    
 **2. Public functions for decode**
 
    //do decode
    public static TlvBox parse(byte[] buffer, int offset, int length);
    
    //get one TLV object
    public Byte getByteValue(int type);        
    public Short getShortValue(int type);    
    public Integer getIntValue(int type);    
    public Long getLongValue(int type);    
    public Float getFloatValue(int type);    
    public Double getDoubleValue(int type);        
    public String getStringValue(int type);
    public TlvBox getObjectValue(int type); 
    public byte[] getBytesValue(int type) ;

 **3. Sample code**
 
     Please refer to Tester.java.

Contact
----------
Email：lujun.hust@gmail.com
