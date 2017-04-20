package com.xinyue.passwd.agreement;

import java.util.List;

import com.xinyue.passwd.Content;

public abstract class Agreement {
	
	
	public abstract void execute();
	public abstract void setPassword(String password);
	public abstract void add(byte[] typeName,byte[] text);
	public abstract void update(int index,byte[] typeName,byte[] text);
	public abstract void remove(int index);
	public abstract int count();
	public abstract int length();
	public abstract List<Content> getData();
	public abstract byte[] getValue();
	public abstract DataPackage getDataPackage();
	public abstract void setDataPackage(DataPackage dataPackage);
	
}
