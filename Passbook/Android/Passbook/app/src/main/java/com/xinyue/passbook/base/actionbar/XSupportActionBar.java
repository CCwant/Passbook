package com.xinyue.passbook.base.actionbar;

import android.app.Activity;
import android.os.Bundle;

import com.xinyue.passbook.ui.MainActivity;
import com.xinyue.passbook.ui.BookActivity;
import com.xinyue.passbook.ui.LoginActivity;
import com.xinyue.passbook.ui.actionbar.BookActionBar;
import com.xinyue.passbook.ui.actionbar.LoginActionBar;
import com.xinyue.passbook.ui.actionbar.MainActionBar;

/**
 * Created by Administrator on 2017/3/21.
 */

public abstract class XSupportActionBar {

    public final static int LOGIN_ACTION_BAR=1;

    public abstract void onCreate(Bundle savedInstanceState);

    public abstract void setTitle(CharSequence title);
    public abstract void setTitleColor(int color);
    public abstract void setDividerVisibility(int visibility);

    public static XSupportActionBar create(Activity activity){
        if(activity instanceof LoginActivity){
            return new LoginActionBar(activity);
        }else if(activity instanceof MainActivity){
            return new MainActionBar(activity);
        }else if(activity instanceof BookActivity){
            return new BookActionBar(activity);
        }



        return null;
    }

}
