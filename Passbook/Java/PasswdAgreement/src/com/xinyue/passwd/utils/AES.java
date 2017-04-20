package com.xinyue.passwd.utils;

import java.security.MessageDigest;
import java.security.SecureRandom;
import java.util.Arrays;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;


public class AES {
	
	public static byte[] encode(byte[] data, byte[] key) throws Exception { 
		//SHA-256加密秘钥
		MessageDigest digest = MessageDigest.getInstance("SHA-256");
		digest.update(key);
		byte[] keyDigest = digest.digest();
		//取前16个字节
		byte[] keyBytes = new byte[16];
		System.arraycopy(keyDigest, 0, keyBytes, 0, keyBytes.length);
		
		//创建AES加密实例
		SecretKeySpec skeySpec = new SecretKeySpec(keyBytes, "AES");  
	    Cipher cip = Cipher.getInstance("AES/ECB/NoPadding");//算法/模式/补码方式
	    cip.init(Cipher.ENCRYPT_MODE,skeySpec);  
	    //分块加密
		int black= data.length/16+1;
		byte[] out = new byte[black * 16];
		int b = 0;
		while(b < black){
			//计算偏移
			int offset = b * 16;
			//计算剩余长度
			int len = (data.length-16-offset) > 0 ? 16:(data.length - offset);
			byte[] input = new byte[16];
			System.arraycopy(data, offset, input, 0, len);
			byte[] output=cip.doFinal(input);
			System.arraycopy(output, 0, out,offset, 16);
			b++;
		}
		return out;  
    }  
	public static byte[] decode(byte[] data, byte[] key) throws Exception { 
		MessageDigest digest = MessageDigest.getInstance("SHA-256");
		digest.update(key);
		byte[] keyBytes = new byte[16];
		System.arraycopy(digest.digest(), 0, keyBytes, 0, keyBytes.length);

		// 创建AES加密实例
		SecretKeySpec skeySpec = new SecretKeySpec(keyBytes, "AES");
		Cipher cip = Cipher.getInstance("AES/ECB/NoPadding");// 算法/模式/补码方式
		cip.init(Cipher.DECRYPT_MODE, skeySpec);
		
		 int blockSize = cip.getBlockSize();  
		// 分块加密
		int black = data.length/16 + (data.length % 16 == 0?0:1);

		byte[] out = new byte[black * 16];
		int b = 0;
		while (b < black) {

			// 计算偏移
			int offset = b * 16;
			// 计算剩余长度
			int len = (data.length - 16 - offset) > 0 ? 16: (data.length - offset);
			byte[] input = new byte[16];
			System.arraycopy(data, offset, input, 0, len);
	
			//byte[] output =cip.update(input,0,len);
			byte[] output=cip.doFinal(input);
			System.arraycopy(output, 0, out, offset, len);
			b++;
		}
		return out;

    }  

}
