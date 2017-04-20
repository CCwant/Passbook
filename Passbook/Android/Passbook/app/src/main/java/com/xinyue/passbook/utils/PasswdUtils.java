package com.xinyue.passbook.utils;

import android.util.Log;

import com.xinyue.passbook.base.AppInterface;
import com.xinyue.passbook.entity.Note;
import com.xinyue.passwd.Content;
import com.xinyue.passwd.Passwd;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

/**
 * Created by Administrator on 2017/3/27.
 */

public class PasswdUtils {


    /**
     * 验证登录
     * @param app
     * @param password
     * @return
     */
    public static boolean loginPasswd(AppInterface app,String password){
        File file=FileManager.readPasswdFile();
        try {
            InputStream fis = new FileInputStream(file);
            int len = fis.available();
            byte[] data = new byte[len];
            fis.read(data);
            Passwd passwd=new Passwd(data,password);
            passwd.execute();
            List<Content> contents=passwd.getData();
            if(contents==null || contents.size() == 0){
                return false;
            }else{
                app.clearNote();
                for (int i = 0; i < contents.size(); i++) {
                    final Content content = contents.get(i);
                    parseBook(app,content);
                }
                return true;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }
    private static void parseBook(AppInterface app,Content passwdContent){
        final String title=new String(passwdContent.getTypeName());
        final String content=new String(passwdContent.getText());
        Note book=new Note();
        book.setTitle(title);
        book.parseText(content);
        app.addNote(book);
    }

    /**
     * 导出
     * @param app
     */
    public static void export(AppInterface app){
        List<Note> books= app.getNotes();

        Passwd passwd=new Passwd();
        passwd.setPassword(app.getPassword());
        for (int i = 0; i < books.size() ; i++) {
            Note book=books.get(i);
            passwd.add(book.getTitle().getBytes(),book.getTextByJson().toString().getBytes());
        }
        passwd.execute();
        File file= FileManager.createPasswdFile();
        try{
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
