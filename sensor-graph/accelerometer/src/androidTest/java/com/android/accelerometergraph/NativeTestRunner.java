package com.android.accelerometergraph;

public class NativeTestRunner {

    public native boolean runUnitTests();

    static {
        System.loadLibrary("NativeTestRunner");
    }
}
