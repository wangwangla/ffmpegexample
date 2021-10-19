//
// Created by 28188 on 2021/10/19.
//

#ifndef FFMPEDDEMO_DEMOSAFE_H
#define FFMPEDDEMO_DEMOSAFE_H

using namespace std;
template<typename T>

class DemoSafe{
    typedef void (*ReaseCallBack)(T *);
    typedef void (*SyncHandle)(queue<T> &);

public:
    DemoSafe(){
        pthread_mutex_init(&mutex,NULL);
        pthread_cond_init(&cond,NULL);
    }
    ~DemoSafe(){
        pthread_cond_destory(&cond);
        pthread_mutex_destory(&mutex);
    }
};


#endif //FFMPEDDEMO_DEMOSAFE_H
