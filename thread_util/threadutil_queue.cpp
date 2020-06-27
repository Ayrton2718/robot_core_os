//
//  threadutil_queue.cpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#include "threadutil_queue.hpp"

namespace thread_util
{

locker                                   QueueBasic::m_locker;
std::unordered_map<std::string, size_t>  QueueBasic::m_key_index;        // key map
std::vector<multi_queue>                 QueueBasic::m_multi_queue_array;


QueueBasic::QueueBasic(std::string key, size_t data_size, bool write_mode)
{
    this->m_locker.lock();
    this->nolock_constructor(key, data_size, write_mode);
    this->m_locker.unlock();
}

QueueBasic::~QueueBasic(void)
{
    this->m_locker.lock();
    this->nolock_destructor();
    this->m_locker.unlock();
}

void QueueBasic::basic_add(const void *input)
{
    this->m_locker.lock();
    this->nolock_add(input);
    this->m_locker.unlock();
}

void QueueBasic::basic_poll(void *output)
{
    this->m_locker.lock();
    this->nolock_peak(output);
    this->nolock_pop();
    this->m_locker.unlock();
}

void QueueBasic::basic_peak(void *output)
{
    this->m_locker.lock();
    this->nolock_peak(output);
    this->m_locker.unlock();
}

void QueueBasic::basic_pop(void)
{
    this->m_locker.lock();
    this->nolock_pop();
    this->m_locker.unlock();
}

size_t QueueBasic::basic_size(void)
{
    size_t size = 0;
    this->m_locker.lock();
    size = this->nolock_size();
    this->m_locker.unlock();

    return size;
}


void QueueBasic::nolock_constructor(std::string key, size_t data_size, bool write_mode)
{
    if(this->m_key_index.find(key) != this->m_key_index.end())
    {
        this->m_using_index = this->m_key_index[key];
    } else {
        printf("thread util queue append key:%s\n", key.c_str());
        
        this->m_using_index = m_key_index.size();
        this->m_key_index.emplace(key, m_key_index.size());
        
        this->m_multi_queue_array.emplace_back(data_size);
    }
    
    this->m_write_mode = write_mode;
    if(this->m_write_mode == false)
    {
        this->m_multi_queue_id = this->m_multi_queue_array[m_using_index].append_queue();
    }
}

void QueueBasic::nolock_destructor(void)
{
    if(this->m_write_mode == false)
    {
        this->m_multi_queue_array[m_using_index].erase_queue(this->m_multi_queue_id);
    }
}

void QueueBasic::nolock_add(const void *input)
{
    this->m_multi_queue_array[m_using_index].push(input);
}

void QueueBasic::nolock_peak(void *output)
{
    if(this->nolock_size() > 0)
    {
        this->m_multi_queue_array[this->m_using_index].front(this->m_multi_queue_id, output);
    }
}

void QueueBasic::nolock_pop(void)
{
    if(this->nolock_size() > 0)
    {
        this->m_multi_queue_array[this->m_using_index].pop(this->m_multi_queue_id);
    }
}

size_t QueueBasic::nolock_size(void)
{
    return this->m_multi_queue_array[this->m_using_index].size(this->m_multi_queue_id);
}

}
