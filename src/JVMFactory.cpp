//
// Created by shandiankulishe on 2021/10/4.
//

#include "JVMFactory.h"

typedef jint(JNICALL* JNICREATEPROC)(JavaVM **pvm, void** penv, void* args);

int JVMFactory::createJVM(JavaVM **jvm, JNIEnv **env, JavaVMOption options[], size_t nOptions, string jvmPath) {
    JavaVMInitArgs args;
    args.version = JNI_VERSION_1_8;
    args.options = options;
    args.nOptions = nOptions;
    args.ignoreUnrecognized = JNI_TRUE;
    HMODULE jvmDll = LoadLibraryA(jvmPath.c_str());
    if (jvmDll == NULL)
    {
        return -1;
    }
    JNICREATEPROC jvmProcAddr = (JNICREATEPROC)GetProcAddress(jvmDll, "JNI_CreateJavaVM");
    if (jvmDll == NULL)
    {
        return -1;
    }
    jint jvmProc = jvmProcAddr(jvm, (void**)env, &args);
    if (jvmProc < 0 || jvm == nullptr || env == nullptr)
    {
        return -1;
    }
    return 0;
}
