//
// Created by 28188 on 2021/10/18.
//

#ifndef FFMPEDDEMO_FFMPEGVIDEO_H
#define FFMPEDDEMO_FFMPEGVIDEO_H


#include "JavaCallHelper.h"
#include "VideoChannel.h"
#include "AudioChannel.h"
#include <pthread.h>
extern "C"{
#include <libavformat/avformat.h>
}


class FFmpegVideo {
public:
    FFmpegVideo(JavaCallHelper *javaCallHelper,const char *dataSource);
    ~FFmpegVideo();
    void prepare();
    void _prepare();

    void start();

    void _start();

private:
    char *dataSource;
    pthread_t pid;
    pthread_t pid_play;
    AVFormatContext *avFormatContext;
    JavaCallHelper *javaCallHelper;
    AudioChannel *audioChannel;
    VideoChannel *videoChannel;
    bool isPlaying;
};


#endif //FFMPEDDEMO_FFMPEGVIDEO_H
