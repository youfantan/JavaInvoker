//
// Created by shandiankulishe on 2021/10/4.
//
#include "jni.h"
#include <string>
#include <windows.h>
using namespace std;
#ifndef JAVAINVOKER_JVMFACTORY_H
#define JAVAINVOKER_JVMFACTORY_H


class JVMFactory {
public:
    __declspec(dllexport)
    /*
     使用此函数以创建JVM
     参数列表：
     jvm: 在创建完成JVM后，返回JVM指针
     env: 在创建完成JVM后，返回JNIEnv指针
     options[]: JVM参数，如-Djava.class.path=.\ 设置ClassPath
     nOptions: 参数个数
     jvmPath: jvm.dll所在路径
     */
    static int createJVM(JavaVM** jvm,JNIEnv** env,JavaVMOption options[],size_t nOptions,string jvmPath);
};


#endif //JAVAINVOKER_JVMFACTORY_H
