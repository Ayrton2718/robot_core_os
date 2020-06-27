//
//  threadutil_multi_queue.hpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#ifndef THREADUTIL_MULTI_QUEUE_HPP
#define THREADUTIL_MULTI_QUEUE_HPP

#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <queue>

namespace thread_util
{

class multi_queue
{
private:
    size_t                                              m_data_size;
    std::vector<std::pair<std::queue<void*>, bool>>     m_queue_array;

public:
    multi_queue(size_t data_size);
    
    size_t append_queue(void);
    
    void erase_queue(size_t index);
    
    void push(const void* input);
    
    void front(size_t index, void* output);
    
    void pop(size_t index);
    
    size_t size(size_t index);
};

}

#endif /*THREADUTIL_MULTI_QUEUE_HPP*/
