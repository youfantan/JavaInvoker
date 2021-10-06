//
// Created by shandiankulishe on 2021/10/4.
//
#include <gtest/gtest.h>
#include "../src/JVMLocator.h"
TEST(TestJavaInvoker,TestJVMLocator)
{
    vector<string> vct;
    ASSERT_TRUE(JVMLocator::findInDefaultDir(&vct));
    for (auto & i : vct) {
        printf("jvm.dll in Default Install Directory:%s\n",i.c_str());
    }
    vct.clear();
    ASSERT_TRUE(JVMLocator::findInEnv(&vct));
    for (auto & i : vct) {
        printf("jvm.dll in OS Environment:%s\n",i.c_str());
    }
    vct.clear();
    ASSERT_TRUE(JVMLocator::findInPath(&vct));
    for (auto & i : vct) {
        printf("jvm.dll in Path:%s\n",i.c_str());
    }
    vct.clear();
    ASSERT_TRUE(JVMLocator::findInReg(&vct));
    for (auto & i : vct) {
        printf("jvm.dll in Reg:%s\n",i.c_str());
    }
}