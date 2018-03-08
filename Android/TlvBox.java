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
package com.jhuster.testcode;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.util.SparseArray;

public class TlvBox {
    
    private static final ByteOrder DEFAULT_BYTE_ORDER = ByteOrder.LITTLE_ENDIAN;
    
    private SparseArray<byte[]> mObjects;
    private int mTotalBytes = 0;

    public TlvBox() {
        mObjects = new SparseArray<byte[]>();
    }
    
    public static TlvBox parse(byte[] buffer, int offset, int length) {
        
        TlvBox box = new TlvBox();
        
        int parsed = 0;
        while (parsed < length) {
            int type = ByteBuffer.wrap(buffer, offset + parsed, 4).order(DEFAULT_BYTE_ORDER).getInt();
            parsed += 4;
            int size = ByteBuffer.wrap(buffer, offset+  parsed, 4).order(DEFAULT_BYTE_ORDER).getInt();
            parsed += 4;
            byte[] value = new byte[size];
            System.arraycopy(buffer, offset + parsed, value, 0, size);
            box.putBytesValue(type, value);
            parsed += size;
        }        
        
        return box;
    }
    
    public byte[] serialize() {
        int offset = 0;
        byte[] result = new byte[mTotalBytes];  
        for(int i=0; i<mObjects.size(); i++) {
            int key = mObjects.keyAt(i);
            byte[] bytes = mObjects.get(key);
            byte[] type   = ByteBuffer.allocate(4).order(DEFAULT_BYTE_ORDER).putInt(key).array();
            byte[] length = ByteBuffer.allocate(4).order(DEFAULT_BYTE_ORDER).putInt(bytes.length).array();
            System.arraycopy(type, 0, result, offset, type.length);
            offset += 4;
            System.arraycopy(length, 0, result, offset, length.length);
            offset += 4;
            System.arraycopy(bytes, 0, result, offset, bytes.length);
            offset += bytes.length;
        }
        return result;
    }
    
    public void putByteValue(int type,byte value) {
        byte[] bytes = new byte[1];        
        bytes[0] = value;
        putBytesValue(type, bytes);
    }
        
    public void putShortValue(int type,short value) {
        byte[] bytes = ByteBuffer.allocate(2).order(DEFAULT_BYTE_ORDER).putShort(value).array();
        putBytesValue(type, bytes);
    }
    
    public void putIntValue(int type,int value) {
        byte[] bytes = ByteBuffer.allocate(4).order(DEFAULT_BYTE_ORDER).putInt(value).array();
        putBytesValue(type, bytes);
    }
    
    public void putLongValue(int type,long value) {
        byte[] bytes = ByteBuffer.allocate(8).order(DEFAULT_BYTE_ORDER).putLong(value).array();
        putBytesValue(type, bytes);
    }
    
    public void putFloatValue(int type,float value) {
        byte[] bytes = ByteBuffer.allocate(4).order(DEFAULT_BYTE_ORDER).putFloat(value).array();
        putBytesValue(type, bytes);
    }
    
    public void putDoubleValue(int type,double value) {
        byte[] bytes = ByteBuffer.allocate(8).order(DEFAULT_BYTE_ORDER).putDouble(value).array();
        putBytesValue(type, bytes);
    }
    
    public void putStringValue(int type,String value) {         
        putBytesValue(type,value.getBytes());        
    }

    public void putObjectValue(int type,TlvBox value) {        
        putBytesValue(type,value.serialize());
    }
    
    public void putBytesValue(int type,byte[] value) {
        mObjects.put(type, value);
        mTotalBytes += value.length + 8;
    }
    
    public Byte getByteValue(int type) {
        byte[] bytes = mObjects.get(type);
        if (bytes == null) {
            return null;
        }
        return bytes[0];
    }
        
    public Short getShortValue(int type) {
        byte[] bytes = mObjects.get(type);
        if (bytes == null) {
            return null;
        }
        return ByteBuffer.wrap(bytes).order(DEFAULT_BYTE_ORDER).getShort();
    }
    
    public Integer getIntValue(int type) {
        byte[] bytes = mObjects.get(type);
        if (bytes == null) {
            return null;
        }
        return ByteBuffer.wrap(bytes).order(DEFAULT_BYTE_ORDER).getInt();
    }
    
    public Long getLongValue(int type) {
        byte[] bytes = mObjects.get(type);
        if (bytes == null) {
            return null;
        }
        return ByteBuffer.wrap(bytes).order(DEFAULT_BYTE_ORDER).getLong();
    }
    
    public Float getFloatValue(int type) {
        byte[] bytes = mObjects.get(type);
        if (bytes == null) {
            return null;
        }
        return ByteBuffer.wrap(bytes).order(DEFAULT_BYTE_ORDER).getFloat();
    }
    
    public Double getDoubleValue(int type) {
        byte[] bytes = mObjects.get(type);
        if (bytes == null) {
            return null;
        }
        return ByteBuffer.wrap(bytes).order(DEFAULT_BYTE_ORDER).getDouble();
    }
    
    public TlvBox getObjectValue(int type) {
        byte[] bytes = mObjects.get(type);
        if (bytes == null) {
            return null;
        }
        return TlvBox.parse(bytes, 0, bytes.length);
    }
    
    public String getStringValue(int type) {
        byte[] bytes = mObjects.get(type);
        if (bytes == null) {
            return null;
        }
        return new String(bytes).trim();
    }
    
    public byte[] getBytesValue(int type) {
        byte[] bytes = mObjects.get(type);
        return bytes;
    }
}
