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
public class Tester {

    public static final int TEST_TYPE_1 = 0x01;
    public static final int TEST_TYPE_2 = 0x02;
    public static final int TEST_TYPE_3 = 0x03;
    public static final int TEST_TYPE_4 = 0x04;
    public static final int TEST_TYPE_5 = 0x05;
    public static final int TEST_TYPE_6 = 0x06;
    public static final int TEST_TYPE_7 = 0x07;
    public static final int TEST_TYPE_8 = 0x08;
    public static final int TEST_TYPE_9 = 0x09;
    
    public static void main(String args[]) {
        
        TlvObject object = new TlvObject();
        object.putByteValue(TEST_TYPE_1, (byte)1);
        object.putShortValue(TEST_TYPE_2,(short)2);
        object.putIntValue(TEST_TYPE_3,(int)3);
        object.putLongValue(TEST_TYPE_4,(long)4);
        object.putFloatValue(TEST_TYPE_5,(float)5.67);
        object.putDoubleValue(TEST_TYPE_6,(double)8.91);
        object.putStringValue(TEST_TYPE_7, "hello world !");
        object.putBytesValue(TEST_TYPE_8,new byte[] {1,2,3,4,5,6} );
        
        TlvObject box = new TlvObject();
        box.putObjectValue(TEST_TYPE_9, object);
        
        byte[] serialized = box.serialize();
        
        TlvObject parsedBox = TlvObject.parse(serialized, 0, serialized.length);
        TlvObject parsedObject = parsedBox.getObjectValue(TEST_TYPE_9);
        
        System.out.println("TEST_TYPE_1: " + parsedObject.getByteValue(TEST_TYPE_1));
        System.out.println("TEST_TYPE_2: " + parsedObject.getShortValue(TEST_TYPE_2));        
        System.out.println("TEST_TYPE_3: " + parsedObject.getIntValue(TEST_TYPE_3));
        System.out.println("TEST_TYPE_4: " + parsedObject.getLongValue(TEST_TYPE_4));
        System.out.println("TEST_TYPE_5: " + parsedObject.getFloatValue(TEST_TYPE_5));
        System.out.println("TEST_TYPE_6: " + parsedObject.getDoubleValue(TEST_TYPE_6));
        System.out.println("TEST_TYPE_7: " + parsedObject.getStringValue(TEST_TYPE_7));
        byte[] bytes = parsedObject.getBytesValue(TEST_TYPE_8);
        for(byte value : bytes) {
            System.out.println("TEST_TYPE_8: " + value);
        }        
    }
}
