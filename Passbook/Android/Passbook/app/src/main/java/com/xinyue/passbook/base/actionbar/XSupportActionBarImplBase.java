package com.xinyue.passbook.base.actionbar;

import android.content.Context;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;

import com.xinyue.passbook.base.MenuPopup;

/**
 * Created by ccwant on 2017/3/21.
 */
public abstract class XSupportActionBarImplBase extends XSupportActionBar {

    View contentView;
    protected final Context mContext;
    MenuPopup mMenu;

    public XSupportActionBarImplBase(Context context) {
        mContext=context;
    }

    /**
     * 设置ActionBar的布局文件
     * @param resId
     */
    public final void setContentView(int resId){
        final LayoutInflater inflater =LayoutInflater.from(mContext);
        contentView=inflater.inflate(resId,null, false);
        setContentView(contentView);
    }
    public final void setContentView(View view){
        ((AppCompatActivity)mContext).getSupportActionBar().setDisplayOptions(ActionBar.DISPLAY_SHOW_CUSTOM);
        ((AppCompatActivity)mContext).getSupportActionBar().setCustomView(view);
    }
    public final View findViewById(int resId){
        return contentView.findViewById(resId);
    }

    public void setBackgroundResource(int resId){
        contentView.setBackgroundResource(resId);
    }
    /**
     * 设置菜单
     * @param resId
     */
    public void setActionBarMenu(int resId){
        mMenu=new MenuPopup(mContext,resId);
        onCreateMenu(mMenu.getContentView());
    }
    /**
     * 当菜单被创建时调用
     * @param view
     */
    public void onCreateMenu(View view){

    }

    /**
     * 设置菜单项监听，添加后，一旦你点击了菜单项可以在onMenuItemSelected获取到
     * @param resId
     */
    public void setOnMenuItemListener(int resId){
        if(mMenu == null){
            return ;
        }
        View v=mMenu.getContentView();
        v.findViewById(resId).setOnClickListener(new OnMenuItemListener());
    }

    /**
     * 菜单项选择的事件
     * @param v
     */
    public void onMenuItemSelected(View v){

    }
    /**
     * 显示Menu菜单
     * @param v
     */
    public void showActionBarMenu(View v){
        mMenu.show(v);
    }

    /**
     * 菜单项监听方法具体的实现，用于回调onMenuItemSelected方法
     */
    private class OnMenuItemListener implements View.OnClickListener{
        @Override
        public void onClick(View v) {
            onMenuItemSelected(v);
            mMenu.dismiss();
        }
    }
}
