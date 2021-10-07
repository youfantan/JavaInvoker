//
// Created by shandiankulishe on 2021/10/4.
//
#define UNICODE
#include <string>
#include <windows.h>
#include <io.h>
#include <vector>
#include <fstream>
#include <tchar.h>
#include <conio.h>
#include <wchar.h>
using namespace std;
#ifndef JAVAINVOKER_JVMLOCATOR_H
#define JAVAINVOKER_JVMLOCATOR_H


class JVMLocator {
public:
    __declspec(dllexport)
     /*
     使用此函数以在默认路径中寻找jvm.dll
     参数列表：
      result: 查找后的路径将写入此对象，此外，如果使用这种方法无法查找到JRE/JDK，将返回false，此时vector内容为空
     */
    static bool findInEnv(vector<string> *result);
    __declspec(dllexport)
    /*
    使用此函数以在环境变量JAVA_HOME中寻找jvm.dll
    参数列表：
     result: 查找后的路径将写入此对象，此外，如果使用这种方法无法查找到JRE/JDK，将返回false，此时vector内容为空
    */
    static bool findInPath(vector<string> *result);
    __declspec(dllexport)
    /*
    使用此函数以在环境变量PATH中寻找jvm.dll
    参数列表：
     result: 查找后的路径将写入此对象，此外，如果使用这种方法无法查找到JRE/JDK，将返回false，此时vector内容为空
    */
    static bool findInDefaultDir(vector<string> *result);
    __declspec(dllexport)
    /*
    使用此函数以在注册表中寻找jvm.dll
    参数列表：
     result: 查找后的路径将写入此对象，此外，如果使用这种方法无法查找到JRE/JDK，将返回false，此时vector内容为空
    */
    static bool findInReg(vector<string> *result);
};


#endif //JAVAINVOKER_JVMLOCATOR_H
