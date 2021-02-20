package com.yiban.app.jni;

import com.yiban.app.application.YibanApplication;

public class JNIHelper {


    public static boolean checkPackageName() {
        return JNI.getInstance().checkPackageName(YibanApplication.getContext());
    }

    public static boolean checkSignature() {
        return JNI.getInstance().checkSignature(YibanApplication.getContext());
    }

    public static String getEncodePwdPublicKey() {
        return JNI.getInstance().getEncodePwdPublicKey(YibanApplication.getContext());
    }

    public static String getEncodeConfigPrivateKey() {
        return JNI.getInstance().getEncodeConfigPrivateKey(YibanApplication.getContext());
    }

}
