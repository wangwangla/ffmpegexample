//
// Created by 28188 on 2021/10/19.
//

#include "AudioChannel.h"

/**
 * 将参数传递给父类
 * @param id
 */
AudioChannel::AudioChannel(int id):BaseChannel(id) {


    SLresult result;
    result = slCreateEngine(&engineObject,0,NULL,0,NULL,NULL);
    if (result!=SL_RESULT_SUCCESS){
        return;
    }
    result = (*engineObject)->Realize(engineObject,SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS){
        return;
    }

    result = (*engineObject)->GetInterface(
            engineObject,
            SL_IID_ENGINE,
            &engineInterface
            );


    if(result != SL_RESULT_SUCCESS){
        return;
    }

    //2
    result = (*engineInterface)->CreateOutputMix(engineInterface,
                                           &outputMixObject,
                                           0,
                                           0,0);
    if (SL_RESULT_SUCCESS != result){
        return;
    }

    result = (*outputMixObject)->Realize(outputMixObject,SL_BOOLEAN_FALSE);
    if (result!=SL_RESULT_SUCCESS){
        return;
    }

    //3创建播放器
    SLDataLocator_AndroidBufferQueue android_queue = {
        SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,2
    };

    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,2,
            SL_SAMPLINGRATE_44_1,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN
    };
    SLDataSource slDataSource = {
            &android_queue,&pcm
    };

    SLDataLocator_OutputMix outputMix = {
        SL_DATALOCATOR_OUTPUTMIX,
        outputMixObject
    };

    SLDataSink audioSnk = {
            &outputMix,NULL
    };
    const SLInterfaceID ids[1] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[1] = {SL_BOOLEAN_TRUE};

    (*engineInterface)->CreateAudioPlayer(
            engineInterface,

            );
}
