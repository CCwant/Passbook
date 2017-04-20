package com.xinyue.passbook.base.actionbar;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.xinyue.passbook.R;
import com.xinyue.passbook.base.actionbar.XSupportActionBarImplBase;
import com.xinyue.passbook.utils.ToastUtils;

import static android.R.attr.button;

/**
 * Created by Administrator on 2017/3/22.
 */

public abstract class ExpandActionBar  extends XSupportActionBarImplBase {

    
    private BaseClick mBaseClick;
    private Button mBtnExpand;
    TextView mTxtTitle;
    private ImageView mImgBack;

    public ExpandActionBar(Context context) {
        super(context);
    }
    @Override
    public void onCreate(Bundle savedInstanceState) {
        setContentView(R.layout.abs_expand_action_bar);
        //setActionBarMenu(R.layout.actionbar_menu);
        mBaseClick=new BaseClick();
        mImgBack=(ImageView)findViewById(R.id.img_back);
        mTxtTitle=(TextView)findViewById(R.id.txt2);
        mBtnExpand=(Button)findViewById(R.id.btn_add);


        mImgBack.setOnClickListener(mBaseClick);
        mBtnExpand.setOnClickListener(mBaseClick);
    }
    public void setBackVisibility(int visibility){
        mImgBack.setVisibility(visibility);
    }

    public void setExpandText(CharSequence text){
        mBtnExpand.setText(text);
    }

    public abstract void onSubmit(View v);

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
    private class BaseClick implements View.OnClickListener{

        @Override
        public void onClick(View v) {
            switch (v.getId()){
                case R.id.img_back:
                    ((Activity)mContext).finish();
                    break;
                case R.id.btn_add:
                    onSubmit(v);
                    break;
                default:
                    break;
            }
        }

    }

}
