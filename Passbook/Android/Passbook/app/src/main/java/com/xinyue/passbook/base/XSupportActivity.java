package com.xinyue.passbook.base;

import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import com.xinyue.passbook.PassbookApplication;
import com.xinyue.passbook.base.actionbar.XSupportActionBar;

/**
 * Created by Administrator on 2017/3/21.
 */

public abstract class XSupportActivity extends AppCompatActivity {

    private XSupportActionBar mActionBar;
    private Toast mToast;
    AppInterface mAppInterface;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        getAppInterface();
        final XSupportActionBar actionBar=getXSupportActionBar();
        actionBar.onCreate(savedInstanceState);
        super.onCreate(savedInstanceState);
    }
    public AppInterface getAppInterface(){
        if(mAppInterface == null){
            mAppInterface = ((PassbookApplication)getApplication()).getAppInterface();
        }
        return mAppInterface;
    }
    public XSupportActionBar getXSupportActionBar(){
        if(mActionBar == null){
            mActionBar= XSupportActionBar.create(this);
        }
        return mActionBar;
    }

    @Override
    protected void onTitleChanged(CharSequence title, int color) {
        super.onTitleChanged(title, color);
        getXSupportActionBar().setTitle(title);
    }

    /**
     * 显示Dialog
     * @param fragment 必须是DialogFragment
     * @param tag 设置一个标志，方便管理
     */
    public void showDialog(DialogFragment fragment, String tag) {
        try {
            fragment.show(getSupportFragmentManager(), tag);
        } catch (IllegalStateException e) {
            e.printStackTrace();
        }
    }

    /**
     * 关闭Dialog
     * @param tag 根据设定好的DialogFragment标志，来关闭Dialog
     */
    public void dismissDialog(String tag) {
        DialogFragment dialog = (DialogFragment) getSupportFragmentManager().findFragmentByTag(tag);
        if (dialog != null) {
            try {
                dialog.dismiss();
            } catch (IllegalStateException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 显示ProgressDialog,无提示信息
     */
    public void showProgressDialog()
    {
        showProgressDialog(null);
    }
    /**
     * 显示ProgressDialog，并设置提示信息
     */
    public void showProgressDialog(String title)
    {
        ProgressDialogFragment progressDialogFragment = new ProgressDialogFragment();
        progressDialogFragment.setTitle(title);
        showDialog(progressDialogFragment, "progress_dialog");
    }
    /**
     * 关闭ProgressDialog
     */
    public void dismissProgressDialog()
    {
        dismissDialog("progress_dialog");
    }

    public void showToast(int resId)
    {
        showToast(getString(resId), 0);
    }
    public void showToast(int resId, int duration)
    {
        showToast(getString(resId), duration);
    }
    public void showToast(String text)
    {
        showToast(text, 0);
    }
    protected void showToast(String text, int duration)
    {
        if (this.mToast != null) {
            this.mToast.cancel();
        }
        this.mToast = Toast.makeText(getApplicationContext(), text, duration);
        runOnUiThread(new ToastRunnable());
    }
    protected void showToast(String text, int duration, Integer gravity)
    {
        if (this.mToast != null) {
            this.mToast.cancel();
        }
        this.mToast = Toast.makeText(getApplicationContext(), text, duration);
        if (gravity != null) {
            this.mToast.setGravity(gravity.intValue(), 0, 0);
        }
        runOnUiThread(new ToastRunnable());
    }
    final class ToastRunnable implements Runnable
    {
        public final void run()
        {
            mToast.show();
        }
    }
}
