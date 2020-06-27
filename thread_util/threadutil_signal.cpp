//
//  threadutil_signalcpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#include "threadutil_signal.hpp"

namespace thread_util
{

locker                                           SignalBasic::m_locker;
std::vector<std::pair<void*, std::vector<bool>>> SignalBasic::m_signal_array;
std::unordered_map<std::string, size_t>          SignalBasic::m_key_index;


SignalBasic::SignalBasic(std::string key, size_t data_size, bool send_mode)
{
    this->m_locker.lock();
    this->nolock_constructor(key, data_size, send_mode);
    this->m_locker.unlock();
}


void SignalBasic::basic_broadcast(const void *send)
{
    this->m_locker.lock();
    this->nolock_broadcast(send);
    this->m_locker.unlock();
}

bool SignalBasic::basic_wait_once(void *receive)
{
    this->m_locker.lock();
    bool val = this->nolock_wait_once(receive);
    this->m_locker.unlock();
    return val;
}

void SignalBasic::basic_privatecast(size_t id, const void* send)
{
    this->m_locker.lock();
    this->nolock_privatecast(id, send);
    this->m_locker.unlock();
}

size_t SignalBasic::basic_private_id(void)
{
    this->m_locker.lock();
    size_t val = this->nolock_private_id();
    this->m_locker.unlock();
    return val;
}

void SignalBasic::nolock_constructor(std::string key, size_t data_size, bool send_mode)
{
    this->m_data_size = data_size;
    
    if(this->m_key_index.find(key) != this->m_key_index.end())
    {
        this->m_using_index = this->m_key_index[key];
    }
    else
    {
        this->m_using_index = this->m_key_index.size();
        this->m_key_index.emplace(key, this->m_key_index.size());
        
        this->m_signal_array.emplace_back();
        
        void *init_data = malloc(this->m_data_size);
        memset(init_data, 0x00, this->m_data_size);
        this->m_signal_array[this->m_using_index].first = init_data;
    }
    
    if(send_mode == false)
    {
        this->m_internal_using_index = this->m_signal_array[this->m_using_index].second.size();
        this->m_signal_array[this->m_using_index].second.push_back(false);
    }
}

void SignalBasic::nolock_broadcast(const void *send)
{
    memcpy(this->m_signal_array[this->m_using_index].first, send, this->m_data_size);
    
    for(size_t internal_index = 0; internal_index < this->m_signal_array[m_using_index].second.size(); internal_index++)
    {
        this->m_signal_array[this->m_using_index].second[internal_index] = true;
    }
}

bool SignalBasic::nolock_wait_once(void *receive)
{
    bool arrived = false;
    if(this->m_signal_array[this->m_using_index].second[this->m_internal_using_index])
    {
        memcpy(receive, this->m_signal_array[m_using_index].first, this->m_data_size);
        this->m_signal_array[m_using_index].second[m_internal_using_index] = false;
        arrived = true;
    }
    return arrived;
}

void SignalBasic::nolock_privatecast(size_t id, const void* send)
{
    memcpy(this->m_signal_array[this->m_using_index].first, send, this->m_data_size);
    this->m_signal_array[this->m_using_index].second[id] = true;
}

size_t SignalBasic::nolock_private_id(void)
{
    return this->m_internal_using_index;
}

}

