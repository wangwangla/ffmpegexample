//
// Created by 28188 on 2021/10/18.
//

#include <cstring>
#include <pthread.h>

#include "FFmpegVideo.h"
#include "macro.h"

FFmpegVideo::FFmpegVideo(JavaCallHelper *javaCallHelper,const char *dataSource) {
    this->javaCallHelper = javaCallHelper;
    this->dataSource = new char [strlen(dataSource)];
    strcpy(this->dataSource,dataSource);
}

FFmpegVideo::~FFmpegVideo() {
    DELETE(dataSource);
    DELETE(javaCallHelper);
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
    int ret = avformat_open_input(&avFormatContext,dataSource,NULL,0);
    if(ret != 0){
        javaCallHelper->error(THREAD_CHILD,FFMPEG_CAN_NOT_OPEN_URL);
        return;
    }

//    查找视频流
//  返回大于等于0 就是 成功
    avformat_find_stream_info(avFormatContext,0);
//    会解码到多个流
    for (int i = 0; i < avFormatContext->nb_streams; ++i) {
        //得到的是音频或者视频
        AVStream *stream = avFormatContext->streams[i];
//        包含解码的各种参数
        AVCodecParameters *codecParameters = stream->codecpar;
//        通过操作
//        都需要得到解码器
//      1.查值编码方式得到解码器
//
        AVCodec *dec = avcodec_find_decoder(codecParameters->codec_id);
        if(dec == NULL){
            javaCallHelper->error(THREAD_CHILD,FFMPEG_FIND_DECODER_FAIL);
            return;
        }
//        获取上下文
        AVCodecContext *context = avcodec_alloc_context3(dec);
        if(context == NULL){
            javaCallHelper->error(THREAD_CHILD,FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL);
            return;
        }

//        设置上下文中的参数
        ret = avcodec_parameters_to_context(context,codecParameters);
        if(ret < 0){
            javaCallHelper->error(THREAD_CHILD,FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL);
            return;
        }

//        参数设置完了，  然后打开
        ret = avcodec_open2(context,dec,0);
        if (ret!=0){
            javaCallHelper->error(THREAD_CHILD,FFMPEG_OPEN_DECODER_FAIL);
            return;
        }
        if(codecParameters->codec_type == AVMEDIA_TYPE_AUDIO){
            audioChannel = new AudioChannel(i);
        } else if (codecParameters->codec_type == AVMEDIA_TYPE_VIDEO){
            videoChannel = new VideoChannel(i);
        }
    }
    if (!audioChannel && !videoChannel){
        javaCallHelper->error(THREAD_CHILD,FFMPEG_NOMEDIA);
        return;
    }

//    准备就绪就通知java
    javaCallHelper->prepare(THREAD_CHILD);
}

void* play(void* args){
//    读取数据包
    FFmpegVideo *fFmpegVideo = static_cast<FFmpegVideo *>(args);
    fFmpegVideo->_start
    ();
//解码
    return 0;
}
//初始化指针一定要给默认值
void FFmpegVideo::start() {
    isPlaying = 1;
    pthread_create(&pid_play,0,play, this);
}

void FFmpegVideo::_start() {
    int ret  ;
    while (isPlaying){
        AVPacket *avPacket = av_packet_alloc();
        ret = av_read_frame(avFormatContext,avPacket);
        if (ret == 0){
            if (audioChannel&&avPacket->stream_index == audioChannel->audioChannel){

            } else if (videoChannel && avPacket->stream_index == videoChannel->videoIndex){
                videoChannel->packets.Push(avPacket);
            }

        } else if (ret == AVERROR_EOF){

        } else{

        }
    }
}
//动态库有加载顺序问题    静态库没有
