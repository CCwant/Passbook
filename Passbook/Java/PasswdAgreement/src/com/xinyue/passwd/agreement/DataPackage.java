package com.xinyue.passwd.agreement;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import com.xinyue.passwd.Content;
import com.xinyue.passwd.data.IData;
import com.xinyue.passwd.data.MapListData;
import com.xinyue.passwd.data.PasswordData;
import com.xinyue.passwd.io.ByteBuffer;
import com.xinyue.passwd.utils.AES;
import com.xinyue.passwd.utils.ByteUtils;
import com.xinyue.passwd.utils.DES;


public class DataPackage {

	String passwd;
	private MapListData mMapListData;
	private PasswordData mPasswordData;
	public DataPackage(){
		mPasswordData=new PasswordData();
		mMapListData=new MapListData();
	}
	public DataPackage(byte[] data){
		ByteBuffer buffer=new ByteBuffer(data);
		byte[] data1=buffer.read(4);
		int length=(int) ByteUtils.bytesToInt32(data1);
		buffer.rest();
		mPasswordData=new PasswordData(buffer.read(length+4));
		mMapListData=new MapListData(buffer.read());
	}
	public void add(byte[] typeName,byte[] text)
	{
		byte[] key=passwd.getBytes();
		try {
			byte[] dtypeName=AES.encode(typeName,key);
			byte[] dtext=AES.encode(text,key);
			mMapListData.add(dtypeName,dtext);	
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public void update(int index,byte[] typeName,byte[] text){
		byte[] key=passwd.getBytes();
		try {
			byte[] dtypeName=AES.encode(typeName,key);
			byte[] dtext=AES.encode(text,key);
			mMapListData.update(index, dtypeName,dtext);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	public void remove(int index){
		mMapListData.remove(index);
	}
	public byte[] getValue(){
		ByteBuffer buffer=new ByteBuffer(length());
		buffer.write(mPasswordData.getValue());
		buffer.write(mMapListData.getValue());
		buffer.rest();
		return buffer.readAll();
	}
	public List<Content> getData(){
		byte[] key=passwd.getBytes();
		List<Content> datas=mMapListData.getData();
		for (int i = 0; i < datas.size(); i++) {
			Content content=datas.get(i);
			try {
				//解密
				content.setTypeName(AES.decode(content.getTypeName(),key));
				content.setText(AES.decode(content.getText(),key));
				
			} catch (Exception e) {
				return null;
			}
			datas.set(i, content);
		}
		return datas;
	}
	public int length(){
		return mMapListData.length()+mPasswordData.length();
	}
	public int count(){
		return mMapListData.count();
		
	}
	public void setPassword(String passwd){
		this.passwd=passwd;
		byte[] key=passwd.getBytes();
		byte[] data;
		try {
			data = AES.encode(key,key);
			mPasswordData.setPassword(data);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	public boolean verify(){
		byte[] key=passwd.getBytes();
		byte[] passwd=getPassword();
		if(ByteUtils.memcmp(key, passwd)){
			return true;
		}
		return false;
	}
	public byte[] getPassword(){
		byte[] key=passwd.getBytes();
		try {
			byte[] data=mPasswordData.getPassword();
			return AES.decode(data,key);
		} catch (Exception e) {
		}
		return null;
	}
	

	
}
