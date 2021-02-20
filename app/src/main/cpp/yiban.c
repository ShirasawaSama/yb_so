//
// Created by yiban on 2021/2/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <jni.h>
#include <string.h>
#include <android/log.h>


#define MODULE_NAME "YIBAN_SO"
#define LOGV(...) \
  __android_log_print(ANDROID_LOG_VERBOSE, MODULE_NAME, __VA_ARGS__)
#define LOGD(...) \
  __android_log_print(ANDROID_LOG_DEBUG, MODULE_NAME, __VA_ARGS__)
#define LOGI(...) \
  __android_log_print(ANDROID_LOG_INFO, MODULE_NAME, __VA_ARGS__)
#define LOGW(...) \
  __android_log_print(ANDROID_LOG_WARN, MODULE_NAME, __VA_ARGS__)
#define LOGE(...) \
  __android_log_print(ANDROID_LOG_ERROR, MODULE_NAME, __VA_ARGS__)
#define LOGF(...) \
  __android_log_print(ANDROID_LOG_FATAL, MODULE_NAME, __VA_ARGS__)


const static char *jniClassPath = "com/yiban/app/jni/_JNI";
//const char *packageName = "com.yiban.jni";
const static char *packageName = "com.yiban.app";
//正式签名字符串
const static char *signature = "30820267308201d0a00302010202044ff3ea94300d06092a864886f70d01010505003077310b30090603550406130238363111300f060355040813087368616e676861693111300f060355040713087368616e6768616931183016060355040a130f7777772e323163616d7075732e636e31183016060355040b130f7777772e323163616d7075732e636e310e300c06035504031305796962616e3020170d3132303730343037303234345a180f37343838303432373037303234345a3077310b30090603550406130238363111300f060355040813087368616e676861693111300f060355040713087368616e6768616931183016060355040a130f7777772e323163616d7075732e636e31183016060355040b130f7777772e323163616d7075732e636e310e300c06035504031305796962616e30819f300d06092a864886f70d010101050003818d0030818902818100b43c9d42eabea8f7ae58ceabfa85500dd8dd6decc07e735d2afe6f459763b385f69802397d0c9e905373307eb79747e24603d11dac609b27355732e203450343f3aadfb068d6622cf2c8bf27a9d20bdd9ccef4f59454b74d64507956ce81fcb131e9f4f0f96b715a10d3eed840af8b16f69130db781f0aca89cd151dbddaacfd0203010001300d06092a864886f70d010105050003818100b3b7cebbaf8c1126f8082f29d19dedbe4545620ecc32600275a45a26ccf2ae793510d64fa6e5339c8797db6807314ba78175dcea834a8124b7b2325da4d76da378d6a66980ae1d54c2d0c30d3cc95b494251105421a5c38811bfc2f84caed869546ffcc866c65ad29d4b947c4a0b9082ab3b244d9d20123a83c1c44a7370296d";
//测试签名字符串
//const static char *signature = "308201dd30820146020101300d06092a864886f70d010105050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b3009060355040613025553301e170d3139303330383039303234375a170d3439303232383039303234375a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330819f300d06092a864886f70d010101050003818d003081890281810093f63342d4b4c8d4e4a2d80a5609203a22507d49bd4b56cc74d3be9fafa3d2dcbcdcf772d3fbb8794e53c806a0e2d0aadb12da3586b8a006fb4e535fcf13d4ef09dc78ae7003a2e445fb4fca4e76723f78de7ace142a8ee4af686cf3f92247996d5781a8fa1302742b27a7c40ceb86c926fd33773c9afb4f7af329953579d5810203010001300d06092a864886f70d0101050500038181002a0328ba86e9f26e5321f04d9f93820bd3cee6c4f65fe5da63755a810027cce88eb75588298de6baf163a710324c980ea5f0d5a26ee25072f5f8becd982fe1f1b4adda26a8746f5187f09dae42b7172d762222d4baa29689164d32509889fbb22f3357cc46071f429357083adee1a9c352843e22a029f45ff4495eafb1280118";


//加密密码公钥
const static char *publicKey = "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAxbzZk3gEsbSe7A95iCIk59Kvhs1fHKE6zRUfOUyTaKd6Rzgh9TB/jAK2ZN7rHzZExMM9kw6lVwmlV0VabSmOYL9OOHDCiEjOlsfinlZpMZ4VHg8gkFoOeO4GvaBs7+YjG51Am6DKuJWMG9l1pAge96Uhx8xWuDQweIkjWFADcGLpDJJtjTcrh4fy8toE0/0zJMmg8S4RM/ub0q59+VhMzBYAfPmCr6YnEZf0QervDcjItr5pTNlkLK9E09HdKI4ynHy7D9lgLTeVmrITdq++mCbgsF/z5Rgzpa/tCgIQTFD+EPPB4oXlaOg6yFceu0XUQEaU0DvAlJ7Zn+VwPkkqJEoGudklNePHcK+eLRLHcjd9MPgU6NP31dEi/QSCA7lbcU91F3gyoBpSsp5m7bf5//OBadjWJDvl2KML7NMQZUr7YXqUQW9AvoNFrH4edn8d5jY5WAxWsCPQlOqNdybMvKF2jhjIE1fTWOzK+AvvFyNhxer5bWGU4S5LTr7QNXnvbngXCdkQfrcSn/ydQXP0vXfjf3NhpluFXqWe5qUFKXvjY6+PdrE/lvTmX4DdvUIu9NDa2JU9mhwAPPR1yjjp4IhgYOTQL69ZQcvy0Ssa6S25Xi3xx2XXbdx8svYcQfHDBF1daK9vca+YRX/DzXxl1S4uGt+FUWSwuFdZ122ZCZ0CAwEAAQ==";

