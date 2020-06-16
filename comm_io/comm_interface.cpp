#include "comm_interface.hpp"

namespace driver_comm
{

thread_util::locker                      CommReader::m_locker;
struct read_data_t*                      CommReader::m_data_lib[64];

CommReader::CommReader(void)
{

}

void CommReader::initializer(void)
{
    memset(m_data_lib, 0x00, sizeof(m_data_lib));
}

void CommReader::set_data(size_t id, const uint8_t* data_buff, uint8_t data_len)
{
    this->m_locker.lock();
    if(this->m_data_lib[id] == NULL)
    {
        this->m_data_lib[id] = (struct read_data_t*)malloc(sizeof(struct read_data_t));
    }

    this->m_data_lib[id]->hash_counter++;
    memcpy(this->m_data_lib[id]->data, data_buff, sizeof(uint8_t) * 8);
    this->m_data_lib[id]->data_len = data_len;
    this->m_locker.unlock();
}

uint8_t CommReader::get_data(size_t id, uint8_t* data_buff)
{
    uint8_t data_len;

    this->m_locker.lock();
    if(this->m_data_lib[id] == NULL)
    {
        memset(data_buff, 0x00, sizeof(uint8_t) * 8);
        data_len = 0;
    }else{
        this->m_data_lib[id]->hash_counter++;
        memcpy(data_buff, this->m_data_lib[id]->data, sizeof(uint8_t) * 8);
        data_len = this->m_data_lib[id]->data_len;
    }
    this->m_locker.unlock();

    return data_len;
}

uint8_t CommReader::get_hash_counter(size_t id)
{
    uint8_t hash_counter;

    this->m_locker.lock();
    if(this->m_data_lib[id] == NULL)
    {
        hash_counter = 0;
    }else{
        hash_counter = this->m_data_lib[id]->hash_counter;
    }
    this->m_locker.unlock();

    return hash_counter;
}

}