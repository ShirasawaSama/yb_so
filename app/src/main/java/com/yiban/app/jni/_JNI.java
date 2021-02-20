package com.yiban.app.jni;

import android.content.Context;

public class _JNI {

    static {
        System.loadLibrary("yiban");
    }

    public native boolean _checkPackageName(Context context);

    public native boolean _checkSignature(Context context);

    public native String _getEncodePwdPublicKey(Context context);

    public native String _getEncodeConfigPrivateKey(Context context);

    public native String _getCachePackageName(Context context);

    public native String _getCacheSignature(Context context);
}