//config解密私钥
const static char *privateKey = "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";


typedef struct {
    char *package_name_cache;
    char *signature_cache;
} JNICache;


JNICache *mCache;


//获取包名
void initPackageName(JNIEnv *env, jobject thiz, jobject context) {
    
    LOGD("package_name_cache = %s", "执行initPackageName");
    if ((mCache->package_name_cache == NULL) || (mCache->package_name_cache[0] == '\0')) {
        LOGD("mCache.package_name_cache = %s", "执行 为空");
        jclass j_context = (*env)->GetObjectClass(env, context);
        jmethodID gpn_methodID = (*env)->GetMethodID(env, j_context, "getPackageName",
                                                     "()Ljava/lang/String;");
        jstring j_package_name = (*env)->CallObjectMethod(env, context, gpn_methodID);
        
        int pa_length = (*env)->GetStringUTFLength(env, j_package_name);

        const char *temp_pa = (*env)->GetStringUTFChars(env, j_package_name, JNI_FALSE);
        LOGD("计算之后  j_package_name转化成c 字符串 = %s\n", temp_pa);
        memcpy(mCache->package_name_cache, temp_pa, pa_length + 1);
        
        free((char *) temp_pa);
        LOGD("计算之后  mCache.package_name_cache = %s\n", mCache->package_name_cache);


    }
    LOGD("mCache.package_name_cache = %s", "执行 不为空");

}


jboolean checkPackageName(JNIEnv *env, jobject thiz, jobject context) {
    
    LOGD("checkPackageName = %s", "执行 checkPackageName");
    initPackageName(env, thiz, context);
    return (mCache->package_name_cache != NULL) &&
           (strcmp(packageName, mCache->package_name_cache) == 0);
}


//获取签名

void initSignature(JNIEnv *env, jobject thiz, jobject context) {
    
    LOGD("initSignature = %s", "执行 initSignature");
    jboolean same_pn = checkPackageName(env, thiz, context);

    if (same_pn) {
        LOGD("same_pn = %s", "执行 包名相同");

        jclass j_context = (*env)->GetObjectClass(env, context);
        //android.content.pm
        jmethodID j_packageManager = (*env)->GetMethodID(env, j_context, "getPackageManager",
                                                         "()Landroid/content/pm/PackageManager;");
        //获取packagemanager对象
        jobject c_packageManager = (*env)->CallObjectMethod(env, context, j_packageManager);

        //获取PackageManager类
        jclass j_packageManagerClass = (*env)->GetObjectClass(env, c_packageManager);
        //找到getPackageInfo 方法
        //android.content.pm   packageinfo
        jmethodID j_getPackageInfo = (*env)->GetMethodID(env, j_packageManagerClass,
                                                         "getPackageInfo",
                                                         "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");


        //包名
        jstring package_name = (*env)->NewStringUTF(env, packageName);

        //获取packageinfo对象
        jobject j_packageInfo = (*env)->CallObjectMethod(env, c_packageManager, j_getPackageInfo,
                                                         package_name, 0x00000040);

        //获取packageinfo 类class
        jclass j_packageInfoClass = (*env)->GetObjectClass(env, j_packageInfo);


        //获取PackageInfo类里面的字段  signatures  android.content.pm

        jfieldID j_signatureField = (*env)->GetFieldID(env, j_packageInfoClass, "signatures",
                                                       "[Landroid/content/pm/Signature;");

        jobjectArray j_signatureArray = (*env)->GetObjectField(env, j_packageInfo,
                                                               j_signatureField);


        jobject j_signatures = (*env)->GetObjectArrayElement(env, j_signatureArray, 0);



        //找到  Signature 中的toCharsString方法

        jclass j_signatureClass = (*env)->GetObjectClass(env, j_signatures);

        //中的toCharsString方法id

        jmethodID j_toCharsStringMethod = (*env)->GetMethodID(env, j_signatureClass,
                                                              "toCharsString",
                                                              "()Ljava/lang/String;");

        jstring real_signature = (*env)->CallObjectMethod(env, j_signatures, j_toCharsStringMethod);


        int signature_length = (*env)->GetStringUTFLength(env, real_signature);

        const char *temp_signature = (*env)->GetStringUTFChars(env, real_signature, JNI_FALSE);
        memcpy(mCache->signature_cache, temp_signature, signature_length + 1);
        free((char *) temp_signature);
    } else {
        LOGD("same_pn = %s", "执行 包名不相同");
    }

}

