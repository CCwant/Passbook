package com.xinyue.passbook.base;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.res.TypedArray;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.xinyue.passbook.R;

/**
 * Created by Administrator on 2017/3/24.
 */

public class XSupportProgressDialog extends Dialog {


    final Context mContext;

    private ProgressBar mProgress;
    private TextView mMessageView;
    private CharSequence mMessage;

    protected XSupportProgressDialog(Context context) {
        super(context);
        mContext=context;
    }

    protected XSupportProgressDialog(Context context, boolean cancelable, DialogInterface.OnCancelListener cancelListener) {
        super(context, cancelable, cancelListener);
        mContext=context;
    }

    protected XSupportProgressDialog(Context context, int themeResId) {
        super(context, themeResId);
        mContext=context;
    }

    public static XSupportProgressDialog show(Context context, CharSequence title,
                                      CharSequence message) {
        return show(context, title, message, false);
    }
    public static XSupportProgressDialog show(Context context, CharSequence title,
                                      CharSequence message, boolean cancelable) {
        return show(context, title, message, cancelable, null);
    }
    public static XSupportProgressDialog show(Context context, CharSequence title,
                                              CharSequence message,
                                              boolean cancelable, OnCancelListener cancelListener) {
        XSupportProgressDialog dialog = new XSupportProgressDialog(context);
        dialog.setTitle(title);
        dialog.setMessage(message);
        dialog.setCancelable(cancelable);
        dialog.setOnCancelListener(cancelListener);
        dialog.show();
        return dialog;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        LayoutInflater inflater = LayoutInflater.from(mContext);
        View view = inflater.inflate(R.layout.abs_loading_dialog, null);
        mProgress = (ProgressBar) view.findViewById(R.id.prb_progress);
        mMessageView = (TextView) view.findViewById(R.id.txt_message);
        setContentView(view);
        super.onCreate(savedInstanceState);
    }
    public void setMessage(CharSequence message) {
        if (mProgress != null) {
            // super.setMessage(message); if HORIZONTAL
            mMessageView.setText(message);
        } else {
            mMessage = message;
        }
    }
}
