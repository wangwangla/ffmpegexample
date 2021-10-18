#include <jni.h>
#include "FFmpegVideo.h"

extern "C" {
};

FFmpegVideo *fFmpegVideo;
extern "C"
JNIEXPORT void JNICALL
Java_com_kangwang_ffmpeddemo_play_DNPlayer_native_1prepare(JNIEnv *env, jobject thiz,
                                                           jstring source_data) {
    const char *sourceData = env->GetStringUTFChars(source_data, 0);
    //创建播放器
    fFmpegVideo = new FFmpegVideo(sourceData);
    fFmpegVideo->prepare();
    //因为我们这这里删除了
    env->ReleaseStringUTFChars(source_data,sourceData);
}