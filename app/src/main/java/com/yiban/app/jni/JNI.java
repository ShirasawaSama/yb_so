package com.yiban.app.jni;

import android.content.Context;

public class JNI {

    private static volatile JNI INSTANCE;

    private final _JNI mJni;

    public static JNI getInstance() {
        if (INSTANCE == null) {
            synchronized (JNI.class) {
                if (INSTANCE == null) {
                    INSTANCE = new JNI();
                }
            }
        }
        return INSTANCE;
    }

    private JNI() {
        mJni = new _JNI();
    }

    public boolean checkPackageName(Context context) {
        return mJni._checkPackageName(context);
    }

    public boolean checkSignature(Context context) {
        return mJni._checkSignature(context);
    }

    public String getEncodePwdPublicKey(Context context) {
        return mJni._getEncodePwdPublicKey(context);
    }

    public String getEncodeConfigPrivateKey(Context context) {
        return mJni._getEncodeConfigPrivateKey(context);
    }
}
