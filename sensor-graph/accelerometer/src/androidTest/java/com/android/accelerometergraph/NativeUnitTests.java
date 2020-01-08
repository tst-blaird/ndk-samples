package com.android.accelerometergraph;

import android.content.Context;
import android.content.res.AssetManager;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;
import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.io.File;

import static org.junit.Assert.*;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 * Run these tests by executing 'gradlew connectedCheck'
 */
@RunWith(AndroidJUnit4.class)
public class NativeUnitTests {

    private Context testContext;

    public NativeUnitTests() {

        try {
            // Context of the app under test.
            testContext = InstrumentationRegistry.getContext();

            AssetManager assetManager = testContext.getResources().getAssets();
            String items[] = testContext.getResources().getAssets().list("");
            Log.i("NATIVE_TESTS", String.format("testContext, resources, assets, list size = %d", items.length));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Test
    public void sampleOnDeviceTest() {
        assertEquals("com.android.accelerometergraph.test", testContext.getPackageName());
    }

    public boolean setUpUnitTests() {
        return true;
    }

    @Test
    public void runTheNativeTests() {

        assertTrue(setUpUnitTests());

        NativeTestRunner runner = new NativeTestRunner();
        assertTrue(runner.runUnitTests());
    }
}
