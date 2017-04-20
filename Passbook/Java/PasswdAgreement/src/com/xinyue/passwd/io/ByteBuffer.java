package com.xinyue.passwd.io;

public class ByteBuffer {

	int seek=0;
	byte[] buffer;
	public ByteBuffer(int length){
		buffer=new byte[length];
		seek=0;
	}
	public ByteBuffer(byte[] data){
		buffer=data;
		seek=0;
	}
	public synchronized byte[] readAll(){
		return buffer;
	}
	public synchronized byte[] read(int len){
		byte[] data=new byte[len];
		for (int i = 0; i < len; i++) {
			data[i]=buffer[seek];
			seek++;
		}
		return data;
	}
	public synchronized byte[] read(){
		byte[] data=new byte[buffer.length-seek];
		for (int i = 0; i < data.length; i++) {
			data[i]=buffer[seek];
			seek++;
		}
		return data;
	}
	public synchronized void seekTo(int seek){
		this.seek=seek;
	}
	public void rest(){
		seek=0;
	}
	public synchronized void write(byte[] data){
		System.arraycopy(data, 0,buffer,seek,data.length);
		seek+=data.length;
	}
	public synchronized void write(byte data){
		buffer[seek]=data;
		seek++;
	}
}
