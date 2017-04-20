package com.xinyue.passwd.utils;
import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;

public class DES {

	
	public static byte[] encode(byte[] data, byte[] key) throws Exception {  
        DESKeySpec desKS = new DESKeySpec(key);  
        SecretKeyFactory skf = SecretKeyFactory.getInstance("DES");  
        SecretKey sk = skf.generateSecret(desKS);  
        Cipher cip = Cipher.getInstance("DES");  
        cip.init(Cipher.ENCRYPT_MODE, sk);  
        return cip.doFinal(data);  
    }  
	public static byte[] decode(byte[] data, byte[] key) throws Exception {  
        DESKeySpec desKS = new DESKeySpec(key);  
        SecretKeyFactory skf = SecretKeyFactory.getInstance("DES");  
        SecretKey sk = skf.generateSecret(desKS);  
        Cipher cip = Cipher.getInstance("DES");  
        cip.init(Cipher.DECRYPT_MODE, sk);  
        return cip.doFinal(data);  
    }  
    
}
