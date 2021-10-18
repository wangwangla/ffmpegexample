//
// Created by 28188 on 2021/10/18.
//

#ifndef FFMPEDDEMO_JAVACALLHELPER_H
#define FFMPEDDEMO_JAVACALLHELPER_H

/**
 * 帮助我们完成反射
 */

class JavaCallHelper {
public:
    JavaCallHelper(JavaVM *vm,JNIEnv *jniEnv,jobject instance);
    ~JavaCallHelper();

    /**
     * 当前是不是处于主线程
     * @param thread
     * @param errorCode
     */
    void error(int thread,int errorCode);

private:
    JavaVM *vm;
    JNIEnv *env;
    jobject instance;
    jmethodID errorMethod;
};


#endif //FFMPEDDEMO_JAVACALLHELPER_H
