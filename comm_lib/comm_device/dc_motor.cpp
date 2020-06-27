#include "dc_motor.hpp"

#include "id_manager.hpp"

namespace comm_device
{

DCMotor::DCMotor(const char* dev_name)
{
    this->m_id = IdManager::get_devid(dev_name);
    this->m_power = 0;

    this->m_comm_queue = new thread_util::QueueSetter<struct comm_io::comm_frame_t> ("comm_thread");
}

void DCMotor::set_power(int power)
{
    struct comm_io::comm_frame_t send_frame;

    if(100 < power)
    {
        power = 100;
    }else if(power < -100){
        power = -100;
    }

    send_frame.id = this->m_id;
    send_frame.data[0] = (int8_t)power;
    send_frame.data_len = 0;

    this->m_comm_queue->add(send_frame);
}

}