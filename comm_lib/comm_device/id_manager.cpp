#include "id_manager.hpp"

namespace comm_device
{

thread_util::locker                         IdManager::m_locker;
std::unordered_map<uint8_t, std::string>    IdManager::m_id_map;

IdManager::IdManager(void)
{
}

void IdManager::set_id(const std::string name, uint8_t id)
{
    m_locker.lock();
    nolock_set_id(name, id);
    m_locker.unlock();
}

std::string IdManager::get_devname(uint8_t id)
{
    m_locker.lock();
    std::string dev_string = nolock_get_devname(id);
    m_locker.unlock();
   return dev_string;
}

bool IdManager::isset_id(uint8_t id)
{
    m_locker.lock();
    bool isset = nolock_isset_id(id);
    m_locker.unlock();
   return isset;
}


void IdManager::nolock_set_id(const std::string name, uint8_t id)
{
    if(m_id_map.find(id) != m_id_map.end())
    {
        m_id_map[id] = name;
    }
    else
    {
        m_id_map.emplace(id, name);
    }
}

std::string IdManager::nolock_get_devname(uint8_t id)
{
    return m_id_map[id];
}

bool IdManager::nolock_isset_id(uint8_t id)
{
    if(m_id_map.find(id) != m_id_map.end())
    {
        return true;
    }else{
        return false;
    }
}

}