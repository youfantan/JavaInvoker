//
// Created by shandiankulishe on 2021/10/5.
//

#include <gtest/gtest.h>
#include "../src/JVMFactory.h"
#include "../src/JVMLocator.h"
int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
bool findJvm(string &jvmPath){
    vector<string> vct;
    if (JVMLocator::findInDefaultDir(&vct)){
        jvmPath=vct[0];
        return true;
    }
    if (JVMLocator::findInEnv(&vct)){
        jvmPath=vct[0];
        return true;
    }
    if (JVMLocator::findInPath(&vct)){
        jvmPath=vct[0];
        return true;
    }
    if (JVMLocator::findInReg(&vct)){
        jvmPath=vct[0];
        return true;
    }
    return false;
}
TEST(TestJavaInvoker,TestJVMFactory)
{
    string classPath = ".\\Test.jar";
    string jvmPath;
    if (findJvm(jvmPath)){
        JavaVMOption options[3];
        string cpArg = "-Djava.class.path=" + classPath;
        char opt1[]="-Djava.compiler=NONE";
        options[0].optionString = opt1;
        options[1].optionString = (char*)cpArg.c_str();
        JavaVM* jvm;
        JNIEnv* env;
        ASSERT_EQ(0,JVMFactory::createJVM(&jvm, &env, options, 2, jvmPath));
        jclass cls = env->FindClass("Test");
        jmethodID jmid = env->GetStaticMethodID(cls, "test", "()V");
        env->CallStaticVoidMethod(cls, jmid);
    } else{
        throw "no jvm.dll found.please install a jre first";
    }
}