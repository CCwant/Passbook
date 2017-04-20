package com.xinyue.passwd.utils;

public class ByteUtils {

	public static byte int8ToBytes(short num){  
        return (byte)((num >>> 0) & 0xff );  
    }  
    public static short bytesToInt8(byte bt){  
        return (short) (bt & 0xff);  
    }
    public static byte[] int16ToBytes(int num){  
        byte[] result = new byte[2];  
        result[0] = (byte)((num >>> 8) & 0xff );  
        result[1] = (byte)((num >>> 0) & 0xff );  
        return result;  
    }  
    /**
     * int16有符号，变成无符号需要result & 0xffffL
     * @param bytes
     * @return
     */
    public static int bytesToInt16(byte[] bytes){  
    	int result = 0;  
        if(bytes.length == 2){  
            int a = (bytes[0] & 0xff) << 8;//说明二   
            int b = (bytes[1] & 0xff);  
            result = a | b ;  
        }  
        return result;  
    }
    public static byte[] int32ToBytes(long num){  
        byte[] result = new byte[4];  
        result[0] = (byte)((num >>> 24) & 0xff);//说明一  
        result[1] = (byte)((num >>> 16)& 0xff );  
        result[2] = (byte)((num >>> 8) & 0xff );  
        result[3] = (byte)((num >>> 0) & 0xff );  
        return result;  
    }  
    /**
     * int32有符号，变成无符号需要result & 0xffffffffL
     * @param bytes
     * @return
     */
    public static long bytesToInt32(byte[] bytes){  
        int result = 0;  
        if(bytes.length == 4){  
            int a = (bytes[0] & 0xff) << 24;//说明二  
            int b = (bytes[1] & 0xff) << 16;  
            int c = (bytes[2] & 0xff) << 8;  
            int d = (bytes[3] & 0xff);  
            result = a | b | c | d;  
        }
        return result ;  
    }
//  //低位在前，高位在后     
// 	public static int bytes2int2(byte[] bytes) {
// 	    int result = 0;
// 	    for (int i = 0; i < bytes.length; i++) {
// 	    	result += (bytes[i] & 0xFF) << (8 * i);
// 	    }
// 	    return result;
// 	}
// 	//低位在前，高位在后  
//	public static byte[] int2bytes2(int num, int len) {
//		byte[] bytes = new byte[len];
//		for (int i = 0; i < bytes.length; i++) {
//			bytes[i] = (byte) ((num >>> (8 * i)) & 0xff);
//
//		}
//		return bytes;
//	}
//    
	   
	   public static long getUint32(long l){
		   return l & 0x00000000ffffffff;
		}
    
	   
    /** 
     * Byte转Bit 
     */  
    public static String byteToBit(byte b) {  
        return "" +(byte)((b >> 7) & 0x1) +   
        (byte)((b >> 6) & 0x1) +   
        (byte)((b >> 5) & 0x1) +   
        (byte)((b >> 4) & 0x1) +   
        (byte)((b >> 3) & 0x1) +   
        (byte)((b >> 2) & 0x1) +   
        (byte)((b >> 1) & 0x1) +   
        (byte)((b >> 0) & 0x1);  
    }  
      
    /** 
     * Bit转Byte 
     */  
    public static byte BitToByte(String byteStr) {  
        int re, len;  
        if (null == byteStr) {  
            return 0;  
        }  
        len = byteStr.length();  
        if (len != 4 && len != 8) {  
            return 0;  
        }  
        if (len == 8) {// 8 bit处理  
            if (byteStr.charAt(0) == '0') {// 正数  
                re = Integer.parseInt(byteStr, 2);  
            } else {// 负数  
                re = Integer.parseInt(byteStr, 2) - 256;  
            }  
        } else {//4 bit处理  
            re = Integer.parseInt(byteStr, 2);  
        }  
        return (byte) re;  
    } 
  //byte 转16进制字符串
  	public static String byte2hex(byte [] buffer){  
          String h = "";  
          for(int i = 0; i < buffer.length; i++){  
              String temp = Integer.toHexString(buffer[i] & 0xFF);  
              if(temp.length() == 1){  
                  temp = "0" + temp;  
              }  
              h = h + " "+ temp;  
          }  
          return h;  
      }  
  	
  	 /**
  	  * 比较两个byte数组数据是否相同,相同返回 true
  	  * 
  	  * @param data1
  	  * @param data2
  	  * @param len
  	  * @return
  	  */
	public static boolean memcmp(byte[] data1, byte[] data2) {
		if (data1 == null && data2 == null) {
			return true;
		}
		if (data1 == null || data2 == null) {
			return false;
		}
		if (data1 == data2) {
			return true;
		}
		boolean bEquals = true;
		int i;
		for (i = 0; i < data1.length && i < data2.length; i++) {
			if (data1[i] != data2[i]) {
				bEquals = false;
				break;
			}
		}
		return bEquals;
	}

}
