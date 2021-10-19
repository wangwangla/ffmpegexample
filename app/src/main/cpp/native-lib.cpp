#include <jni.h>
#include "FFmpegVideo.h"

extern "C" {
};

FFmpegVideo *fFmpegVideo;

JavaVM *javaVm = 0;
int JNI_OnLoad(JavaVM *vm,void *r){
    javaVm = vm;
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_kangwang_ffmpeddemo_play_DNPlayer_native_1prepare(JNIEnv *env, jobject thiz,
                                                           jstring source_data) {
    const char *sourceData = env->GetStringUTFChars(source_data, 0);
//   回调工具
    JavaCallHelper *javaCallHelper = new JavaCallHelper(javaVm,env,thiz);
    //创建播放器
    fFmpegVideo = new FFmpegVideo(javaCallHelper,sourceData);
    fFmpegVideo->prepare();
    //因为我们这这里删除了
    env->ReleaseStringUTFChars(source_data,sourceData);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_kangwang_ffmpeddemo_play_DNPlayer_native_1start(JNIEnv *env, jobject thiz) {
    // TODO: implement native_start()
    fFmpegVideo->start();
}