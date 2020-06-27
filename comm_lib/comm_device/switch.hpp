#ifndef COMM_DEVICE_SWITCH_HPP
#define COMM_DEVICE_SWITCH_HPP

#include "comm_io/comm_io.hpp"
#include "thread_util/threadutil_queue.hpp"

namespace comm_device
{

class Switch
{
private:
    thread_util::QueueSetter<struct comm_io::comm_frame_t>*  m_comm_queue;

    uint8_t m_id;
    uint8_t m_num;

public:
    Switch(const char* dev_name, int switch_num);

    bool get_status(void);
};

}

#endif /*COMM_DEVICE_SWITCH_HPP*/