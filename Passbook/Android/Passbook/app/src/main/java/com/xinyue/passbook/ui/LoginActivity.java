package com.xinyue.passbook.ui;


import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.LinearInterpolator;
import android.view.animation.RotateAnimation;
import android.widget.EditText;
import android.widget.ImageView;

import com.xinyue.passbook.R;
import com.xinyue.passbook.base.XSupportActivity;
import com.xinyue.passbook.utils.FileManager;
import com.xinyue.passbook.utils.PasswdUtils;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by Administrator on 2017/3/22.
 */
public class LoginActivity extends XSupportActivity{

    @BindView(R.id.edt_password)
    EditText mEdtPassword;

    @BindView(R.id.img_logo)
    ImageView mImgLogo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        ButterKnife.bind(this);
        setTitle("登录");
        //mEdtPassword=(EditText)findViewById(R.id.edt_password);
        mImgLogo.clearAnimation();
        Animation animation=new RotateAnimation(0f,360f, Animation.RELATIVE_TO_SELF,0.5f,Animation.RELATIVE_TO_SELF,0.5f);
        animation.setInterpolator(new LinearInterpolator());//不停顿
        animation.setDuration(20000);
        animation.setRepeatCount(Animation.INFINITE);
        animation.setRepeatMode(Animation.RESTART);//设置反方向执行
        mImgLogo.startAnimation(animation);
    }
    public void onLogin(View v){
        final String password=mEdtPassword.getText().toString();
        if (!checkLogin(password)) {
            return;
        }
        //读取及加载数据
        //判断密码文件是否存在
        if (FileManager.isPasswdFileExists()) {
            if (PasswdUtils.loginPasswd(getAppInterface(), password)) {
                loginSuccess(password);
            } else {
                showToast("密码错误");
            }
        } else {
            loginSuccess(password);
        }
    }
    private void loginSuccess(String password){
        getAppInterface().setPassword(password);
        MainActivity.jumpTo(this);
        finish();
    }
    private boolean checkLogin(String password){
        if(TextUtils.isEmpty(password)){
            showToast("密码不能为空");
            return false;
        }else if(password.length() < 6){
            showToast("密码长度至少6位");
            return false;
        }else{
            return true;
        }
    }

}
