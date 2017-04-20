package com.xinyue.passwd.data;

import com.xinyue.passwd.io.ByteBuffer;
import com.xinyue.passwd.utils.ByteUtils;

public class PasswordData implements IData{

	private int size=0; 
	byte[] data;
	public PasswordData() {
		
	}
	public PasswordData(byte[] data) {
		ByteBuffer buffer=new ByteBuffer(data);
		byte[] data1=buffer.read(4);
		this.size=(int) ByteUtils.bytesToInt32(data1);
		this.data=buffer.read(size);
		
	}

	public void setPassword(byte[] password){
		data=password;
		size=data.length;
	}
	public byte[] getPassword(){
		return data;
	}
	
	@Override
	public int length() {
		return size+4;
	}
	@Override
	public byte[] getValue() {
		byte[] data=new byte[length()];
		byte[] data1=ByteUtils.int32ToBytes(size);
		System.arraycopy(data1, 0,data,0,4);
		System.arraycopy(this.data, 0,data,4,size);
		return data;
	}
	
	
	
}
