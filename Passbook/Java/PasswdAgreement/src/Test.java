
import java.io.FileInputStream;
import java.io.InputStream;
import java.security.MessageDigest;
import java.util.Arrays;
import java.util.List;

import com.xinyue.passwd.Content;
import com.xinyue.passwd.agreement.DataPackage;
import com.xinyue.passwd.agreement.HeaderPackage;
import com.xinyue.passwd.agreement.PasswdAgreement;
import com.xinyue.passwd.data.MapListData;
import com.xinyue.passwd.io.ByteBuffer;
import com.xinyue.passwd.utils.AES;
import com.xinyue.passwd.utils.Base64;
import com.xinyue.passwd.utils.ByteUtils;
import com.xinyue.passwd.utils.DES;
import com.xinyue.passwd.utils.HashUtils;
import com.xinyue.passwd.utils.MD5;
import com.xinyue.passwd.utils.StringUtils;
import com.xinyue.passwd.utils.HashUtils.HashType;




public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
				byte[] key="1234567890".getBytes();
				byte[] data="123".getBytes();
				byte[] data1 = null;
				try {
					data1 = AES.encode(data, key);
				} catch (Exception e) {
					e.printStackTrace();
				}
				System.out.println("字符："+Arrays.toString(data));
				System.out.println("加密："+Arrays.toString(data1));
				System.out.println("加密KEY："+Arrays.toString(key));
				// -3 76 42 101 100 34 -92 -12 -111 94 -97 -50 14 36 103 -53 
				//fffffffd 4c 2a 65 64 22 ffffffa4 fffffff4 ffffff91 5e ffffff9f ffffffce e 24 67 ffffffcb
				//byte[] data1 = {-3,76,42,101,100,34,-92,-12,-111,94,-97,-50,14,36,103,-53};
				//
				byte[] data2 = null;
				try {
					data2 = AES.decode(data1, key);
				} catch (Exception e) {
					e.printStackTrace();
				}
				
				System.out.println(Arrays.toString(data2));
				System.out.println(new String(data2));
				
		
		//System.out.println(ByteUtils.byte2hex(ByteUtils.int32ToBytes(1144)));
//		MapListData map=new MapListData();
//		
//		map.add("ppp".getBytes(), "123".getBytes());
//		map.add("5abcd".getBytes(), "5678".getBytes());
//		
//		System.out.println(Arrays.toString(map.getValue()));
		
		//map.text();		
//		byte[] text="54165168961256262623".getBytes();
//		byte[] key1="12345678910".getBytes();
//		byte[] key2="12345678910".getBytes();
//		
//		try {
//			System.out.println(Arrays.toString(text));
//			//加密
//			//byte[] data = Base64.encode(text,Base64.DEFAULT);
//			
//			byte[] data1= AES.encode(text, key1);
//			System.out.println(text[0] & 0xff);
//			System.out.println(Arrays.toString(data1));
//
//			//解密
//			//byte[] data2= AES.decode(data1, key2);
//			//byte[] data3 = Base64.decode(data2,Base64.DEFAULT);
////			
////			System.out.println(Arrays.toString(data1));
////			System.out.println(Arrays.toString(data2));
////			System.out.println(new String(data2));
//		} catch (Exception e) {
//			e.printStackTrace();
//		}
		
		
		
		//System.out.println(StringUtils.isUTF8("nihao".getBytes()));
		
	}
	

}
