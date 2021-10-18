//
// Created by 28188 on 2021/10/18.
//

#include <cstring>
#include <pthread.h>
extern "C"{
#include <libavformat/avformat.h>
}
#include "FFmpegVideo.h"

FFmpegVideo::FFmpegVideo(const char *dataSource) {
    this->dataSource = new char [strlen(dataSource)];
    strcpy(this->dataSource,dataSource);
}

FFmpegVideo::~FFmpegVideo() {
    delete dataSource;
    dataSource = 0;
}

void *task_prepare(void *args){
    FFmpegVideo *fFmpegVideo = static_cast<FFmpegVideo *>(args);
    fFmpegVideo->_prepare();
    return 0;
}
/**
 * 解码流程
 * 读取的时候，如果在主线程访问 ，可能会存在问题，所以使用线程来完成
 */
void FFmpegVideo::prepare() {
    //创建一个线程
    pthread_create(&pid,0,task_prepare, this);
}

void FFmpegVideo::_prepare() {
    av_register_all();
    avformat_network_init();//初始化网络
    avFormatContext =avformat_alloc_context();
    AVDictionary *opts = NULL;
    //如果这么久都没有打开，就认为有问题
    av_dict_set(&opts, "timeout", "30000000", 0);

    avformat_open_input(&avFormatContext,dataSource,NULL,&opts);

}
