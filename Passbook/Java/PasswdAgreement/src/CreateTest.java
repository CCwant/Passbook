import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;

import com.xinyue.passwd.Passwd;
import com.xinyue.passwd.agreement.DataPackage;
import com.xinyue.passwd.agreement.PasswdAgreement;
import com.xinyue.passwd.utils.AES;
import com.xinyue.passwd.utils.ByteUtils;


public class CreateTest {

	public static void main(String[] args) {

		
		Passwd passwd=new Passwd();
		passwd.setPassword("12345678910");

		passwd.add("阿里".getBytes(), "123456".getBytes());
		passwd.add("阿里1".getBytes(), "123456".getBytes());
		passwd.add("阿里2".getBytes(), "123456".getBytes());
		passwd.add("阿里3".getBytes(), "123456".getBytes());
		passwd.add("阿里4".getBytes(), "123456".getBytes());
		passwd.add("阿里5".getBytes(), "123456".getBytes());
		passwd.add("阿里6".getBytes(), "123456".getBytes());
		passwd.add("阿里7".getBytes(), "123456".getBytes());
		passwd.add("阿里8".getBytes(), "123456".getBytes());
		passwd.add("阿里9".getBytes(), "123456".getBytes());
		passwd.add("阿里10".getBytes(), "123456".getBytes());
		passwd.add("阿里11".getBytes(), "哈哈哈哈".getBytes());
		
	
		passwd.execute();
		
		
		File file=new File("E://123.passwd");
		try {
			file.createNewFile();
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			FileOutputStream fos=new FileOutputStream(file);
			fos.write(passwd.getValue(), 0, passwd.length());
			fos.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
		
	}

}
