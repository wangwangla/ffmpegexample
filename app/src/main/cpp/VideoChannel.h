//
// Created by 28188 on 2021/10/19.
//

#ifndef FFMPEDDEMO_VIDEOCHANNEL_H
#define FFMPEDDEMO_VIDEOCHANNEL_H


#include "BaseChannel.h"

class VideoChannel: public BaseChannel {
public:
    VideoChannel(int videoIndex);
    virtual ~VideoChannel();

    int videoIndex;

};


#endif //FFMPEDDEMO_VIDEOCHANNEL_H
