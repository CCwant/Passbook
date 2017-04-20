package com.xinyue.passbook.ui.actionbar;

import android.content.Context;
import android.os.Bundle;
import android.view.View;

import com.xinyue.passbook.base.actionbar.ExpandActionBar;
import com.xinyue.passbook.ui.BookActivity;


/**
 * Created by Administrator on 2017/3/22.
 */

public class BookActionBar extends ExpandActionBar {
    public BookActionBar(Context context) {
        super(context);
    }
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setExpandText("保存");
        //setBackgroundResource(R.drawable.bg_action_bar);
        setTitleColor(0xffdddddd);
    }
    @Override
    public void onSubmit(View v) {
        ((BookActivity)mContext).onSubmit(v);
    }
}
