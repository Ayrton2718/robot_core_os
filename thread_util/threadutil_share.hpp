//
//  threadutil_share.hpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#ifndef THREADUTIL_SHARE_HPP
#define THREADUTIL_SHARE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>
#include "private/threadutil_locker.hpp"

namespace thread_util
{

void Share_init(size_t use_count);

class ShareBasic
{
private:
    static locker m_locker;
    static std::vector<void*> m_share_array;
    static std::unordered_map<std::string, size_t> m_key_index;

    size_t m_using_index;
    size_t m_data_size;

    void nolock_constructor(std::string key, size_t data_size);
    void nolock_write(const void* input);
    void nolock_read(void *output);

protected:
    ShareBasic(std::string key, size_t data_size);

    void basic_write(const void* input);
    void basic_read(void *output);
};

template<typename T>
class Share : protected ShareBasic
{
public:
    Share(std::string key) : ShareBasic(key, sizeof(T)) {};

    //共有変数に代入
    void write(const T input)
    {
        this->basic_write(&input);
    }

    //共有変数の値を取得
    T read(void)
    {
        T data;
        this->basic_read(&data);
        return data;
    }

};

}

#endif /*THREADUTIL_SHAREHPP*/
