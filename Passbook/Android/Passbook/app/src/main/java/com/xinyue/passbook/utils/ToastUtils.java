package com.xinyue.passbook.utils;

/**
 * Created by Administrator on 2016/12/8.
 */


import android.content.Context;
import android.os.Handler;
import android.widget.Toast;

public class ToastUtils
{
    private static Handler mHandler = new Handler();
    private static Toast mToast;
    private static Runnable r = new Runnable()
    {
        public void run()
        {
            mToast.cancel();
            mToast=null;
        }
    };
    public static void ShowLong(Context context, String text)
    {
        Toast.makeText(context, text,Toast.LENGTH_LONG).show();
    }

    public static void ShowShort(Context context, int resId)
    {
        mHandler.removeCallbacks(r);
        if (mToast != null) {
            mToast.setText(resId);
            mToast.show();
        }else{
            mToast = Toast.makeText(context, resId,Toast.LENGTH_SHORT);
            mToast.show();
            mHandler.postDelayed(r, 2000L);
        }
    }

    public static void ShowShort(Context context, String text)
    {
        mHandler.removeCallbacks(r);
        if (mToast != null) {
            mToast.setText(text);
            mToast.show();
        }else{
            mToast = Toast.makeText(context, text,Toast.LENGTH_SHORT);
            mToast.show();
            mHandler.postDelayed(r, 2000L);
        }
    }

    public static void ShowShortCenter(Context context, String text)
    {
        if (mToast != null) {
            mToast.setText(text);
            mHandler.removeCallbacks(r);
        }else{
            mHandler.postDelayed(r, 2000L);
            mToast = Toast.makeText(context, text,Toast.LENGTH_SHORT);
            mToast.setGravity(17, 0, 0);
            mToast.show();
        }
    }
    public static void ShowTime(Context context, String text, int duration)
    {
        Toast.makeText(context, text, duration).show();
    }
}
