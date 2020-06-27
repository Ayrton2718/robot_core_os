//
//  threadutil_callback.hpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#ifndef THREADUTIL_CALLBACK_HPP
#define THREADUTIL_CALLBACK_HPP

#include <stdio.h>
#include "private/threadutil_locker.hpp"

#include "threadutil_queue.hpp"
#include "threadutil_signal.hpp"

namespace thread_util
{

struct Callback_args_t
{
    const void  *data;
    size_t      signal_private_id;
};

template <typename ARG_T, typename RET_T>
class CallbackCall : private QueueSetter<struct Callback_args_t>, private SignalReader<RET_T>
{
private:
    size_t m_private_id;

public:
    CallbackCall(std::string key) : QueueSetter<struct Callback_args_t> ("callback_" + key), SignalReader<RET_T> ("callback_" + key)
    {
        this->m_private_id = this->private_id();
    }
    
    // 呼び出し、別スレッドの関数の戻り値を受け取るまで待機。
    RET_T call(ARG_T send_data)
    {
        struct Callback_args_t args = {&send_data, this->m_private_id};
        this->add(args);
        
        return this->wait();
    }
};

template <typename ARG_T>
class CallbackCall<ARG_T, void> : private QueueSetter<ARG_T>
{
private:

public:
    CallbackCall(std::string key) : QueueSetter<ARG_T> ("callback_" + key)
    {
    }
    
    // 呼び出す。関数の終了をまたない。
    void call(ARG_T send_data)
    {
        this->add(send_data);
    }
};


template <typename ARG_T, typename RET_T>
class CallbackReply : private QueueReader<struct Callback_args_t>, private SignalSender<RET_T>
{
private:
    RET_T (*m_callback)(ARG_T);

public:
    CallbackReply(std::string key, RET_T (*callback)(ARG_T)) : QueueReader<struct Callback_args_t> ("callback_" + key), SignalSender<RET_T> ("callback_" + key)
    {
        this->m_callback = callback;
    }

    // 呼び出されるまで待機。
    void wait(void)
    {
        while(this->size() <= 0)
        {
            thread_util::locker::yield();
        }

        struct Callback_args_t args = this->poll();
        this->privatecast(args.signal_private_id, m_callback(*((ARG_T*)args.data)));
    }

    // 呼び出されているか、チェックして、呼び出されていた場合は、関数を実行する。
    void wait_once(void)
    {
        if(this->size() > 0)
        {
            struct Callback_args_t args = this->poll();
            this->privatecast(args.signal_private_id, m_callback(*((ARG_T*)args.data)));
        }
    }
};

template <typename ARG_T>
class CallbackReply<ARG_T, void> : private QueueReader<ARG_T>
{
private:
    void (*m_callback)(ARG_T);

public:
    CallbackReply(std::string key, void (*callback)(ARG_T)) : QueueReader<ARG_T> ("callback_" + key)
    {
        m_callback = callback;
    }

    // 呼び出されるまで待機。
    void wait(void)
    {
        while(this->size() <= 0)
        {
            thread_util::locker::yield();
        }

        m_callback(this->poll());
    }

    // 呼び出されているか、チェックして、呼び出されていた場合は、関数を実行する。
    void wait_once(void)
    {
        if(this->size() > 0)
        {
            m_callback(this->poll());
        }
    }
};

}


#endif /*THREADUTIL_CALLBACK_HPP*/
