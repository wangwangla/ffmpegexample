//
// Created by 28188 on 2021/10/18.
//

#ifndef FFMPEDDEMO_FFMPEGVIDEO_H
#define FFMPEDDEMO_FFMPEGVIDEO_H


class FFmpegVideo {
public:
    FFmpegVideo(const char *dataSource);
    ~FFmpegVideo();
    void prepare();
    void _prepare();

private:
    char *dataSource;
    pthread_t pid;
    AVFormatContext *avFormatContext;
};


#endif //FFMPEDDEMO_FFMPEGVIDEO_H
