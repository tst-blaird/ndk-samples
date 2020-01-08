//
// Created by blaird on 1/7/2020.
//

#include <jni.h>
#include <com_android_accelerometergraph_NativeTestRunner.h>
#include <gtest/gtest.h>
#include <android/log.h>

JavaVM * javaVm = nullptr;
jclass globalNativeTestRunnerJavaClass = nullptr;
std::string testFilesDir;

extern "C" {
#define NATIVE_TEST_RUNNER(method) Java_com_android_accelerometergraph_NativeTestRunner_ ## method

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    if (!vm)
    {
        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "Invalid java vm!!!");
        return 0;
    }

    javaVm = vm;
    JNIEnv* env = nullptr;
    javaVm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
    if (!env)
    {
        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "Failed to get java environment on load!!!!");
        return 0;
    }

    { // get a global ref to the java class and cache it
            jclass nativeTestRunner = env->FindClass("com/android/accelerometer/NativeTestRunner");
            if (!nativeTestRunner) {
                __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "Failed to find NativeTestRunner java class!!!");
            return 0;
        }
        globalNativeTestRunnerJavaClass = static_cast<jclass>(env->NewGlobalRef(nativeTestRunner));
        if (!globalNativeTestRunnerJavaClass) {
            __android_log_print(ANDROID_LOG_ERROR, "NATIVE",
                    "Failed to get global ref of NativeTestRunner java class!!!");
            return 0;
        }
        env->DeleteLocalRef(nativeTestRunner);
        nativeTestRunner = nullptr;
    }

    __android_log_print(ANDROID_LOG_INFO, "NATIVE", "Java native test runner library successfully loaded!");

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM * vm, void *)
{
    if (!vm)
    {
        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "Unload called with invalid vm pointer...");
        return;
    }

    __android_log_print(ANDROID_LOG_INFO, "NATIVE", "Unloading java native library!");

    JNIEnv* env = nullptr;
    vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
    if (!env) {
        __android_log_print(ANDROID_LOG_ERROR, "NATIVE", "Failed to get java environment on unload!!!!");
        return;
    }

    if (globalNativeTestRunnerJavaClass){
        // Destroy the global class references
        env->DeleteGlobalRef(globalNativeTestRunnerJavaClass);
        globalNativeTestRunnerJavaClass = nullptr;
    }

    javaVm = nullptr;
}

jboolean JNICALL
NATIVE_TEST_RUNNER(runUnitTests)(JNIEnv *env, jobject obj) {
    //int argc = 1;
    //char* argv[] = { "AndroidNativeUnitTests", NULL };

    try {
        //testing::InitGoogleTest(&argc, argv);
        testing::InitGoogleTest();
        int result = RUN_ALL_TESTS();
        return (result == 0) ? JNI_TRUE : JNI_FALSE;
    }
        catch (...) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

} // extern "C"
