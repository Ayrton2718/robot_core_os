//
//  threadutil_queue.hpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#ifndef THREADUTIL_QUEUE_HPP
#define THREADUTIL_QUEUE_HPP

#include <stdio.h>
#include "private/threadutil_locker.hpp"
#include "private/threadutil_multi_queue.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

/*
int main(int argc, char **args)
{
    thread_util::Queue<int> read(0);
    thread_util::Queue<int> send(0);
    send.add(100);
    if (read.size() > 0)
    {
        printf("%d\n", read.poll());
    }
    return 0;
}
 */

namespace thread_util
{

class QueueBasic
{
private:
    static locker                                   m_locker;

    static std::unordered_map<std::string, size_t>  m_key_index;        // key map
    
    static std::vector<multi_queue>                 m_multi_queue_array;

    size_t m_using_index;

    bool m_write_mode;
    size_t m_multi_queue_id;
    
    void nolock_constructor(std::string key, size_t data_size, bool write_mode);
    void nolock_destructor(void);
        
    void nolock_add(const void *input);
    
    void nolock_peak(void *output);

    void nolock_pop(void);
    
    size_t nolock_size(void);

protected:
    QueueBasic(std::string key, size_t data_size, bool write_mode);
    
    virtual ~QueueBasic(void);

    void basic_add(const void *input);
    
    void basic_poll(void *output);

    void basic_peak(void *output);

    void basic_pop(void);

    size_t basic_size(void);
};


template <typename T>
class QueueSetter : private QueueBasic
{
private:

public:
    QueueSetter(std::string key) : QueueBasic(key, sizeof(T), true)
    {
    }

    //データを受け取り、コピーをキューに入れる。
    void add(const T input)
    {
        this->basic_add(&input);
    }
};


template <typename T>
class QueueReader : private QueueBasic
{
private:

public:
    QueueReader(std::string key) : QueueBasic(key, sizeof(T), false)
    {
    }

    //取り出し&削除
    T poll(void)
    {
        T data;
        this->basic_poll(&data);
        return data;
    }

    //キューからデータを取り出し、outputにコピーする。
    T peak(void)
    {
        T data;
        this->basic_peak(&data);
        return data;
    }

    //キューの次のデータを削除する。
    void pop(void)
    {
        this->basic_pop();
    }

    //キューのサイズ
    size_t size(void)
    {
        size_t size = this->basic_size();
        return size;
    }
};

}

#endif /*THREADUTIL_QUEUE_HPP*/
