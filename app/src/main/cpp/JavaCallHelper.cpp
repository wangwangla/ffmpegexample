//
// Created by 28188 on 2021/10/18.
//


#include "JavaCallHelper.h"
#include "macro.h"

JavaCallHelper::JavaCallHelper(JavaVM *vm, JNIEnv *jniEnv,jobject instance) {
    this->env = env;
    this->vm = vm;
    //jobject涉及到跨方法，跨进程 就需要一个全局引用
    this->instance = env->NewGlobalRef(instance);

    jclass  clazz = env->GetObjectClass(instance);
    errorMethod = env->GetMethodID(clazz,"onError","(I)V");
    prepareMethod = env->GetMethodID(clazz,"prapare","()V");
}

JavaCallHelper::~JavaCallHelper() {
    env->DeleteGlobalRef(instance);
}

void JavaCallHelper::error(int thread, int errorCode) {
    if (thread == THREAD_MAIN){
        //如果是主线程，那么就直接调用
        env->CallVoidMethod(instance,errorMethod,errorCode);
    } else{
        //如果不是主线程   就获取线程的env   env是不可以跨线程的
        //将当前的env附加到vm线程
        JNIEnv *env;
        vm->AttachCurrentThread(&env,0);
//        在通过这个env来调用
        env->CallVoidMethod(instance,errorMethod,errorCode);
//      调用完成之后  在从vm中删除依附
        vm->DetachCurrentThread();
    }
}

void JavaCallHelper::prepare(int thread) {
    if (thread == THREAD_CHILD){
        env->CallVoidMethod(instance,prepareMethod);
    } else if (thread == THREAD_MAIN){
        JNIEnv *env;
        vm->AttachCurrentThread(&env,0);
        env->CallVoidMethod(instance,prepareMethod);
        vm->DetachCurrentThread();
    }

}
