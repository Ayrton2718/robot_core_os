//
//  threadutil_share.cpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#include "threadutil_share.hpp"

namespace thread_util
{

locker                                  ShareBasic::m_locker;
std::vector<void*>                      ShareBasic::m_share_array;
std::unordered_map<std::string, size_t> ShareBasic::m_key_index;

ShareBasic::ShareBasic(std::string key, size_t data_size)
{
    this->m_locker.lock();
    this->nolock_constructor(key, data_size);
    this->m_locker.unlock();
}

void ShareBasic::basic_write(const void *input)
{
    this->m_locker.lock();
    this->nolock_write(input);
    this->m_locker.unlock();
}

void ShareBasic::basic_read(void *output)
{
    this->m_locker.lock();
    this->nolock_read(output);
    this->m_locker.unlock();
}

void ShareBasic::nolock_constructor(std::string key, size_t data_size)
{
    this->m_data_size = data_size;

    if(this->m_key_index.find(key) != this->m_key_index.end()) {
        this->m_using_index = this->m_key_index[key];
    } else {
        printf("thread util share append key:%s\n", key.c_str());

        this->m_using_index = m_key_index.size();
        this->m_key_index.emplace(key, m_key_index.size());

        void *init_data = malloc(this->m_data_size);
        memset(init_data, 0x00, this->m_data_size);
        this->m_share_array.emplace_back(init_data);
    }
}

void ShareBasic::nolock_write(const void *input)
{
    memcpy(this->m_share_array[this->m_using_index], input, this->m_data_size);
}

void ShareBasic::nolock_read(void *output)
{
    memcpy(output, this->m_share_array[this->m_using_index], this->m_data_size);
}

};

