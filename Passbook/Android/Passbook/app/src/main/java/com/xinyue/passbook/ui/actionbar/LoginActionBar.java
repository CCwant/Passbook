package com.xinyue.passbook.ui.actionbar;

import android.content.Context;
import android.os.Bundle;

import com.xinyue.passbook.R;
import com.xinyue.passbook.base.actionbar.NoBackNormalActionBar;

/**
 * Created by Administrator on 2017/3/24.
 */

public class LoginActionBar extends NoBackNormalActionBar {
    public LoginActionBar(Context context) {
        super(context);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setBackgroundResource(R.drawable.bg_action_bar);
        setTitleColor(0xffdddddd);
    }
}
