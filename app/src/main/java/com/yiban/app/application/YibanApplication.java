package com.yiban.app.application;

import android.app.Application;
import android.content.Context;


public class YibanApplication extends Application {
    public static final String TAG = "com.yiban.app";
    private static YibanApplication mInstance = null;


    public static Context getContext() {
        if (mInstance != null)
            return mInstance.getApplicationContext();
        else
            return null;
    }

    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        mInstance = this;
    }

    public static YibanApplication getInstance() {
        return mInstance;
    }


}
