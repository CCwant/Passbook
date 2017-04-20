package com.xinyue.passwd.utils;

import java.security.MessageDigest;
import java.util.Random;


public class MD5 {

    public static byte[] encode(byte[] src) { 
    	
        try {  
            MessageDigest md5 = MessageDigest.getInstance("MD5");  
            return md5.digest(src);  
        } catch (Exception e) {  
            return null;  
        }  
    } 
}
