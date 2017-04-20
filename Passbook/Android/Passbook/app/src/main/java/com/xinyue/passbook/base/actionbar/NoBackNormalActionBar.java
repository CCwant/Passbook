package com.xinyue.passbook.base.actionbar;

import android.content.Context;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.xinyue.passbook.R;
import com.xinyue.passbook.base.actionbar.XSupportActionBarImplBase;
import com.xinyue.passbook.utils.ToastUtils;

/**
 * Created by Administrator on 2017/3/21.
 */

public class NoBackNormalActionBar extends XSupportActionBarImplBase {

    private TextView mTxtTitle;

    public NoBackNormalActionBar(Context context) {
        super(context);
    }
    @Override
    public void onCreate(Bundle savedInstanceState) {
        setContentView(R.layout.abs_no_back_normal_action_bar);
        mTxtTitle=(TextView)findViewById(R.id.txt_title);
    }
    @Override
    public void setTitle(CharSequence title) {
        mTxtTitle.setText(title);
    }
    @Override
    public void setTitleColor(int color){
        mTxtTitle.setTextColor(color);
    }
    @Override
    public void setDividerVisibility(int visibility) {
        findViewById(R.id.action_bar_divider).setVisibility(visibility);
    }
}
