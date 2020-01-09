//
// Created by blaird on 1/9/2020.
//

#ifndef SENSOR_GRAPH_SENSORGRAPH_H
#define SENSOR_GRAPH_SENSORGRAPH_H

// OpenGL ES 2.0 code
#include <dlfcn.h>
#include <jni.h>
#include <GLES2/gl2.h>

#include <android/log.h>
#include <android/asset_manager_jni.h>
#include <android/sensor.h>

#include <cstdint>
#include <cassert>
#include <string>

#define  LOG_TAG    "accelerometergraph"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

const int LOOPER_ID_USER = 3;
const int SENSOR_HISTORY_LENGTH = 100;
const int SENSOR_REFRESH_RATE_HZ = 100;
constexpr int32_t SENSOR_REFRESH_PERIOD_US = int32_t(1000000 / SENSOR_REFRESH_RATE_HZ);
const float SENSOR_FILTER_ALPHA = 0.1f;

class sensorgraph {
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    ASensorManager *sensorManager;
    const ASensor *accelerometer;
    ASensorEventQueue *accelerometerEventQueue;
    ALooper *looper;

    GLuint shaderProgram;
    GLuint vPositionHandle;
    GLuint vSensorValueHandle;
    GLuint uFragColorHandle;
    GLfloat xPos[SENSOR_HISTORY_LENGTH];

    struct AccelerometerData {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };
    AccelerometerData sensorData[SENSOR_HISTORY_LENGTH*2];
    AccelerometerData sensorDataFilter;
    int sensorDataIndex;

public:
    sensorgraph();
    void init(AAssetManager *assetManager);
    void surfaceCreated();
    void surfaceChanged(int w, int h);
    void generateXPos();
    GLuint createProgram(const std::string& pVertexSource, const std::string& pFragmentSource);
    GLuint loadShader(GLenum shaderType, const std::string& pSource);
    void update();
    void render();
    void pause();
    void resume();
};

#endif //SENSOR_GRAPH_SENSORGRAPH_H
