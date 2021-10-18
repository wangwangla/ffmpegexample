//
// Created by 28188 on 2021/10/18.
//

#ifndef FFMPEDDEMO_FFMPEGVIDEO_H
#define FFMPEDDEMO_FFMPEGVIDEO_H


#include "JavaCallHelper.h"

class FFmpegVideo {
public:
    FFmpegVideo(JavaCallHelper *javaCallHelper,const char *dataSource);
    ~FFmpegVideo();
    void prepare();
    void _prepare();

private:
    char *dataSource;
    pthread_t pid;
    AVFormatContext *avFormatContext;
    JavaCallHelper *javaCallHelper;
};


#endif //FFMPEDDEMO_FFMPEGVIDEO_H
