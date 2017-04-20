package com.xinyue.passbook.base.actionbar;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.xinyue.passbook.R;

/**
 * Created by Administrator on 2017/3/22.
 */

public class NoramlActionBar  extends XSupportActionBarImplBase {

    private TextView mTxtTitle;

    public NoramlActionBar(Context context) {
        super(context);
    }
    @Override
    public void onCreate(Bundle savedInstanceState) {
        setContentView(R.layout.abs_normal_action_bar);
        //setActionBarMenu(R.layout.actionbar_menu);
        mTxtTitle=(TextView)findViewById(R.id.txt2);
        ImageView imgBack=(ImageView)findViewById(R.id.img_back);
        imgBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ((Activity)mContext).finish();
            }
        });

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
