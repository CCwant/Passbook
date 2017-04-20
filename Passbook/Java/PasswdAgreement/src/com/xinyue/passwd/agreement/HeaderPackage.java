package com.xinyue.passwd.agreement;

import java.util.Arrays;
import java.util.zip.Adler32;

import com.xinyue.passwd.data.IData;
import com.xinyue.passwd.io.ByteBuffer;
import com.xinyue.passwd.utils.ByteUtils;
import com.xinyue.passwd.utils.HashUtils;
import com.xinyue.passwd.utils.HashUtils.HashType;

public class HeaderPackage {

	public final static int HEADER_LEN=48;
	//版本号
	byte[] magic = new byte[12];
	//校验和 计算文件中checksum字段之后（16字节之后）的数据
	byte[] checksum = new byte[4];
	//文件sha1 签名signature字段之后的数据（36字节之后）
	byte[] signature = new byte[20];
	//整个文件的大小
	byte[] fileSize = new byte[4];
	//header结构本身占用的字节数
	byte[] headerSize = new byte[4];
	//data结构本身占用的字节数
	byte[] dataSize = new byte[4];
	
	DataPackage mDataPackage;
	
	public HeaderPackage(int version){
		setVersion(version);
	}
	public HeaderPackage(byte[] data) {
		ByteBuffer buffer=new ByteBuffer(data);
		magic=buffer.read(12);
		checksum=buffer.read(4);
		signature=buffer.read(20);
		fileSize=buffer.read(4);
		headerSize=buffer.read(4);
		dataSize=buffer.read(4);
		long dataLength=ByteUtils.bytesToInt32(dataSize);
		mDataPackage=new DataPackage(buffer.read((int)dataLength));
	}
	public DataPackage getDataPackage(){
		return mDataPackage;
	}
	public void setVersion(int version){
		if(version > 999){
			return;
		}
		byte[] sign="passwd".getBytes();
		byte[] ver=String.format("%03d", version).getBytes();
		System.arraycopy(sign, 0,magic,0,sign.length);
		System.arraycopy(new byte[]{0x0A}, 0,magic,6,1);
		System.arraycopy(ver, 0,magic,7,ver.length);
	}
	public void setChecksum(long sum){
		byte[] checksum = ByteUtils.int32ToBytes(sum);
		System.arraycopy(checksum, 0,this.checksum,0,checksum.length);
	}
	public void setSignature(byte[] signature){
		if(signature.length > 20){
			return ;
		}
		System.arraycopy(signature, 0,this.signature,0,signature.length);
	}
	public void setFileSize(int size){
		byte[] fileSize = ByteUtils.int32ToBytes(size);
		System.arraycopy(fileSize, 0,this.fileSize,0,fileSize.length);
	}
	public void setHeaderSize(int size){
		byte[] headerSize = ByteUtils.int32ToBytes(size);
		System.arraycopy(headerSize, 0,this.headerSize,0,headerSize.length);
	}
	public void setDataSize(int size){
		byte[] dataSize = ByteUtils.int32ToBytes(size);
		System.arraycopy(dataSize, 0,this.dataSize,0,dataSize.length);
	}
	public void calculate(DataPackage dataPackage){
		setDataSize(dataPackage.length());
		setFileSize(dataPackage.length()+HEADER_LEN);
		setHeaderSize(HEADER_LEN);
		calculateSignature(dataPackage);
		calculateChecksum(dataPackage);
		
	}
	private void calculateSignature(DataPackage dataPackage){
		ByteBuffer buffer=new ByteBuffer(12+dataPackage.length());
		buffer.write(fileSize);
		buffer.write(headerSize);
		buffer.write(dataSize);
		buffer.write(dataPackage.getValue());
		buffer.rest();
		byte[] data= buffer.readAll();
		try {
			signature=HashUtils.encode(data, HashType.SHA1);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	private void calculateChecksum(DataPackage dataPackage){
		ByteBuffer buffer=new ByteBuffer(32+dataPackage.length());
		buffer.write(signature);
		buffer.write(fileSize);
		buffer.write(headerSize);
		buffer.write(dataSize);
		buffer.write(dataPackage.getValue());
		buffer.rest();
		byte[] data= buffer.readAll();
		Adler32 adler32=new Adler32();
		adler32.update(data);
		checksum=ByteUtils.int32ToBytes(adler32.getValue());
	}
	public byte[] getValue(DataPackage dataPackage){
		calculate(dataPackage);
		ByteBuffer buffer=new ByteBuffer(HEADER_LEN);
		buffer.write(magic);
		buffer.write(checksum);
		buffer.write(signature);
		buffer.write(fileSize);
		buffer.write(headerSize);
		buffer.write(dataSize);
		buffer.rest();
		return buffer.readAll();
	}
}
