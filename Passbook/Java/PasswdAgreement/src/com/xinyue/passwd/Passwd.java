package com.xinyue.passwd;

import java.util.List;

import com.xinyue.passwd.agreement.Agreement;
import com.xinyue.passwd.agreement.PasswdAgreement;

public class Passwd {

	private Agreement mAgreement;
	
	public Passwd(){
		mAgreement=new PasswdAgreement();
	}
	public Passwd(byte[] data,String passwd){
		mAgreement=new PasswdAgreement(data,passwd);
	}
	public void setPassword(String password){
		mAgreement.setPassword(password);
	}
	public void execute(){
		mAgreement.execute();
	}
	public void add(byte[] typeName, byte[] text) {
		mAgreement.add(typeName, text);
	}
	public void update(int index, byte[] typeName, byte[] text) {
		mAgreement.update(index, typeName, text);
	}
	public void remove(int index) {
		mAgreement.remove(index);
	}
	public int count() {
		return mAgreement.count();
	}
	public int length() {
		return mAgreement.length();
	}
	public List<Content> getData() {
		return mAgreement.getData();
	}
	public byte[] getValue() {
		return mAgreement.getValue();
	}

	
	
}
