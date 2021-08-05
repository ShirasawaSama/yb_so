package com.yiban;

import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;

import com.yiban.app.jni.JNIHelper;
import com.yiban.jni.R;
import com.yiban.jni.databinding.ActivityMainBinding;

import java.nio.charset.StandardCharsets;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityMainBinding mBinding = DataBindingUtil.setContentView(this, R.layout.activity_main);


        mBinding.tvName.setOnClickListener(v -> {
//            boolean result = JNIHelper.checkPackageName();
//            Toast.makeText(this, "包名验证" + (result ? "" : "不") + "正确", Toast.LENGTH_SHORT).show();

            String publicKey = JNIHelper.getEncodePwdPublicKey();
            Toast.makeText(this, publicKey, Toast.LENGTH_SHORT).show();

        });

        mBinding.tvSignature.setOnClickListener(v -> {
//            boolean result = JNIHelper.checkSignature();
//            Toast.makeText(this, "签名验证" + (result ? "" : "不") + "正确", Toast.LENGTH_SHORT).show();
//            String signature = getSignature();
//            Log.d(TAG, "onCreate: signature = " + signature);

            String  privateKey =  JNIHelper.getEncodeConfigPrivateKey();
            Toast.makeText(this, privateKey, Toast.LENGTH_SHORT).show();

        });


    }

    public String getSignature() {
        try {
            PackageInfo packageInfo = getPackageManager().getPackageInfo(getPackageName(), PackageManager.GET_SIGNATURES);
            Signature[] signs = packageInfo.signatures;
            Signature sign = signs[0];
            return sign.toCharsString();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "";
    }
}