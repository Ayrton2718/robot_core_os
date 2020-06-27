//
//  threadutil_multi_queue.hpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#include "threadutil_multi_queue.hpp"

#include <string.h>

namespace thread_util
{

multi_queue::multi_queue(size_t  data_size)
{
    this->m_data_size = data_size;
}

size_t multi_queue::append_queue(void)
{
    bool found = false;
    size_t index;

    for(index = 0; index < this->m_queue_array.size(); index++)
    {
        if(this->m_queue_array[index].second == false)
        {
//            printf("thread util multi queue enable index:%zu\n", index);

            this->m_queue_array[index].second = true;
            found = true;
            break;
        }
    }
    
    if(found == false)
    {
//        printf("thread util multi queue append index:%zu\n", index);

        this->m_queue_array.emplace_back();
        index = this->m_queue_array.size() - 1;
        this->m_queue_array[index].second = true;
    }

    return index;
}

void multi_queue::erase_queue(size_t index)
{
    while(this->m_queue_array[index].first.size() > 0)
    {
        this->m_queue_array[index].first.pop();
    }
    this->m_queue_array[index].second = false;
    
//    printf("thread util multi queue disenable index:%zu\n", index);
}


void multi_queue::push(const void* input)
{
    for(size_t queue_index = 0; queue_index < this->m_queue_array.size(); queue_index++)
    {
        if(this->m_queue_array[queue_index].second == true)
        {
            void *copy_data = malloc(this->m_data_size);
            memcpy(copy_data, input, this->m_data_size);
            this->m_queue_array[queue_index].first.push(copy_data);
        }
    }
}

void multi_queue::front(size_t index, void* output)
{
    memcpy(output, this->m_queue_array[index].first.front(), this->m_data_size);
}

void multi_queue::pop(size_t index)
{
    void *inside_data = this->m_queue_array[index].first.front();
    free(inside_data);
    this->m_queue_array[index].first.pop();
}

size_t multi_queue::size(size_t index)
{
    return this->m_queue_array[index].first.size();
}

}

