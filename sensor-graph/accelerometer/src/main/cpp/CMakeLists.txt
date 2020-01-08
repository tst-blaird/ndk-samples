cmake_minimum_required(VERSION 3.4.1)

find_package(Java)
if (Java_FOUND)
    SET(LIB_JAVA_INC ${CMAKE_BINARY_DIR}/java_inc)
    SET(LIB_JAVA_TEMP ${CMAKE_BINARY_DIR}/java_temp)

    SET(LIB_NATIVE_TEST_JAVA_HEADER ${LIB_JAVA_INC}/com_android_accelerometergraph_NativeTestRunner.h)
    SET(LIB_NATIVE_TEST_JAVA_API_DEF ${TEST_SRC_DIR}/java/com/android/accelerometergraph/NativeTestRunner.java)

    MESSAGE("*******************************************************************")
    MESSAGE("* LIB_JAVA_INC                 = ${LIB_JAVA_INC}")
    MESSAGE("* LIB_JAVA_TEMP                = ${LIB_JAVA_TEMP}")
    MESSAGE("* Java_JAVAC_EXECUTABLE        = ${Java_JAVAC_EXECUTABLE}")
    MESSAGE("* LIB_NATIVE_TEST_JAVA_HEADER   = ${LIB_NATIVE_TEST_JAVA_HEADER}")
    MESSAGE("* LIB_NATIVE_TEST_JAVA_API_DEF  = ${LIB_NATIVE_TEST_JAVA_API_DEF}")
    MESSAGE("*******************************************************************")

    add_custom_command(
            OUTPUT ${LIB_NATIVE_TEST_JAVA_HEADER}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAVA_INC}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_JAVA_TEMP}
            COMMAND echo ${Java_JAVAC_EXECUTABLE} -d ${LIB_JAVA_TEMP} -h ${LIB_JAVA_INC} ${LIB_NATIVE_TEST_JAVA_API_DEF}
            COMMAND ${Java_JAVAC_EXECUTABLE} -d ${LIB_JAVA_TEMP} -h ${LIB_JAVA_INC} ${LIB_NATIVE_TEST_JAVA_API_DEF}
            DEPENDS ${LIB_NATIVE_TEST_JAVA_API_DEF}
            COMMENT "Generating Java include file: ${LIB_NATIVE_TEST_JAVA_HEADER}"
    )

    INCLUDE_DIRECTORIES(${LIB_JAVA_INC})
    #error( "Java found!" )
else(Java_FOUND)
    message(
            FATAL_ERROR
            "Java not found!")
    error( "Java not found!" )
endif(Java_FOUND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

add_library(
        accelerometergraph
        SHARED
        sensorgraph.cpp)

# Include libraries needed for accelerometergraph lib
target_link_libraries(
        accelerometergraph
        android
        GLESv2
        log)

set(GOOGLETEST_ROOT ${ANDROID_NDK}/sources/third_party/googletest)
add_library(gtest STATIC ${GOOGLETEST_ROOT}/src/gtest_main.cc ${GOOGLETEST_ROOT}/src/gtest-all.cc)
target_include_directories(gtest PRIVATE ${GOOGLETEST_ROOT})
target_include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)

add_library(
        NativeTestRunner
        SHARED
        ${TEST_SRC_DIR}/cpp/nativeTestRunner.cpp
        ${LIB_NATIVE_TEST_JAVA_HEADER})

target_link_libraries (
        NativeTestRunner
        gtest
        accelerometergraph)
