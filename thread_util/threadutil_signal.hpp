//
//  threadutil_signal.hpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#ifndef THREADUTIL_SIGNAL_HPP
#define THREADUTIL_SIGNAL_HPP

#include <stdio.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include "private/threadutil_locker.hpp"

namespace thread_util
{

class SignalBasic
{
private:
    static locker                                           m_locker;
    static std::vector<std::pair<void*, std::vector<bool>>> m_signal_array;
    static std::unordered_map<std::string, size_t>          m_key_index;
    
    size_t m_using_index;
    size_t m_internal_using_index;
    size_t m_data_size;

    void nolock_constructor(std::string key, size_t data_size, bool send_mode);
    void nolock_broadcast(const void* send);
    bool nolock_wait_once(void *receive);
    
    void nolock_privatecast(size_t id, const void* send);
    size_t nolock_private_id(void);
    
protected:
    SignalBasic(std::string key, size_t data_size, bool send_mode);

    void basic_broadcast(const void* send);
    bool basic_wait_once(void* receive);
    
    void basic_privatecast(size_t id, const void* send);
    size_t basic_private_id(void);
};


template<typename T>
class SignalSender : private SignalBasic
{
public:
    SignalSender(std::string key) : SignalBasic(key, sizeof(T), true)
    {
    }

    //シグナルを送信する。
    void broadcast(const T send)
    {
        this->basic_broadcast(&send);
    }
    
    //指定されたIDにのみ送信する。
    void privatecast(size_t id, const T send)
    {
        this->basic_privatecast(id, &send);
    }

};


template<typename T>
class SignalReader : private SignalBasic
{
public:
    SignalReader(std::string key) : SignalBasic(key, sizeof(T), false)
    {
    }

    //新たなシグナルを受信するまで半永久的に待つ。
    T wait(void)
    {
        T output;
        while(this->basic_wait_once(&output) == false)
        {
            locker::yield();
        }
        return output;
    }

    //新たなシグナルを受信したかどうかを返す。
    bool wait_once(T* output)
    {
        return this->basic_wait_once(output);
    }
    
    //自身のシグナルIdを返す。
    size_t private_id(void)
    {
        return this->basic_private_id();
    }
};

}

#endif /*THREADUTIL_SIGNAL_HPP*/
