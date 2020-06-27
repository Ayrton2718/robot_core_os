#include "comm_interface.hpp"

namespace comm_io
{

thread_util::locker                      CommReader::m_locker;
CommReader::read_data_t*                 CommReader::m_data_lib[64];

CommReader::CommReader(void)
{

}

void CommReader::initializer(void)
{
    memset(m_data_lib, 0x00, sizeof(m_data_lib));
}

void CommReader::set_data(size_t id, const uint8_t* data_buff, uint8_t data_len)
{
    m_locker.lock();
    if(m_data_lib[id] == NULL)
    {
        m_data_lib[id] = (read_data_t*)malloc(sizeof(read_data_t));
    }

    m_data_lib[id]->hash_counter++;
    memcpy(m_data_lib[id]->data, data_buff, sizeof(uint8_t) * 8);
    m_data_lib[id]->data_len = data_len;
    m_locker.unlock();
}

uint8_t CommReader::get_data(size_t id, uint8_t* data_buff)
{
    uint8_t data_len;

    m_locker.lock();
    if(m_data_lib[id] == NULL)
    {
        memset(data_buff, 0x00, sizeof(uint8_t) * 8);
        data_len = 0;
    }else{
        m_data_lib[id]->hash_counter++;
        memcpy(data_buff, m_data_lib[id]->data, sizeof(uint8_t) * 8);
        data_len = m_data_lib[id]->data_len;
    }
    m_locker.unlock();

    return data_len;
}

uint8_t CommReader::get_hash_counter(size_t id)
{
    uint8_t hash_counter;

    m_locker.lock();
    if(m_data_lib[id] == NULL)
    {
        hash_counter = 0;
    }else{
        hash_counter = m_data_lib[id]->hash_counter;
    }
    m_locker.unlock();

    return hash_counter;
}

}