jboolean checkSignature(JNIEnv *env, jobject thiz, jobject context) {
    
    LOGD("checkSignature = %s", "执行 checkSignature");
    if ((mCache->signature_cache == NULL) || (mCache->signature_cache[0] == '\0')) {
        LOGD("mCache.signature_cache = %s", "NULL");
        initSignature(env, thiz, context);
    }
    LOGD("mCache.signature_cache = %s", mCache->signature_cache);
    if (mCache->signature_cache != NULL) {
        LOGD(" strcmp(signature, mCache.signature_cache) = %d",
             strcmp(signature, mCache->signature_cache));
    } else {
        LOGD(" strcmp(signature, mCache.signature_cache) = %s",
             mCache->signature_cache);
    }

    return (mCache->signature_cache != NULL) && (strcmp(signature, mCache->signature_cache) == 0);
}

jstring getEncodePwdPublicKey(JNIEnv *env, jobject thiz, jobject context) {
    
    LOGD("getEncodePwdPublicKey = %s", "执行getEncodePwdPublicKey");
    jboolean isSuccess = checkSignature(env, thiz, context);

    return (*env)->NewStringUTF(env, isSuccess ? publicKey : "");
}

jstring getEncodeConfigPrivateKey(JNIEnv *env, jobject thiz, jobject context) {
    
    jboolean isSuccess = checkSignature(env, thiz, context);
    return (*env)->NewStringUTF(env, isSuccess ? privateKey : "");
}

jstring getCachePackageName(JNIEnv *env, jobject thiz, jobject context) {
    
    initPackageName(env, thiz, context);
    return (*env)->NewStringUTF(env, mCache->package_name_cache);
}

jstring getCacheSignature(JNIEnv *env, jobject thiz, jobject context) {
    
    initSignature(env, thiz, context);
    return (*env)->NewStringUTF(env, mCache->signature_cache);
}


//android.content.Context
static const JNINativeMethod methods[] = {
        "_checkPackageName", "(Landroid/content/Context;)Z", &checkPackageName,
        "_checkSignature", "(Landroid/content/Context;)Z", &checkSignature,
        "_getEncodePwdPublicKey", "(Landroid/content/Context;)Ljava/lang/String;",
        &getEncodePwdPublicKey,
        "_getEncodeConfigPrivateKey", "(Landroid/content/Context;)Ljava/lang/String;",
        &getEncodeConfigPrivateKey,
        "_getCachePackageName", "(Landroid/content/Context;)Ljava/lang/String;",
        &getCachePackageName,
        "_getCacheSignature", "(Landroid/content/Context;)Ljava/lang/String;", &getCacheSignature
};


void initJNICache(JNIEnv *env) {
    mCache = (JNICache *) malloc(sizeof(JNICache));
    jstring pa_temp = (*env)->NewStringUTF(env, packageName);
    int pa_length = (*env)->GetStringUTFLength(env, pa_temp);
    jstring sign_temp = (*env)->NewStringUTF(env, signature);
    int signature_length = (*env)->GetStringUTFLength(env, sign_temp);

    mCache->package_name_cache = (char *) malloc(pa_length + 1);
    mCache->signature_cache = (char *) malloc(signature_length + 1);
    memset(mCache->package_name_cache, 0, pa_length);
    memset(mCache->signature_cache, 0, signature_length);
    LOGD("%s\n", "================================================================");
    LOGD("mCache->package_name_cache = %s pa_length = %d\n", mCache->package_name_cache, pa_length);
    LOGD("mCache->signature_cache = %s signature_length = %d\n", mCache->signature_cache,
         signature_length);
    LOGD("%s\n", "================================================================");
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    LOGD("JNI_OnLoad = %s", "执行 JNI_OnLoad");
    JNIEnv *env = NULL;
    //通过Java虚拟机去创建JNIEnv
    jint jniVersion = -1;
    if ((*vm)->GetEnv(vm, (void **) (&env), JNI_VERSION_1_6) == JNI_OK) {
        jniVersion = JNI_VERSION_1_6;
    }

    if ((*vm)->GetEnv(vm, (void **) (&env), JNI_VERSION_1_4) == JNI_OK) {
        jniVersion = JNI_VERSION_1_4;
    }

    if ((*vm)->GetEnv(vm, (void **) (&env), JNI_VERSION_1_2) == JNI_OK) {
        jniVersion = JNI_VERSION_1_2;
    }
    if (jniVersion == -1) {
        return jniVersion;
    }

    //找到动态注册的JNI类

    jclass jniClass = (*env)->FindClass(env, jniClassPath);

    (*env)->RegisterNatives(env, jniClass, methods, sizeof(methods) / sizeof(JNINativeMethod));
    LOGD("jniVersion = %d", jniVersion);


    initJNICache(env);
    return jniVersion;

}


JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGD("JNI_OnUnload = %s", "执行 JNI_OnUnload");
    if (mCache != NULL) {
        LOGD("JNI_OnUnload = %s", "mCache != NULL");
        free((char *) mCache->package_name_cache);
        free((char *) mCache->signature_cache);
    }
}








