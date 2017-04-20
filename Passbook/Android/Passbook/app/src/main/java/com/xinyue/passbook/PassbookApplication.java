package com.xinyue.passbook;

import com.xinyue.passbook.base.AppInterface;
import com.xinyue.passbook.base.XSupportApplication;

/**
 * Created by Administrator on 2017/3/22.
 */

public class PassbookApplication extends XSupportApplication {


    AppInterface mAppInterface;
    @Override
    public void onCreate() {
        super.onCreate();
        mAppInterface=new AppInterface(this);

    }
    public AppInterface getAppInterface(){
        if(mAppInterface == null){
            mAppInterface = new AppInterface(this);
        }
        return mAppInterface;
    }
    @Override
    public void onTerminate() {
        super.onTerminate();
    }
}
