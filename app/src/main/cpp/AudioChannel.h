//
// Created by 28188 on 2021/10/19.
//

#ifndef FFMPEDDEMO_AUDIOCHANNEL_H
#define FFMPEDDEMO_AUDIOCHANNEL_H


#include "BaseChannel.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class AudioChannel: public BaseChannel {
public:
    AudioChannel(int id,AVCodecContext *avCodecContext);
    ~AudioChannel();
    void play();
    void decode();
    void _play();
    void getPcm();
    int audioChannel;
private:
    pthread_t pid_audio_decode;
    pthread_t pid_audio_play;
    //引擎和接口
    SLObjectItf engineObject = 0;
    SLEngineItf engineInterface = 0;
    //混音
    SLObjectItf outputMixObject = 0;
    //播放器
    SLObjectItf audioPlayerObject;
    SLAndroidSimpleBufferQueueItf androidSimpleBufferQueueItf;
    SLPlayItf audioPlayInterface;
};


#endif //FFMPEDDEMO_AUDIOCHANNEL_H
