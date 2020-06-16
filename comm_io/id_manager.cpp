#include "id_manager.hpp"

namespace driver_comm
{

thread_util::locker                      IdManager::m_locker;
std::unordered_map<byte, std::string>    IdManager::m_id_map;

IdManager::IdManager(void)
{
}

void IdManager::IdManager_cons(void)
{
}

void IdManager::set_id(byte id, std::string name)
{
    m_locker.lock();
    this->nolock_set_id(id, name);
    m_locker.unlock();
}

std::string IdManager::get_devname(byte id)
{
    m_locker.lock();
    std::string dev_string = this->nolock_get_devname(id);
    m_locker.unlock();
   return dev_string;
}

bool IdManager::isset_id(byte id)
{
    m_locker.lock();
    bool isset = this->nolock_isset_id(id);
    m_locker.unlock();
   return isset;
}


void IdManager::nolock_set_id(byte id, std::string name)
{
    if(this->m_id_map.find(id) != this->m_id_map.end())
    {
        this->m_id_map[id] = name;
    }
    else
    {
        this->m_id_map.emplace(id, name);
    }
}

std::string IdManager::nolock_get_devname(byte id)
{
    return this->m_id_map[id];
}

bool IdManager::nolock_isset_id(byte id)
{
    if(this->m_id_map.find(id) != this->m_id_map.end())
    {
        return true;
    }else{
        return false;
    }
}

}