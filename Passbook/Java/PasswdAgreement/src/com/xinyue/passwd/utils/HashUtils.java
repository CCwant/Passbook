package com.xinyue.passwd.utils;

import java.security.MessageDigest;
import java.util.HashMap;
import java.util.Map;

public class HashUtils {
	public static enum HashType{
		MD5("MD5"),SHA1("SHA1"),SHA256("SHA-256"),SHA384("SHA-384"),SHA512("SHA-512");
		 private String text;
	    
		 HashType(String text) {
	        this.text = text;
	    }
	    
	    public String getType() {
	        return this.text;
	    }
	    
	    // Implementing a fromString method on an enum type
	    private static final Map<String, HashType> stringToEnum = new HashMap<String, HashType>();
	    static {
	        // Initialize map from constant name to enum constant
	        for(HashType blah : values()) {
	            stringToEnum.put(blah.toString(), blah);
	        }
	    }
	    
	    // Returns Blah for string, or null if string is invalid
	    public static HashType fromString(String symbol) {
	        return stringToEnum.get(symbol);
	    }

	    @Override
	    public String toString() {
	        return text;
	    }
	}
	//SHA-256,SHA-384,SHA-512
	
	public static byte[] encode(byte[] data, HashType type) throws Exception {
		MessageDigest md5 = MessageDigest.getInstance(type.getType());
		md5.update(data, 0, data.length);
		return md5.digest();
	}
	
}
