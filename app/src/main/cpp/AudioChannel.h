//
// Created by 28188 on 2021/10/19.
//

#ifndef FFMPEDDEMO_AUDIOCHANNEL_H
#define FFMPEDDEMO_AUDIOCHANNEL_H


#include "BaseChannel.h"

class AudioChannel: public BaseChannel {
public:
    AudioChannel(int id);
    virtual ~AudioChannel();
    int audioChannel;

};


#endif //FFMPEDDEMO_AUDIOCHANNEL_H
