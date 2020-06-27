#ifndef COMM_IO_COMM_INTERFACE_HPP
#define COMM_IO_COMM_INTERFACE_HPP

#include "comm_io.hpp"

#include "../thread-util/threadutil.hpp"
#include "stdint.h"

namespace comm_io
{

struct read_data_t
{
    uint8_t hash_counter;
    uint8_t data[8];
    uint8_t data_len;
};

class CommReader
{
private:
    static thread_util::locker                      m_locker;
    static struct read_data_t*                      m_data_lib[64];

public:
    CommReader(void);
    static void initializer(void);

    static void set_data(size_t id, const uint8_t* data_buff, uint8_t data_len);

    static uint8_t get_data(size_t id, uint8_t* data_buff);

    static uint8_t get_hash_counter(size_t id);
};

}

#endif /*COMM_IO_COMM_INTERFACE_HPP*/