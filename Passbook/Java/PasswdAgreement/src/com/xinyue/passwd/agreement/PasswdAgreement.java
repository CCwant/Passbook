package com.xinyue.passwd.agreement;

import java.util.Arrays;
import java.util.List;

import com.xinyue.passwd.Content;
import com.xinyue.passwd.io.ByteBuffer;

public class PasswdAgreement extends Agreement{
	
	private int length=-1;
	private byte[] data=null;
	private List<Content> contents=null;
	
	private HeaderPackage mHeaderPackage;
	private DataPackage mDataPackage;
	
	public PasswdAgreement(){
		mHeaderPackage=new HeaderPackage(48);
		mDataPackage=new DataPackage();
	}
	public PasswdAgreement(byte[] data,String password){
		mHeaderPackage=new HeaderPackage(data);
		mDataPackage=mHeaderPackage.getDataPackage();
		mDataPackage.setPassword(password);
	}
	@Override
	public DataPackage getDataPackage(){
		return mDataPackage;
	}
	@Override
	public void setDataPackage(DataPackage dataPackage){
		mDataPackage=dataPackage;
	}
	@Override
	public void setPassword(String password){
		mDataPackage.setPassword(password);
	}
	@Override
	public void execute(){
		if(!mDataPackage.verify()){
			return ;
		}
		int dataLength=mDataPackage.length();
		if(dataLength==4){
			return;
		}
		length = dataLength+HeaderPackage.HEADER_LEN;
		//
		ByteBuffer buffer=new ByteBuffer(length);
		buffer.write(mHeaderPackage.getValue(mDataPackage));
		buffer.write(mDataPackage.getValue());
		buffer.rest();
		data = buffer.readAll();
		//
		contents=mDataPackage.getData();
	}
	@Override
	public int length(){
		return length;
	}
	@Override
	public byte[] getValue(){
		return data;
	}
	@Override
	public  void add(byte[] typeName,byte[] text)
	{
		mDataPackage.add(typeName, text);
	}
	@Override
	public  void update(int index,byte[] typeName,byte[] text)
	{
		mDataPackage.update(index, typeName, text);
	}
	@Override
	public  void remove(int index)
	{
		mDataPackage.remove(index);
	}
	@Override
	public  int count()
	{
		return mDataPackage.count();
	}
	@Override
	public  List<Content> getData(){
		return contents;
	}
	
	
	
	

}
