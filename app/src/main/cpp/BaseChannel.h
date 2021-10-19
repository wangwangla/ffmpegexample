//
// Created by 28188 on 2021/10/19.
//

#ifndef FFMPEDDEMO_BASECHANNEL_H
#define FFMPEDDEMO_BASECHANNEL_H

extern "C"{
#include <libavcodec/avcodec.h>
};
#include "SafeQueue.h"

class BaseChannel {
public:
    BaseChannel(int channelIndex);
    virtual ~BaseChannel();
    int channelIndex;
    SafeQueue<AVPacket*> packets;

};


#endif //FFMPEDDEMO_BASECHANNEL_H
