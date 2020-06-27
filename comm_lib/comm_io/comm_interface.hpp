#ifndef COMM_IO_COMM_INTERFACE_HPP
#define COMM_IO_COMM_INTERFACE_HPP

#include "comm_can.hpp"

#include "../thread_util/threadutil.hpp"
#include "stdint.h"

namespace comm_io
{

class CommReader
{
private:
    typedef struct
    {
        uint8_t hash_counter;
        uint8_t data[8];
        uint8_t data_len;
    } read_data_t;

private:
    static thread_util::locker                      m_locker;
    static read_data_t*                             m_data_lib[64];

public:
    CommReader(void);
    static void initializer(void);

    static void set_data(size_t id, const uint8_t* data_buff, uint8_t data_len);

    static uint8_t get_data(size_t id, uint8_t* data_buff);

    static uint8_t get_hash_counter(size_t id);
};

// class CommSender
// {
// private:
//     typedef struct
//     {
//         uint8_t hash_counter;
//         uint8_t data[8];
//         uint8_t data_len;
//     } send_data_t;

// private:
//     static thread_util::locker                      m_locker;
//     static send_data_t*                             m_data_lib[64];

// public:
//     CommSender(void);
//     static void initializer(void);

//     static void set_data(size_t id, const uint8_t* data_buff, uint8_t data_len);

//     static uint8_t get_data(size_t id, uint8_t* data_buff);

//     static uint8_t get_hash_counter(size_t id);
// };

}

#endif /*COMM_IO_COMM_INTERFACE_HPP*/