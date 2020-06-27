#ifndef COMM_DEVICE_DC_MOTOR_HPP
#define COMM_DEVICE_DC_MOTOR_HPP

#include "comm_io/comm_io.hpp"
#include "thread_util/threadutil_queue.hpp"

namespace comm_device
{

class DCMotor
{
private:
    thread_util::QueueSetter<struct comm_io::comm_frame_t>*  m_comm_queue;

    uint8_t m_id;
    uint8_t m_power;

public:
    DCMotor(const char* dev_name);

    void set_power(int power);  //-100 ~ 100.
};

}

#endif /*COMM_DEVICE_DC_MOTOR_HPP*/