#include "switch.hpp"

#include "id_manager.hpp"

namespace comm_device
{

Switch::Switch(const char* dev_name, int switch_num)
{
    this->m_id = IdManager::get_devid(dev_name);
    this->m_num = switch_num;

    this->m_comm_queue = new thread_util::QueueSetter<struct comm_io::comm_frame_t> ("comm_thread");
}

bool Switch::get_status(void)
{
    struct comm_io::comm_frame_t send_frame;
    send_frame.id = this->m_id;
    send_frame.data_len = 0;

    uint8_t befo_hashcounter = comm_io::CommReader::get_hash_counter(this->m_id);

    this->m_comm_queue->add(send_frame);

    while(comm_io::CommReader::get_hash_counter(this->m_id) == befo_hashcounter)
    {
        thread_util::locker::yield();
    }

    uint8_t data[8];
    uint8_t data_len = comm_io::CommReader::get_data(this->m_id, data);

    if(data_len == 1)
    {
        if(data[0] & (0x01 << this->m_num) != 0)
        {
            return true;
        }else{
            return false;
        }
    }
}

}