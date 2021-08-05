package com.yiban.app.jni;

import android.content.Context;

import androidx.annotation.Keep;

@Keep
public class _JNI {

    static {
        System.loadLibrary("yiban");
    }

    public native boolean _checkPackageName(Context context);

    public native boolean _checkSignature(Context context);

    public native String _getEncodePwdPublicKey(Context context);

    public native String _getEncodeConfigPrivateKey(Context context);

    public native void  _startAntiDebug(Context context);

    public native String _getPwdRSAPublicKey(Context context);

    public native String _getPwdRSAPrivateKey(Context context);

}
