import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

import com.xinyue.passwd.Content;
import com.xinyue.passwd.Passwd;
import com.xinyue.passwd.agreement.DataPackage;
import com.xinyue.passwd.agreement.PasswdAgreement;
import com.xinyue.passwd.utils.ByteUtils;


public class ReadTest {

	public static void main(String[] args) {

		
		try {
		
			InputStream fis = new FileInputStream("e://123.passwd");
			//InputStream fis = new FileInputStream("d://123.passwd");
			int len=fis.available();
			byte[] data=new byte[len];
			fis.read(data);
			
			Passwd passwd=new Passwd(data,"12345678910");
			//passwd.update(0, "502".getBytes(), "11".getBytes());
			//passwd.remove(0);
			passwd.execute();
		
			System.out.println(ByteUtils.byte2hex(passwd.getValue()));
			List<Content> contents=passwd.getData();
			if(contents==null){
				System.out.println("解密失败.");
			}else{
				for (int i = 0; i < contents.size(); i++) {
					Content content = contents.get(i);
					System.out.println(new String(content.getTypeName()) + "  "+ new String(content.getText()));
				}
			}
			
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}

}
