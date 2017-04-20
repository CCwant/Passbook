package com.xinyue.passbook.ui.actionbar;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.xinyue.passbook.R;
import com.xinyue.passbook.base.actionbar.ExpandActionBar;
import com.xinyue.passbook.base.actionbar.XSupportActionBarImplBase;
import com.xinyue.passbook.ui.BookActivity;
import com.xinyue.passbook.utils.ToastUtils;

/**
 * Created by Administrator on 2017/3/22.
 */

public class MainActionBar extends ExpandActionBar {

    public MainActionBar(Context context) {
        super(context);
    }
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.main_action_bar);
        //setActionBarMenu(R.layout.actionbar_menu);
        setBackVisibility(View.GONE);
        //setBackgroundResource(R.drawable.bg_action_bar);
        setTitleColor(0xffdddddd);
    }

    @Override
    public void onSubmit(View v) {
        BookActivity.jumpTo(mContext);
    }

    @Override
    public void setTitle(CharSequence title) {
        TextView textView=(TextView)findViewById(R.id.txt2);
        textView.setText(title);
    }

    @Override
    public void setDividerVisibility(int visibility) {
        findViewById(R.id.action_bar_divider).setVisibility(visibility);
    }
//    @Override
//    public void onCreateMenu(View view) {
//        super.onCreateMenu(view);
//        setOnMenuItemListener(R.id.menu1);
//        setOnMenuItemListener(R.id.menu2);
//        setOnMenuItemListener(R.id.menu3);
//    }
//    @Override
//    public void onMenuItemSelected(View v) {
//        super.onMenuItemSelected(v);
//        switch (v.getId()){
//            case R.id.menu1:
//                ToastUtils.ShowShort(mContext,"我是菜单一");
//                break;
//            case R.id.menu2:
//                ToastUtils.ShowShort(mContext,"我是菜单二");
//                break;
//            case R.id.menu3:
//                ToastUtils.ShowShort(mContext,"我是菜单三");
//                break;
//            default:
//                break;
//        }
//    }

}
