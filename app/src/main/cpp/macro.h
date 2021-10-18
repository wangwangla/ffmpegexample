//
// Created by 28188 on 2021/10/18.
//

#ifndef FFMPEDDEMO_MACRO_H
#define FFMPEDDEMO_MACRO_H

#include <android/log.h>

#define LOGE(...) _android_log_print(ANDROID_LOG_ERROR,"FFMPEG",_VA_ARGS_)
#define DELETE(obj) if(obj){delete obj; obj = 0;}

#define THREAD_MAIN 1
#define THREAD_CHILD 2


#define FFMPEG_CAN_NOT_OPEN_URL 1
#define FFMPEG_CAN_NOT_FIND_STREAM 2
#define FFMPEG_FIND_DECODER_FAIL 3
#define FFMPPEEG_ALLOC_CONTEXT_FAIL 4

#define FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL 6
#define FFMPEG_OPEN_DECODER_FAIL 7
#define FFMPEG_NOMEDIA 8



#endif //FFMPEDDEMO_MACRO_H
