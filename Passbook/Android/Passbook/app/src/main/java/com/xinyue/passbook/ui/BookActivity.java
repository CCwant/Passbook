package com.xinyue.passbook.ui;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import com.xinyue.passbook.R;
import com.xinyue.passbook.base.XSupportActivity;
import com.xinyue.passbook.entity.Note;
import com.xinyue.passbook.utils.FileManager;
import com.xinyue.passbook.utils.PasswdUtils;
import com.xinyue.passwd.Passwd;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.List;

/**
 * Created by Administrator on 2017/3/22.
 */

public class BookActivity extends XSupportActivity {

    Note mBook;
    private EditText mEdtTitle;
    private EditText mEdtContent;
    private int mPosition;

    public static void jumpTo(Context context){
        Intent intent=new Intent(context,BookActivity.class);
        context.startActivity(intent);
    }
    public static void jumpTo(Context context,int position,Note book){
        Intent intent=new Intent(context,BookActivity.class);
        intent.putExtra("book",book);
        intent.putExtra("position",position);
        context.startActivity(intent);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_book);
        parseIntent();

        mEdtTitle=(EditText)findViewById(R.id.edt_title);
        mEdtContent=(EditText)findViewById(R.id.edt_content);

        if(mBook!=null){
            mEdtTitle.setText(mBook.getTitle());
            mEdtContent.setText(mBook.getText());
        }
    }
    public void parseIntent(){
        Intent intent=getIntent();

        mBook=intent.getParcelableExtra("book");
        mPosition=intent.getIntExtra("position",0);
        if(mBook != null){
            Log.d("123","book title:"+mBook.getTitle());
            Log.d("123","book content:"+mBook.getText());
        }
    }
    public void onSubmit(View v){
        showProgressDialog();
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                final String title=mEdtTitle.getText().toString();
                final String content=mEdtContent.getText().toString();
                if(!checkSubmit(title)){
                    dismissProgressDialog();
                    return ;
                }
                if(mBook == null){
                    mBook=new Note();
                    mBook.setTitle(title);
                    mBook.setText(content);
                    mBook.setModifyTime(System.currentTimeMillis());
                    getAppInterface().addNote(mBook);
                }else{
                    mBook.setTitle(title);
                    mBook.setText(content);
                    mBook.setModifyTime(System.currentTimeMillis());
                    getAppInterface().updateNote(mPosition,mBook);
                }
                Log.d("123","book:"+mBook.toString());
                save();
                dismissProgressDialog();
                finish();
            }
        },500);
    }
    private boolean checkSubmit(String title){
        if(TextUtils.isEmpty(title)){
            showToast("标题不能为空");
            return false;
        }
        return true;
    }
    public void save(){
        PasswdUtils.export(getAppInterface());
    }
}
