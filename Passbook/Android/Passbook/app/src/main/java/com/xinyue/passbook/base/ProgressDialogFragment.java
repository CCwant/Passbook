package com.xinyue.passbook.base;

import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.DialogFragment;

import com.xinyue.passbook.R;

/**
 * Created by Administrator on 2016/12/16.
 */


public class ProgressDialogFragment  extends DialogFragment
{
    private boolean mIsDissmissOnPause = false;
    private DialogInterface.OnCancelListener mOnCancelListener = null;
    private String mText;

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        //return super.onCreateDialog(savedInstanceState);
        setStyle(STYLE_NO_FRAME,0);
        XSupportProgressDialog dialog = new XSupportProgressDialog(getActivity(), R.style.CustomAlertDialog);
        dialog.setMessage(mText);
        if (mOnCancelListener != null) {
            setCancelable(true);
            dialog.setOnCancelListener(mOnCancelListener);
            return dialog;
        }
        setCancelable(false);
        return dialog;
    }
    @Override
    public void onPause() {
        super.onPause();
        if (this.mIsDissmissOnPause) {
            dismissAllowingStateLoss();
        }
    }

    public ProgressDialogFragment setDissmissOnPause(boolean paramBoolean) {
        mIsDissmissOnPause = paramBoolean;
        return this;
    }
    public ProgressDialogFragment setOnCancelListener(DialogInterface.OnCancelListener paramOnCancelListener) {
        this.mOnCancelListener = paramOnCancelListener;
        return this;
    }
    public ProgressDialogFragment setTitle(String paramString) {
        this.mText = paramString;
        return this;
    }
}